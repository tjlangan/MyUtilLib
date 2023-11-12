#include <assert.h>
#include <stdio.h>

#include "../src/data_structures/array.h"

void print_arr(const void* element) { printf("%d ", *((int*)element)); }

int main(void) {
    // Run test functions

    Array* arr = Array_create(sizeof(int), 5);
    for (int i = 0; i < 5; i++) {
        Array_append(arr, &i);
    }

    Array_iterate(arr, print_arr);
    printf("\n No Errors\n");

    return 0;
}
