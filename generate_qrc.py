#!/bin/python3
import sys
from pathlib import Path

if __name__ == "__main__":
    path = Path(sys.argv[1])
    if not path.is_dir():
        print("please use a directory")
        sys.exit(-1)
    files = [name for name in path.iterdir() if name.is_file()]
    for file in files:
        print(f"<file>./ui/{path.name}/{file.name}</file>")
