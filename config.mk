# config.mk: Makefile configuration file for bpf-cpu-flame-graph

# Define the project name and version
PROJECT_NAME = bpf-cpu-flame-graph
PROJECT_VERSION = 1.0

# Define the Linux kernel version to target
TARGET_KERNEL_VERSION = $(shell uname -r)

# Define the BPF program compilation flags
CFLAGS_BPF = -Wall -Wextra -O2 -fPIC -DBPF_MAJOR_VERSION=1 -DBPF_MINOR_VERSION=0

# Define the C compiler flags
CFLAGS = -Wall -Wextra -O2

# Define the linker flags
LDFLAGS = -shared

# Define the object files and libraries to link against
OBJECTS = main.o utils.o bpf.o
LIBRARIES = -lelf

# Define the kernel module loading flags
LOAD_FLAGS = -m elf_i386 -Ttext 0x10000000

# Define the CPU flame graph generation flags
FLAME_GRAPH_FLAGS = -O2 -fprofile-generate

# Define the unit test flags
TEST_FLAGS = -Wall -Wextra -O2 -pthread

# Define the dependencies to install
DEPENDENCIES = linux-headers libelf-dev

# Define the Makefile targets
all: main

main: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o main

main.o: src/main.c
	$(CC) $(CFLAGS) $(CFLAGS_BPF) -c src/main.c -o main.o

utils.o: src/utils.c src/utils.h
	$(CC) $(CFLAGS) $(CFLAGS_BPF) -c src/utils.c -o utils.o

bpf.o: src/bpf.c src/bpf.h
	$(CC) $(CFLAGS) $(CFLAGS_BPF) -c src/bpf.c -o bpf.o

tests: test_utils test_bpf

test_utils: test_utils.o
	$(CC) $(TEST_FLAGS) test_utils.o $(LIBRARIES) -o test_utils

test_utils.o: tests/test_utils.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c tests/test_utils.c -o test_utils.o

test_bpf: test_bpf.o
	$(CC) $(TEST_FLAGS) test_bpf.o $(LIBRARIES) -o test_bpf

test_bpf.o: tests/test_bpf.c
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c tests/test_bpf.c -o test_bpf.o

install:
	sudo make -C /lib/modules/$(TARGET_KERNEL_VERSION)/build M=$(PWD) modules

load:
	sudo insmod main.ko

unload:
	sudo rmmod main

clean:
	rm -f *.o *.ko main test_utils test_bpf

flame_graph:
	sudo ./main -f flame_graph.svg -t 1

.PHONY: all main tests install load unload clean flame_graph