# BPF-CPU-Flame-Graph
Generate CPU flame graphs using BPF for performance analysis

A lightweight tool for visualizing CPU usage patterns.

## What it does
This project uses BPF (Berkeley Packet Filter) to generate a CPU flame graph, useful for performance analysis. It's designed to be simple and easy to use. The goal is to provide a basic framework for exploring CPU usage patterns.

## Install
```bash
git clone https://github.com/SamyAlderson/bpf-cpu-flame-graph.git
cd bpf-cpu-flame-graph
make
```

## Usage
```bash
./bpf-cpu-flame-graph -h
Usage: ./bpf-cpu-flame-graph [options] <pid>
  -h, --help            show this help message and exit
  -p, --pid PID         process ID to analyze
  -o, --output FILE     output file for the flame graph
```
Run the tool with a process ID, e.g.:
```bash
./bpf-cpu-flame-graph -p 1234 -o flamegraph.svg
```
This will generate a flame graph for process 1234 and save it as flamegraph.svg.

## Build from source
Make sure you have the necessary dependencies installed, including a C compiler and the bpf libraries. Then, run:
```bash
make
```

## Run tests
```bash
make test
```
This will run the test suite, which includes 7 test cases.

## Project structure
- `main.c`: the entry point for the program
- `bpf.c`: contains the BPF-related code
- `utils.c`: utility functions for the program
- `test_main.c`: the test suite
- `Makefile`: the build script
- `README.md`: this file
- `LICENSE`: the project license

## License
Copyright (c) 2026 SamyAlderson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.