/* Include stdlib.h for exit function */
#include <stdlib.h>

/* Include bpf.h for BPF definitions */
#include <bpf.h>

/* Include utils.h for custom functions */
#include "utils.h"

int main() {
    /* Initialize BPF */
    bpf_init();

    /* Call custom function */
    my_custom_function();

    /* Exit with success code */
    exit(EXIT_SUCCESS);
}

/* Define custom function */
void my_custom_function() {
    /* Your custom function implementation */
}
