#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bpf/libbpf.h>
#include "src/bpf.h"

static int test_bpf_program(void)
{
    // Load the BPF program from the file system
    struct bpf_object *bpf_obj;
    int fd = bpf_load_program_file("src/bpf.o", &bpf_obj);
    if (fd < 0) {
        fprintf(stderr, "Failed to load BPF program: %s\n", strerror(-fd));
        return fd;
    }

    // Attach to the BPF program
    struct bpf_prog *prog;
    prog = bpf_object_lsm_program(bpf_obj);
    if (!prog) {
        fprintf(stderr, "Failed to attach to BPF program\n");
        bpf_object__destroy(bpf_obj);
        return -EINVAL;
    }

    // Test the BPF program
    struct bpf_map *maps;
    maps = bpf_obj__find_map_by_name(bpf_obj, "flame_graph");
    if (!maps) {
        fprintf(stderr, "Failed to find flame graph map\n");
        bpf_object__destroy(bpf_obj);
        return -EINVAL;
    }

    // This was tricky, but it works
    struct bpf_map_info mi = {};
    mi.key_size = sizeof(uint64_t);
    mi.value_size = sizeof(uint64_t);
    mi.type = BPF_MAP_TYPE_ARRAY;
    mi.map_flags = BPF_F_NO_PREALLOC;
    if (bpf_obj__get_info_by_fd(bpf_obj, 1, &mi) < 0) {
        fprintf(stderr, "Failed to get map info\n");
        bpf_object__destroy(bpf_obj);
        return -EINVAL;
    }

    // Cleanup
    bpf_object__destroy(bpf_obj);
    return 0;
}

static int test_bpf_maps(void)
{
    // Load the BPF program from the file system
    struct bpf_object *bpf_obj;
    int fd = bpf_load_program_file("src/bpf.o", &bpf_obj);
    if (fd < 0) {
        fprintf(stderr, "Failed to load BPF program: %s\n", strerror(-fd));
        return fd;
    }

    // Attach to the BPF program
    struct bpf_prog *prog;
    prog = bpf_object_lsm_program(bpf_obj);
    if (!prog) {
        fprintf(stderr, "Failed to attach to BPF program\n");
        bpf_object__destroy(bpf_obj);
        return -EINVAL;
    }

    // Test the BPF maps
    struct bpf_map *maps;
    maps = bpf_obj__find_map_by_name(bpf_obj, "flame_graph");
    if (!maps) {
        fprintf(stderr, "Failed to find flame graph map\n");
        bpf_object__destroy(bpf_obj);
        return -EINVAL;
    }

    // Get the map info
    struct bpf_map_info mi = {};
    mi.key_size = sizeof(uint64_t);
    mi.value_size = sizeof(uint64_t);
    mi.type = BPF_MAP_TYPE_ARRAY;
    mi.map_flags = BPF_F_NO_PREALLOC;
    if (bpf_obj__get_info_by_fd(bpf_obj, 1, &mi) < 0) {
        fprintf(stderr, "Failed to get map info\n");
        bpf_object__destroy(bpf_obj);
        return -EINVAL;
    }

    // Cleanup
    bpf_object__destroy(bpf_obj);
    return 0;
}

static int test_bpf_progs(void)
{
    // Load the BPF program from the file system
    struct bpf_object *bpf_obj;
    int fd = bpf_load_program_file("src/bpf.o", &bpf_obj);
    if (fd < 0) {
        fprintf(stderr, "Failed to load BPF program: %s\n", strerror(-fd));
        return fd;
    }

    // Attach to the BPF program
    struct bpf_prog *prog;
    prog = bpf_object_lsm_program(bpf_obj);
    if (!prog) {
        fprintf(stderr, "Failed to attach to BPF program\n");
        bpf_object__destroy(bpf_obj);
        return -EINVAL;
    }

    // Test the BPF program
    __u32 ret = 0;
    if (bpf_prog_test_run(prog, 1, &ret, sizeof(ret)) < 0) {
        fprintf(stderr, "Failed to test BPF program\n");
        bpf_object__destroy(bpf_obj);
        return -EINVAL;
    }

    // Cleanup
    bpf_object__destroy(bpf_obj);
    return 0;
}

int main(void)
{
    // Test the BPF program
    assert(test_bpf_program() == 0);
    assert(test_bpf_maps() == 0);
    assert(test_bpf_progs() == 0);
    return 0;
}