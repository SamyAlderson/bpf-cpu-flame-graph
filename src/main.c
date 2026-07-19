#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <linux/bpf.h>
#include <linux/bpf.h>
#include <linux/filter.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include "bpf.h"
#include "utils.h"

#define BPF_MAX_PROG_SIZE 4096

struct thread_data {
    int fd;
    char *prog_name;
    char *map_name;
    char *file_name;
    char *path;
};

void *thread_func(void *arg) {
    struct thread_data *data = arg;
    int err;
    char buf[BPF_MAX_PROG_SIZE];

    // Load BPF program from file
    err = load_bpf_program(data->fd, data->prog_name, data->file_name, buf, BPF_MAX_PROG_SIZE);
    if (err < 0) {
        fprintf(stderr, "Error loading BPF program: %s\n", strerror(-err));
        exit(1);
    }

    // Attach BPF program to map
    err = attach_bpf_program(data->fd, data->map_name, buf, BPF_MAX_PROG_SIZE);
    if (err < 0) {
        fprintf(stderr, "Error attaching BPF program: %s\n", strerror(-err));
        exit(1);
    }

    // Start tracing
    err = start_tracing(data->fd);
    if (err < 0) {
        fprintf(stderr, "Error starting tracing: %s\n", strerror(-err));
        exit(1);
    }

    // Wait for tracing to complete
    wait_for_tracing_completion(data->fd);

    // Detach BPF program from map
    detach_bpf_program(data->fd, data->map_name);

    // Unload BPF program
    unload_bpf_program(data->fd, data->prog_name);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int err;
    int fd;
    char *prog_name;
    char *map_name;
    char *file_name;
    pthread_t thread;
    struct thread_data thread_data;
    char *path;

    // Check command-line arguments
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <prog_name> <map_name> <file_name> <path> <iterations>\n", argv[0]);
        exit(1);
    }

    prog_name = argv[1];
    map_name = argv[2];
    file_name = argv[3];
    path = argv[4];
    int iterations = atoi(argv[5]);

    // Create BPF socket
    fd = bpf_create_socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        fprintf(stderr, "Error creating BPF socket: %s\n", strerror(-fd));
        exit(1);
    }

    // Create BPF program
    err = create_bpf_program(fd, prog_name, file_name);
    if (err < 0) {
        fprintf(stderr, "Error creating BPF program: %s\n", strerror(-err));
        exit(1);
    }

    // Create map for BPF program
    err = create_bpf_map(fd, map_name, "hash");
    if (err < 0) {
        fprintf(stderr, "Error creating BPF map: %s\n", strerror(-err));
        exit(1);
    }

    // Create thread to run tracing
    thread_data.fd = fd;
    thread_data.prog_name = prog_name;
    thread_data.map_name = map_name;
    thread_data.file_name = file_name;
    thread_data.path = path;
    pthread_create(&thread, NULL, thread_func, &thread_data);

    // Wait for tracing to complete
    pthread_join(thread, NULL);

    // Close BPF socket
    close(fd);

    return 0;
}