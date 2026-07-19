// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include "bpf.h"
#include "utils.h"

// Function to print usage
void print_usage(void) {
    printf("Usage: %s <options>\n", argv[0]);
}

int main(int argc, char **argv) {
    // Initialize variables
    int opt;
    char *optarg;

    // Parse command line options
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h':
                print_usage();
                return 0;
            default:
                fprintf(stderr, "Invalid option: %c\n", opt);
                return 1;
        }
    }

    // Call bpf_init function
    if (bpf_init() < 0) {
        fprintf(stderr, "Failed to initialize BPF\n");
        return 1;
    }

    // Call main function
    return main_func();
}
