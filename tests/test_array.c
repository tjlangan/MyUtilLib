#include <assert.h>
#include <stdio.h>

#include "../src/data_structures/arrays/array.h"

void print_arr(const void* element) { printf("%d ", *((int*)element)); }
void double_int(const void* element) { *((int*)element) *= 2; }
int compare_int(const void* a, const void* b) {
    int int_a = *((const int*)a);
    int int_b = *((const int*)b);

    if (int_a < int_b) {
        return -1;  // a should come before b
    } else if (int_a > int_b) {
        return 1;  // a should come after b
    } else {
        return 0;  // a and b are equal
    }
}

void test_array(void) {
    // Test creation
    Array* arr = Array_create(sizeof(int), 5);
    assert(arr != NULL);
    assert(arr->capacity == 5);
    assert(arr->data != NULL);
    assert(arr->size == 0);
    assert(arr->data_size == sizeof(int));

    // Test basics
    assert(Array_size(arr) == 0);
    assert(Array_capacity(arr) == 5);
    assert(Array_is_empty(arr) == true);
    assert(Array_is_full(arr) == false);

    // Test appending
    Array_append(arr, &(int){42});  // {42}
    assert(Array_size(arr) == 1);
    assert(*((int*)Array_get(arr, 0)) == 42);

    // Test inserting
    Array_insert(arr, 0, &(int){7});  // insert in front {7, 42}
    Array_insert(arr, Array_size(arr),
                 &(int){98});          // insert at back {7, 42, 98}
    Array_insert(arr, 1, &(int){15});  // insert in middle {7, 15, 42 98}
    assert(Array_size(arr) == 4);
    assert(*((int*)Array_get(arr, 0)) == 7);
    assert(*((int*)Array_get(arr, Array_size(arr) - 1)) == 98);
    assert(*((int*)Array_get(arr, 1)) == 15);

    // Test removing

    Array_remove(arr, 1);                    // remove middle {7, 42, 98}
    Array_remove(arr, Array_size(arr) - 1);  // remove back {7, 42}
    Array_remove(arr, 0);                    // remove front {42}

    assert(Array_size(arr) == 1);
    assert(*((int*)Array_get(arr, 0)) == 42);

    // Test setting
    Array_set(arr, 0, &(int){99});
    assert(Array_size(arr) == 1);
    assert(*((int*)Array_get(arr, 0)) == 99);

    // Test clearing
    Array_clear(arr);
    assert(arr != NULL);
    assert(Array_size(arr) == 0);
    assert(Array_capacity(arr) == 0);

    int vals[] = {37, -12, 94, 0, -56, 789, 23, -987, 456, -72};
    int sorted[] = {-987, -72, -56, -12, 0, 23, 37, 94, 456, 789};
    int doubled[] = {-1974, -144, -112, -24, 0, 46, 74, 188, 912, 1578};

    // Test adding a bunch of vals
    for (size_t i = 0; i < 10; i++) {
        Array_append(arr, &vals[i]);
        assert(Array_size(arr) == (i + 1));
        assert(*((int*)Array_get(arr, i)) == vals[i]);
    }

    // Test find
    assert(Array_find(arr, &(int){23}) == 6);

    // Test sort
    Array_sort(arr, compare_int);
    for (size_t i = 0; i < 10; i++) {
        assert(*((int*)Array_get(arr, i)) == sorted[i]);
    }

    // Test iterate
    Array_iterate(arr, double_int);
    for (size_t i = 0; i < 10; i++) {
        assert(*((int*)Array_get(arr, i)) == doubled[i]);
    }
}

int main(void) {
    // Run test functions
    test_array();

    printf("Looks good\n");

    return 0;
}
