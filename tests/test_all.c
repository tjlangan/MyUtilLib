#include <stdio.h>

#include "test_array.h"

int main() {
    printf("Testing Arrays...\n");
    test_array();
    test_int_array();
    test_struct_array();
    printf("Array tests pass!\n");

    return 0;
}