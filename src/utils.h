#ifndef _UTILS_H_
#define _UTILS_H_

/**
 * @file utils.h
 * @brief Header file for utility functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "bpf.h"

/**
 * @defgroup utils Utility Functions
 * @{
 */

/**
 * @brief Checks if a file exists
 * @param filename Name of the file to check
 * @return true if file exists, false otherwise
 */
bool utils_file_exists(const char *filename);

/**
 * @brief Reads a file into a buffer
 * @param filename Name of the file to read
 * @param buf Pointer to buffer to read into
 * @param size Size of buffer
 * @return true if successful, false otherwise
 */
bool utils_read_file(const char *filename, char *buf, size_t size);

/**
 * @brief Writes a buffer to a file
 * @param filename Name of the file to write to
 * @param buf Pointer to buffer to write
 * @param size Size of buffer
 * @return true if successful, false otherwise
 */
bool utils_write_file(const char *filename, const char *buf, size_t size);

/**
 * @brief Converts a hexadecimal string to an integer
 * @param hex_string Hexadecimal string to convert
 * @param num Pointer to integer to store result
 * @return true if successful, false otherwise
 */
bool utils_hex_to_int(const char *hex_string, uint64_t *num);

/**
 * @brief Prints a message to stderr
 * @param format Format string
 * @param ... Arguments to print
 */
void utils_print_err(const char *format, ...);

/**
 * @}
 */

#endif /* _UTILS_H_ */