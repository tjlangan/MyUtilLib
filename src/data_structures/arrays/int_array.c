#include "int_array.h"

Array* IntArray_create(size_t capacity) {
    ReturnArray result = Array_create(sizeof(int), capacity);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
    return result.arr;
}

void IntArray_destroy(Array** arr) {
    ReturnError result = Array_destroy(arr);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

void IntArray_append(Array* arr, int element) {
    ReturnError result = Array_append(arr, &(T){sizeof(int), &element});
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

void IntArray_insert(Array* arr, size_t index, int element) {
    ReturnError result = Array_insert(arr, index, &(T){sizeof(int), &element});
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

void IntArray_remove(Array* arr, size_t index) {
    ReturnError result = Array_remove(arr, index);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

int IntArray_get(const Array* arr, size_t index) {
    ReturnData result = Array_get(arr, index);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
    return *(int*)result.value->data;
}

void IntArray_set(Array* arr, size_t index, int element) {
    ReturnError result = Array_set(arr, index, &(T){sizeof(int), &element});
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

size_t IntArray_find(const Array* arr, int element) {
    ReturnSizeT result = Array_find(arr, &(T){sizeof(int), &element});
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
    return result.value;
}

size_t IntArray_size(const Array* arr) {
    ReturnSizeT result = Array_size(arr);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
    return result.value;
}

size_t IntArray_capacity(const Array* arr) {
    ReturnSizeT result = Array_capacity(arr);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
    return result.value;
}

bool IntArray_is_empty(const Array* arr) {
    ReturnBool result = Array_is_empty(arr);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
    return result.value;
}

bool IntArray_is_full(const Array* arr) {
    ReturnBool result = Array_is_full(arr);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
    return result.value;
}

void IntArray_resize(Array* arr, size_t new_capacity) {
    ReturnError result = Array_resize(arr, new_capacity);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

void IntArray_clear(Array* arr) {
    ReturnError result = Array_clear(arr);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

void IntArray_iterate(const Array* arr, CallbackFunction callback) {
    ReturnError result = Array_iterate(arr, callback);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

void IntArray_swap(Array* arr, size_t index_a, size_t index_b) {
    ReturnError result = Array_swap(arr, index_a, index_b);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

static int __compare__(const T* a, const T* b) {
    int int_a = *(const int*)a->data;
    int int_b = *(const int*)b->data;

    if (int_a < int_b) {
        return -1;  // a should come before b
    } else if (int_a > int_b) {
        return 1;  // a should come after b
    } else {
        return 0;  // a and b are equal
    }
}

void IntArray_sort(Array* arr) {
    ReturnError result = Array_sort(arr, __compare__);
    if (result.error > 0) {
        /**
         * TODO: Error handling
         */
    }
}

static void __print__(T* element) { printf("%d ", *(int*)element->data); }

void IntArray_print(Array* arr) { IntArray_iterate(arr, __print__); }
