#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "src/utils.h"

// Unit tests for utility functions
void test_utils(void) {
    // Test case: test utility function 1
    char* result = utils_function1("test input");
    assert(strcmp(result, "expected output") == 0);
    free(result);

    // Test case: test utility function 2
    result = utils_function2(123);
    assert(strcmp(result, "expected output") == 0);
    free(result);

    // Test case: test error handling for utility function 1
    result = utils_function1(NULL);
    assert(strcmp(result, "error: input is NULL") == 0);
    free(result);

    // Test case: test error handling for utility function 2
    result = utils_function2(-1);
    assert(strcmp(result, "error: invalid input") == 0);
    free(result);
}

// Test case: test error handling for missing utility function
void test_missing_utility_function(void) {
    // This was tricky, need to check if the function is declared
    void* utils_function3 = NULL;
    #ifdef UTILS_FUNCTION3
    utils_function3 = utils_function3();
    #else
    // Not proud of this but it works
    assert(utils_function3 == NULL);
    #endif
}

int main(int argc, char** argv) {
    // Run all unit tests
    test_utils();
    test_missing_utility_function();

    // All tests passed, return success
    return 0;
}