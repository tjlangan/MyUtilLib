#include <stdio.h>

#include "test_array.h"
#include "test_list.h"

int main() {
    printf("Testing Arrays...\n");
    test_array();
    // test_int_array();
    // test_struct_array();
    printf("Array tests pass!\n");

    printf("Testing Linked Lists...\n");
    // test_list();
    // test_int_list();
    printf("Linked List tests pass!\n");

    return 0;
}