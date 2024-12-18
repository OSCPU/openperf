import sys
import argparse
from datetime import datetime
import json
import yaml
import itertools
import re
import asyncio
from tqdm.asyncio import tqdm_asyncio
from dataclasses import dataclass, field
from typing import List, Tuple, Set, Dict, Optional, Any


@dataclass
class OpenPerfTiming:
    seconds: int
    milliseconds: float


@dataclass
class TestParameters:
    """Represents the parameters configuration for a test"""

    parameters: Dict[str, List[str]]


@dataclass
class TestDefinition:
    """Represents a single test configuration"""

    timeout: Optional[int]
    format: str
    parameters: TestParameters
    tags: List[str] = field(default_factory=list)  # List of tags for filtering


@dataclass
class TestConfiguration:
    """Root configuration class"""

    max_workers: Optional[int]
    tests: Dict[str, TestDefinition]


@dataclass
class TestResult:
    test_name: str
    command: str
    returncode: int
    stderr: str
    duration: float
    timestamp: str
    openperf_timing: Optional[OpenPerfTiming] = None
    tags: List[str] = field(default_factory=list)


class TestConfig:
    def __init__(self, config_path: str):
        """Load and parse test configuration file."""
        with open(config_path, "r") as f:
            raw_config = yaml.safe_load(f)

        # Convert raw dictionary to dataclass
        tests_dict = {}
        for test_name, test_data in raw_config.get("tests", {}).items():
            test_params = TestParameters(parameters=test_data.get("parameters", {}))
            tests_dict[test_name] = TestDefinition(
                timeout=test_data.get("timeout"),
                format=test_data.get("format", ""),
                parameters=test_params,
                tags=test_data.get("tags", []),  # Test tags
            )

        self.config = TestConfiguration(
            max_workers=raw_config.get("max_workers"),
            tests=tests_dict,
        )

        self.validate_config()

    def validate_config(self):
        """Validate the configuration file structure."""
        if not self.config.tests:
            raise ValueError("Missing required field 'tests' in config")

        for test_name, test_config in self.config.tests.items():
            if not test_config.parameters.parameters:
                raise ValueError(f"Test '{test_name}' must have 'parameters' field")

    def filter_tests_by_tags(
        self, include_tags: Optional[Set[str]]
    ) -> Dict[str, TestDefinition]:
        """Filter tests based on tags."""
        if not include_tags:
            return self.config.tests

        filtered_tests = {}
        for test_name, test_def in self.config.tests.items():
            test_tags = set(test_def.tags)
            # Include test if it has any of the included tags (or if no include_tags specified)
            if test_tags & include_tags:
                filtered_tests[test_name] = test_def

        return filtered_tests

    def generate_test_cases(
        self,
        include_tags: Optional[Set[str]] = None,
    ) -> List[Dict[str, Any]]:
        """Generate all test cases from config, filtered by tags."""
        test_cases = []

        # Filter tests by tags
        filtered_tests = self.filter_tests_by_tags(include_tags)

        for test_name, test_config in filtered_tests.items():
            # Separate positional and named parameters
            positional_params = []
            named_params = {}

            for param_name, param_values in test_config.parameters.parameters.items():
                try:
                    pos = int(param_name)
                    while len(positional_params) <= pos:
                        positional_params.append(None)
                    positional_params[pos] = param_values
                except ValueError:
                    named_params[param_name] = param_values

            positional_combinations = list(
                itertools.product(*[p for p in positional_params if p is not None])
            )
            named_combinations = [
                dict(zip(named_params.keys(), values))
                for values in itertools.product(*named_params.values())
            ]

            if not named_combinations:
                named_combinations = [{}]

            for pos_values in positional_combinations:
                for named_values in named_combinations:
                    command = test_config.format.format(*pos_values, **named_values)

                    param_strs = []
                    for i, value in enumerate(pos_values):
                        param_strs.append(f"p{i}-{value}")
                    for name, value in named_values.items():
                        param_strs.append(f"{name}-{value}")

                    case_name = f"{test_name}_{'_'.join(param_strs)}"

                    case = {
                        "name": case_name,
                        "args": command.split(),
                        "timeout": test_config.timeout,
                        "tags": test_config.tags,
                    }
                    test_cases.append(case)

        return test_cases


