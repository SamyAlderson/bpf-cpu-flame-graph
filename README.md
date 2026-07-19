# bpf-cpu-flame-graph
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![CI Status](https://github.com/SamyAlderson/bpf-cpu-flame-graph/actions/workflows/ci.yml/badge.svg)](https://github.com/SamyAlderson/bpf-cpu-flame-graph/actions/workflows/ci.yml)
[![Language: C](https://img.shields.io/badge/Language-C-green.svg)](https://isocpp.org/)

**"Visualize CPU performance with precision and simplicity"**

## Overview

bpf-cpu-flame-graph is a C-based project that generates a CPU flame graph using BPF (Berkeley Packet Filter) for performance analysis. This tool is designed to provide a detailed breakdown of CPU usage, enabling developers to pinpoint performance bottlenecks and optimize system resources.

## Features

*   BPF program compilation
*   CPU flame graph generation
*   Performance analysis
*   Kernel module loading

## Prerequisites

*   Linux kernel 4.10 or later
*   BPF support enabled (usually enabled by default)
*   C compiler (e.g., `gcc`)
*   Make utility (usually installed by default)

## Installation

1.  Clone the repository using Git: `git clone https://github.com/SamyAlderson/bpf-cpu-flame-graph.git`
2.  Navigate to the project directory: `cd bpf-cpu-flame-graph`
3.  Run the build script using Make: `make`

## Usage

To generate a CPU flame graph, follow these steps:

```bash
# Load the BPF program
sudo ./bpf_load.sh

# Run the flame graph generator
./flame_graph.sh
```

This will produce a flame graph in the `output` directory.

```c
// Example usage in src/main.c
#include <stdio.h>
#include "bpf.h"

int main() {
    // Load the BPF program
    int fd = bpf_load_program(BPF_OBJ_FILE);

    // Generate the flame graph
    flame_graph(fd);

    return 0;
}
```

## Project Architecture / Structure

The project is structured as follows:

*   `src/`: Source code directory
    *   `main.c`: Main entry point for the BPF program
    *   `utils.c`: Utility functions for the BPF program
    *   `bpf.c`: BPF program implementation
    *   `bpf.h`: Header file for the BPF program
*   `tests/`: Unit tests directory
    *   `test_bpf.c`: Unit tests for the BPF program
    *   `test_utils.c`: Unit tests for the utility functions
*   `Makefile`: Build script for the project
*   `config.mk`: Makefile configuration file

## Building from Source

To build the project from source, run the following commands:

```bash
# Compile the BPF program
make

# Load the BPF program
sudo ./bpf_load.sh

# Generate the flame graph
./flame_graph.sh
```

## Testing

Unit tests are located in the `tests/` directory. To run the tests, use the following command:

```bash
make test
```

## Contributing Guidelines

Contributions are welcome and appreciated! Please follow these guidelines:

1.  Fork the repository on GitHub
2.  Create a new branch for your changes
3.  Make your changes and commit them
4.  Push your changes to the remote branch
5.  Open a pull request on GitHub

## License

bpf-cpu-flame-graph is licensed under the MIT License. See `LICENSE.txt` for details.