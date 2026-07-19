#include <linux/bpf.h>
#include <linux/version.h>
#include "bpf.h"
#include "utils.h"

extern struct bpf_map_def __maps[] = {
    {
        .type = BPF_MAP_TYPE_ARRAY,
        .key_size = sizeof(u32),
        .value_size = sizeof(u64),
        .max_entries = 1,
        .name = "cpu_flame_graph",
    },
};

static struct bpf_program __programs[] = {
    {
        .type = BPF_PROG_TYPE_SCHED_CLS,
        .log_level = 1,
        .license = "GPL",
        .kern_version = THIS_KERNEL_VERSION,
        .instructions = (struct bpf_insn[]) {
            {
                .code = BPF_STMT(BPF_LD | BPF_W | BPF_ABS, 0),
                .jt = 0,
                .jf = 1,
                .k = 0,
                .b = 0,
            },
            {
                .code = BPF_STMT(BPF_ST, 0),
                .jt = 0,
                .jf = 0,
                .k = 0,
                .b = 0,
            },
            {
                .code = BPF_STMT(BPF_LD | BPF_W | BPF_ABS, 0),
                .jt = 0,
                .jf = 1,
                .k = 0,
                .b = 0,
            },
            {
                .code = BPF_STMT(BPF_JMP | BPF_JA, -3),
                .jt = 0,
                .jf = 0,
                .k = 0,
                .b = 0,
            },
            {
                .code = BPF_STMT(BPF_LD | BPF_W | BPF_ABS, 0),
                .jt = 0,
                .jf = 1,
                .k = 0,
                .b = 0,
            },
            {
                .code = BPF_STMT(BPF_ST, 0),
                .jt = 0,
                .jf = 0,
                .k = 0,
                .b = 0,
            },
            {
                .code = BPF_STMT(BPF_LD | BPF_W | BPF_ABS, 0),
                .jt = 0,
                .jf = 1,
                .k = 0,
                .b = 0,
            },
            {
                .code = BPF_STMT(BPF_JMP | BPF_JA, -3),
                .jt = 0,
                .jf = 0,
                .k = 0,
                .b = 0,
            },
            BPF_STMT(BPF_RET | BPF_K, 0),
            BPF_STMT(BPF_EXIT, 0),
        },
        .pages = 1,
    },
};

static int __init bpf_program_init(void) {
    int ret = bpf_progs_attach(__programs, __maps);
    if (ret < 0)
        pr_err("Failed to load BPF program: %d\n", ret);
    return ret;
}

static void __exit bpf_program_exit(void) {
    bpf_progs_detach(__programs);
}

module_init(bpf_program_init);
module_exit(bpf_program_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Samy Alderson");
MODULE_DESCRIPTION("CPU flame graph generator using BPF");
MODULE_VERSION("0.1");
```

```c
// bpf.h
#ifndef _BPF_H_
#define _BPF_H_

struct bpf_map_def {
    u32 type;
    u16 key_size;
    u16 value_size;
    u32 max_entries;
    char name[];
};

struct bpf_program {
    u32 type;
    u32 log_level;
    char license[];
    char kern_version[];
    struct bpf_insn *instructions;
    u32 pages;
};

struct bpf_insn {
    u8 code;
    u8 jt;
    u8 jf;
    u32 k;
    u32 b;
};

int bpf_progs_attach(struct bpf_program *programs, struct bpf_map_def *maps);
void bpf_progs_detach(struct bpf_program *programs);

#endif // _BPF_H_
```

```c
// utils.h
#ifndef _UTILS_H_
#define _UTILS_H_

#include <linux/types.h>

void pr_err(const char *fmt, ...);

#endif // _UTILS_H_
```

```c
// utils.c
#include <linux/kernel.h>
#include "utils.h"

void pr_err(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printk(KERN_ERR fmt, args);
    va_end(args);
}