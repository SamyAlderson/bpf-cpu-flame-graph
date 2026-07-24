# bpf-cpu-flame-graph
**BPF-based CPU flame graph generator for performance analysis**

This project generates a CPU flame graph using BPF for performance analysis. It's a simple tool to help developers understand CPU usage and identify performance bottlenecks. The goal is to provide a lightweight, easy-to-use solution that integrates with existing BPF-based performance tools.

## Install
```bash
git clone https://github.com/SamyAlderson/bpf-cpu-flame-graph.git
cd bpf-cpu-flame-graph
make install
```
## Usage
```bash
./bpf-cpu-flame-graph --help
```
This will display usage instructions. Run the program with the `-p` flag to specify the file path where you want to save the flame graph.

## Build from Source
```bash
make
```
This will build the program and its dependencies.

## Run Tests
```bash
make test
```
This will run the test suite.

## Project Structure
- `bpf-cpu-flame-graph.c`: main program
- `bpf.c`: BPF-related functions
- `utils.c`: utility functions
- `test_bpf-cpu-flame-graph.c`: test suite
- `Makefile`: build script
- `README.md`: this file

## License
Copyright (c) 2026 SamyAlderson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.