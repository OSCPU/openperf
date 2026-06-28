#!/usr/bin/env python3
import subprocess
import sys
import time

def main() -> int:
    if len(sys.argv) < 2:
        print("usage: monotonic_time.py COMMAND [ARG...]", file=sys.stderr)
        return 2

    start = time.monotonic()
    result = subprocess.run(sys.argv[1:])
    elapsed = time.monotonic() - start
    print(f"[WALL] {elapsed:.2f} s", flush=True)
    return result.returncode

if __name__ == "__main__":
    raise SystemExit(main())