class TestRunner:
    def __init__(self):
        self.results: List[TestResult] = []

    def _parse_openperf_timing(self, output: str) -> Optional[OpenPerfTiming]:
        """Parse OpenPerf timing from output."""
        pattern = r"OpenPerf time:(?:\s+(?P<seconds>\d+)\s+s,)?\s+(?P<milliseconds>[\d.]+)\s+ms"
        match = re.search(pattern, output)
        if match:
            seconds = int(match.group("seconds")) if match.group("seconds") else 0
            milliseconds = float(match.group("milliseconds"))
            return OpenPerfTiming(seconds=seconds, milliseconds=milliseconds)
        return None

    async def _run_single_test(
        self, test_config: Tuple[str, List[str], Optional[int], List[str]]
    ) -> TestResult:
        """Run a single test in a separate process asynchronously."""
        name, args, timeout, tags = test_config

        command = args
        start_time = asyncio.get_event_loop().time()

        try:
            process = await asyncio.create_subprocess_exec(
                *command,
                stdout=asyncio.subprocess.PIPE,
                stderr=asyncio.subprocess.PIPE,
            )
            try:
                stdout_byte, stderr_byte = await asyncio.wait_for(
                    process.communicate(), timeout=timeout
                )
            except TimeoutError:
                process.kill()
                return TestResult(
                    test_name=name,
                    command=" ".join(command),
                    returncode=-256,
                    stderr="Python timeout waiting for subprocess",
                    duration=asyncio.get_event_loop().time() - start_time,
                    timestamp=datetime.now().isoformat(),
                    openperf_timing=None,
                    tags=tags,
                )

            stdout = stdout_byte.decode()
            stderr = stderr_byte.decode()
            openperf_timing = self._parse_openperf_timing(stdout + stderr)
            returncode = process.returncode if process.returncode is not None else -256

            return TestResult(
                test_name=name,
                command=" ".join(command),
                returncode=returncode,
                stderr=stderr,
                duration=asyncio.get_event_loop().time() - start_time,
                timestamp=datetime.now().isoformat(),
                openperf_timing=openperf_timing,
                tags=tags,
            )

        except Exception as e:
            return TestResult(
                test_name=name,
                command=" ".join(command),
                returncode=-1,
                stderr=f"Test failed with error: {str(e)}",
                duration=0.0,
                timestamp=datetime.now().isoformat(),
                openperf_timing=None,
                tags=tags,
            )

    async def run_tests(
        self,
        tests: List[Tuple[str, List[str], Optional[int], List[str]]],
        max_concurrent: Optional[int],
    ) -> List[TestResult]:
        """Run multiple tests concurrently using asyncio.

        Args:
            tests: List of tuples containing (test_name, args_list, timeout, tags)
            max_concurrent: Maximum number of concurrent test processes
        Returns:
            List of TestResult objects
        """
        # Create a semaphore to limit concurrent processes
        semaphore = asyncio.Semaphore(max_concurrent if max_concurrent else 8)

        async def run_with_semaphore(test_config):
            async with semaphore:
                return await self._run_single_test(test_config)

        # Create tasks for all tests
        tasks = [run_with_semaphore(test_config) for test_config in tests]

        # Run tests with progress bar
        self.results = await tqdm_asyncio.gather(*tasks, desc="Running tests")
        return self.results

    def export_results(self, output_file: str):
        """Export test results to JSON file."""
        results_dict = [
            {
                "test_name": r.test_name,
                "command": r.command,
                "returncode": r.returncode,
                "stderr": r.stderr,
                "duration": r.duration,
                "timestamp": r.timestamp,
                "openperf_timing": (
                    {
                        "seconds": r.openperf_timing.seconds,
                        "milliseconds": r.openperf_timing.milliseconds,
                        "total_seconds": r.openperf_timing.seconds
                        + (r.openperf_timing.milliseconds / 1000),
                    }
                    if r.openperf_timing
                    else None
                ),
            }
            for r in self.results
        ]
        with open(output_file, "w") as f:
            json.dump(results_dict, f, indent=2)


def format_openperf_time(timing: Optional[OpenPerfTiming]) -> str:
    """Format OpenPerf timing for display."""
    if timing:
        if timing.seconds != 0:
            return f"{timing.seconds} s, {timing.milliseconds:.3f} ms"
        else:
            return f"{timing.milliseconds:.3f} ms"
    else:
        return "N/A"


def run_from_config(
    config_path: str,
    output_file: Optional[str] = None,
    include_tags: Optional[Set[str]] = None,
) -> int:
    """Run all tests specified in a config file."""
    config = TestConfig(config_path)
    runner = TestRunner()

    test_cases = config.generate_test_cases(include_tags)
    results = asyncio.run(
        runner.run_tests(
            list(
                (t["name"], t["args"], t.get("timeout"), t["tags"]) for t in test_cases
            ),
            max_concurrent=config.config.max_workers,
        )
    )

    print(f"\nRunning tests from config: {config_path}")
    if include_tags:
        print(f"Including tags: {', '.join(include_tags)}")
    print(
        "\n{:<30} {:<15} {:<25} {:<10} {:<20}".format(
            "Test Name", "Return Code", "OpenPerf Time", "Duration", "Tags"
        )
    )
    print("-" * 100)

    failed = 0
    for result in results:
        print(
            "{:<30} {:<15} {:<25} {:.2f}s {:<20}".format(
                result.test_name,
                result.returncode,
                format_openperf_time(result.openperf_timing),
                result.duration,
                ", ".join(result.tags),
            )
        )

        if result.returncode != 0:
            failed += 1
            print("Error:")
            print(result.stderr)

    if output_file:
        runner.export_results(output_file)
        print(f"\nResults exported to {output_file}")

    return failed


def main():
    parser = argparse.ArgumentParser(description="Test Runner for Binary Files")
    parser.add_argument("config", help="Path to YAML config file")
    parser.add_argument("--output", help="Output JSON file for results")
    parser.add_argument(
        "--tags",
        help="Only run tests with these tags (comma-separated)",
        type=str,
    )
    args = parser.parse_args()

    # Convert tag arguments to sets
    include_tags = set(args.tags.split(",")) if args.tags else None

    try:
        failed = run_from_config(args.config, args.output, include_tags)
        if failed == 0:
            sys.exit(0)
        else:
            sys.exit(1)
    except Exception as e:
        print(f"Error: {str(e)}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
