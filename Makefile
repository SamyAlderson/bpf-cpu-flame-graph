# Build script for bpf-cpu-flame-graph project

# Configuration file
CONFIG = config.mk

# Source files
MAIN SRC = src/main.c
UTILS_SRC = src/utils.c
BPF_SRC = src/bpf.c
TEST_BPF_SRC = tests/test_bpf.c
TEST_UTILS_SRC = tests/test_utils.c

# Object files
MAIN_OBJ = $(MAIN_SRC:.c=.o)
UTILS_OBJ = $(UTILS_SRC:.c=.o)
BPF_OBJ = $(BPF_SRC:.c=.o)
TEST_BPF_OBJ = $(TEST_BPF_SRC:.c=.o)
TEST_UTILS_OBJ = $(TEST_UTILS_SRC:.c=.o)

# Header files
BPF_H = src/bpf.h
UTILS_H = src/utils.h

# Compilation flags
CFLAGS = -Wall -Wextra -Werror -O2 -Isrc -Itests
BPF_CFLAGS = -Wall -Wextra -Werror -O2 -Isrc -Itests -D__KERNEL__ -DBPF
TEST_CFLAGS = -Wall -Wextra -Werror -O2 -Isrc -Itests -DTEST_BPF

# ELF file for BPF program
ELF_FILE = bpf.o

# Kernel module file
KMOD_FILE = bpf.ko

# Test executable
TEST_EXEC = test_bpf

# BPF compilation target
all: $(ELF_FILE) $(KMOD_FILE)

# BPF program compilation
$(ELF_FILE): $(BPF_SRC) $(UTILS_H) $(BPF_H)
	$(CC) $(BPF_CFLAGS) -c $^ -o $@

# Kernel module compilation
$(KMOD_FILE): $(ELF_FILE) $(BPF_H)
	$(MAKE) -C /usr/src/linux-headers M=$(PWD) modules

# Utility functions compilation
$(UTILS_OBJ): $(UTILS_SRC) $(UTILS_H)
	$(CC) $(CFLAGS) -c $^ -o $@

# Main entry point compilation
$(MAIN_OBJ): $(MAIN_SRC) $(BPF_H) $(UTILS_H)
	$(CC) $(CFLAGS) -c $^ -o $@

# Unit tests for BPF program compilation
$(TEST_BPF_OBJ): $(TEST_BPF_SRC) $(TEST_CFLAGS) $(BPF_H)
	$(CC) $(TEST_CFLAGS) -c $^ -o $@

# Unit tests for utility functions compilation
$(TEST_UTILS_OBJ): $(TEST_UTILS_SRC) $(TEST_CFLAGS) $(UTILS_H)
	$(CC) $(TEST_CFLAGS) -c $^ -o $@

# Linking utility functions
utils.o: $(UTILS_OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@

# Linking main entry point
main.o: $(MAIN_OBJ)
	$(CC) $(CFLAGS) -c $^ -o $@

# Linking BPF program
bpf.ko: $(ELF_FILE) $(UTILS_OBJ) $(MAIN_OBJ)
	$(MAKE) -C /usr/src/linux-headers M=$(PWD) modules

# Test executable
test_bpf: $(TEST_BPF_OBJ) $(TEST_UTILS_OBJ) $(UTILS_OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Cleaning targets
clean:
	rm -f $(MAIN_OBJ) $(UTILS_OBJ) $(BPF_OBJ) $(TEST_BPF_OBJ) $(TEST_UTILS_OBJ) $(ELF_FILE) $(KMOD_FILE) $(TEST_EXEC)

# Configuration file loading
include $(CONFIG)

# Check for required dependencies
$(shell if ! command -v gcc &> /dev/null; then echo "gcc not found"; exit 1; fi)
$(shell if ! command -v make &> /dev/null; then echo "make not found"; exit 1; fi)
$(shell if ! test -d /usr/src/linux-headers; then echo "linux-headers not found"; exit 1; fi)
$(shell if ! test -f /usr/include/elf.h; then echo "libelf-dev not found"; exit 1; fi)