import sys
import os
import argparse
from typing import List, Dict, Optional, Any
from dataclasses import dataclass
from datetime import datetime
import json
import yaml
import itertools
import re
import asyncio
import json
import os
import re
from datetime import datetime
from typing import List, Optional, Tuple
from dataclasses import dataclass
from tqdm.asyncio import tqdm_asyncio


@dataclass
class OpenPerfTiming:
    seconds: int
    milliseconds: float


@dataclass
class TestResult:
    test_name: str
    command: str
    returncode: int
    stderr: str
    duration: float
    timestamp: str
    openperf_timing: Optional[OpenPerfTiming] = None


class TestConfig:
    def __init__(self, config_path: str):
        """Load and parse test configuration file."""
        with open(config_path, "r") as f:
            self.config = yaml.safe_load(f)
        self.validate_config()

    def validate_config(self):
        """Validate the configuration file structure."""
        required_fields = ["binary", "tests"]
        for field in required_fields:
            if field not in self.config:
                raise ValueError(f"Missing required field '{field}' in config")

        if not isinstance(self.config["tests"], dict):
            raise ValueError("'tests' must be a dictionary")

    def generate_test_cases(self) -> List[Dict[str, Any]]:
        """Generate all test cases from config."""
        test_cases = []

        for test_name, test_config in self.config["tests"].items():
            if not {"format", "parameters"}.issubset(test_config.keys()):
                raise ValueError(
                    f"Test '{test_name}' must have 'format' and 'parameters' fields"
                )

            # Separate positional and named parameters
            positional_params = []
            named_params = {}

            for param_name, param_values in test_config["parameters"].items():
                try:
                    # If parameter name can be converted to int, it's positional
                    pos = int(param_name)
                    # Ensure list has enough slots for this position
                    while len(positional_params) <= pos:
                        positional_params.append(None)
                    positional_params[pos] = param_values
                except ValueError:
                    # If parameter name is not an integer, it's named
                    named_params[param_name] = param_values

            # Generate all combinations of parameter values
            positional_combinations = list(
                itertools.product(*[p for p in positional_params if p is not None])
            )
            named_combinations = [
                dict(zip(named_params.keys(), values))
                for values in itertools.product(*named_params.values())
            ]

            # If no named parameters, ensure we have at least an empty dict
            if not named_combinations:
                named_combinations = [{}]

            # Generate each test case from the combinations
            for pos_values in positional_combinations:
                for named_values in named_combinations:
                    # Format string with both positional and named parameters
                    command = test_config["format"].format(*pos_values, **named_values)

                    # Generate descriptive name for this test case
                    param_strs = []
                    for i, value in enumerate(pos_values):
                        param_strs.append(f"p{i}-{value}")
                    for name, value in named_values.items():
                        param_strs.append(f"{name}-{value}")

                    case_name = f"{test_name}_{'_'.join(param_strs)}"

                    case = {
                        "name": case_name,
                        "args": command.split(),
                        "timeout": test_config.get("timeout"),
                    }
                    test_cases.append(case)

        return test_cases


class TestRunner:
    def __init__(self, binary_path: str):
        """Initialize the test runner with path to binary."""
        if not os.path.exists(binary_path):
            raise FileNotFoundError(f"Binary not found at {binary_path}")
        if not os.access(binary_path, os.X_OK):
            raise PermissionError(f"Binary at {binary_path} is not executable")
        self.binary_path = binary_path
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
        self, test_config: Tuple[str, List[str], Optional[int]]
    ) -> TestResult:
        """Run a single test in a separate process asynchronously."""
        name, args, timeout = test_config
        command = [self.binary_path] + args
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
                )

            stderr = stderr_byte.decode()
            openperf_timing = self._parse_openperf_timing(stderr)
            returncode = process.returncode
            if returncode is None:
                returncode = -256
            return TestResult(
                test_name=name,
                command=" ".join(command),
                returncode=returncode,
                stderr=stderr,
                duration=asyncio.get_event_loop().time() - start_time,
                timestamp=datetime.now().isoformat(),
                openperf_timing=openperf_timing,
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
            )

    async def run_tests(
        self,
        tests: List[Tuple[str, List[str], Optional[int]]],
        max_concurrent: Optional[int],
    ) -> List[TestResult]:
        """Run multiple tests concurrently using asyncio.

        Args:
            tests: List of tuples containing (test_name, args_list, timeout)
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


def run_from_config(config_path: str, output_file: Optional[str] = None):
    """Run all tests specified in a config file."""
    config = TestConfig(config_path)
    runner = TestRunner(config.config["binary"])

    test_cases = config.generate_test_cases()
    results = asyncio.run(
        runner.run_tests(
            list((t["name"], t["args"], t.get("timeout")) for t in test_cases),
            max_concurrent=config.config.get("max_workers"),
        )
    )

    print(f"\nRunning tests from config: {config_path}")
    print(
        "\n{:<30} {:<15} {:<25} {:<10}".format(
            "Test Name", "Return Code", "OpenPerf Time", "Duration"
        )
    )
    print("-" * 80)
    for result in results:
        print(
            "{:<30} {:<15} {:<25} {:.2f}s".format(
                result.test_name,
                result.returncode,
                format_openperf_time(result.openperf_timing),
                result.duration,
            )
        )

        if result.returncode != 0:
            print("Error:")
            print(result.stderr)

    if output_file:
        runner.export_results(output_file)
        print(f"\nResults exported to {output_file}")


def main():
    parser = argparse.ArgumentParser(description="Test Runner for Binary Files")
    parser.add_argument("config", help="Path to YAML config file")
    parser.add_argument("--output", help="Output JSON file for results")

    args = parser.parse_args()

    try:
        run_from_config(args.config, args.output)
    except Exception as e:
        print(f"Error: {str(e)}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
