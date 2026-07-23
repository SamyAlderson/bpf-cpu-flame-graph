# bpf-cpu-flame-graph
A BPF-based CPU flame graph generator for performance analysis

## What it does
This project generates a CPU flame graph using BPF (Berkeley Packet Filter) for performance analysis. It's designed to provide a detailed view of CPU usage, helping developers identify performance bottlenecks and optimize their systems.

## Install
To install, simply clone this repository and compile the BPF program:
```bash
git clone https://github.com/SamyAlderson/bpf-cpu-flame-graph.git
cd bpf-cpu-flame-graph
make
```
## Usage
To generate a CPU flame graph, run the following command:
```bash
sudo ./bpf-cpu-flame-graph > flame_graph.svg
```
This will generate a flame graph in SVG format, which can be viewed using any web browser.

## Building from source
To build from source, run the following commands:
```bash
make clean
make
```
This will recompile the BPF program and any dependencies.

## Running tests
To run the test suite, execute the following command:
```bash
make test
```
This will run the tests in the `test/` directory.

## Project structure
The project consists of the following key files:

* `bpf-cpu-flame-graph.c`: The main BPF program.
* `parser.c`: A utility function for parsing CPU usage data.
* `test/`: A test suite for the BPF program.
* `Makefile`: A build script for compiling and linking the BPF program.

## License
Copyright (c) 2026 SamyAlderson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.