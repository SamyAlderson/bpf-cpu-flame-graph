#include "utils.h"
#include "bpf.h"

// Function to map a CPU ID to a human-readable string
const char *cpu_to_str(int cpu_id) {
    // This function is a bit of a hack, but it works for now
    // A more proper solution would involve a database of CPU information
    switch (cpu_id) {
        case 0:
            return "CPU 0";
        case 1:
            return "CPU 1";
        case 2:
            return "CPU 2";
        default:
            return "CPU unknown";
    }
}

// Function to map a BPF program return code to a human-readable string
const char *bpf_ret_to_str(int ret) {
    // This is a bit of a mess, but it's better than nothing
    switch (ret) {
        case BPF_OK:
            return "BPF_OK";
        case BPF_ERR:
            return "BPF_ERR";
        case BPF_NO_MEM:
            return "BPF_NO_MEM";
        default:
            return "BPF unknown";
    }
}

// Function to print a CPU flame graph
void print_flame_graph(struct bpf_flame_graph *flame_graph) {
    // This was tricky to implement, but it's working now
    printf("CPU flame graph:\n");
    for (int i = 0; i < flame_graph->num_cpus; i++) {
        struct bpf_cpu_info *cpu_info = &flame_graph->cpus[i];
        printf("%s\n", cpu_to_str(i));
        printf("  %d: %d\n", cpu_info->pid, cpu_info->time);
    }
}

// Function to free a BPF program
void free_bpf_program(struct bpf_program *program) {
    // Not proud of this but it works
    if (program->maps != NULL) {
        for (int i = 0; i < program->num_maps; i++) {
            free(program->maps[i]);
        }
        free(program->maps);
    }
    if (program->progs != NULL) {
        for (int i = 0; i < program->num_progs; i++) {
            free(program->progs[i]);
        }
        free(program->progs);
    }
}

// Function to print a BPF program error message
void print_bpf_error(int ret) {
    // This is a bit of a mess, but it's better than nothing
    printf("BPF error: %s\n", bpf_ret_to_str(ret));
}