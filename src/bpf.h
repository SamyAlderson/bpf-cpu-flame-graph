#ifndef BPF_H
#define BPF_H

/**
 * @file bpf.h
 * @brief Header file for BPF program
 *
 * This header file provides the interface for the BPF program.
 * It includes function prototypes, macro definitions, and type
 * declarations for the program's functionality.
 */

#include <linux/types.h>
#include <linux/bpf.h>

/**
 * @def BPF_CPU_FLAME_GRAPH_MAJOR
 * @brief Major version number of the BPF program
 */
#define BPF_CPU_FLAME_GRAPH_MAJOR 1

/**
 * @def BPF_CPU_FLAME_GRAPH_MINOR
 * @brief Minor version number of the BPF program
 */
#define BPF_CPU_FLAME_GRAPH_MINOR 0

/**
 * @enum bpf_cpu_flame_graph_err
 * @brief Error codes for the BPF program
 */
typedef enum {
    /**
     * No error occurred
     */
    BPF_CPU_FLAME_GRAPH_ERR_NONE = 0,

    /**
     * Failed to load kernel module
     */
    BPF_CPU_FLAME_GRAPH_ERR_MODULE_LOAD_FAILURE = -1,

    /**
     * Failed to initialize BPF program
     */
    BPF_CPU_FLAME_GRAPH_ERR_BPF_INIT_FAILURE = -2,

    /**
     * Failed to generate CPU flame graph
     */
    BPF_CPU_FLAME_GRAPH_ERR_FLAME_GRAPH_GEN_FAILURE = -3,

    /**
     * Unknown error
     */
    BPF_CPU_FLAME_GRAPH_ERR_UNKNOWN = -4,
} bpf_cpu_flame_graph_err;

/**
 * @typedef bpf_cpu_flame_graph_probe
 * @brief BPF probe type for CPU flame graph generation
 */
typedef struct {
    /**
     * Probe ID
     */
    __be32 id;

    /**
     * Probe name
     */
    char name[16];
} bpf_cpu_flame_graph_probe;

/**
 * @fn void __exit bpf_cpu_flame_graph_cleanup(void)
 * @brief Clean up function for the BPF program
 *
 * This function is called when the BPF program is unloaded.
 * It ensures that all resources are released and the program is cleaned up.
 */
void __exit bpf_cpu_flame_graph_cleanup(void);

/**
 * @fn int __init bpf_cpu_flame_graph_init(void)
 * @brief Initialization function for the BPF program
 *
 * This function is called when the BPF program is loaded.
 * It sets up the program's resources and initializes the CPU flame graph generation.
 *
 * @return 0 on success, negative error code on failure
 */
int __init bpf_cpu_flame_graph_init(void);

#endif  // BPF_H