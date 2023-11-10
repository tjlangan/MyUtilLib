#include "array.h"

#include <stdlib.h>

Array* create(unsigned int capacity) {
    if (capacity == 0) {
        capacity = 2;
    }
    Array* arr = (Array*)malloc(sizeof(Array) + capacity * sizeof(int));

    if (arr != NULL) {
        arr->capacity = capacity;
        arr->count = 0;
        arr->error = false;
    }
    return arr;
}

int destroy(Array** arr) {
    if (*arr != NULL) {
        free(*arr);
        *arr = NULL;
        return 0;
    }
    return -1;
}

bool is_empty(Array* arr) {
    if (arr == NULL) {
        return true;
    }
    return arr->count == 0;
}

bool is_full(Array* arr) {
    if (arr == NULL) {
        return false;
    }
    return arr->count == arr->capacity;
}

bool in_bounds(Array* arr, unsigned int index) {
    if (arr == NULL) {
        return false;
    }
    return index < arr->capacity;
}

int get_count(Array* arr) {
    if (arr == NULL) {
        return -1;
    }
    return arr->count;
}

int get_capacity(Array* arr) {
    if (arr == NULL) {
        return -1;
    }
    return arr->capacity;
}

bool get_error(Array* arr) {
    if (arr == NULL) {
        return true;
    }
    return arr->error;
}

int first(Array* arr) { return value_at(arr, 0); }

int last(Array* arr) { return value_at(arr, arr->count - 1); }

int index_of(Array* arr, int value) {
    arr->error = false;

    if (arr == NULL) {
        arr->error = true;
        return -1;
    }

    int temp = 0;
    for (unsigned int i = 0; i < arr->count; i++) {
        temp = value_at(arr, i);
        if (arr->error) {
            break;
        }
        if (value == temp) {
            return i;
        }
    }

    return -1;
}

int value_at(Array* arr, unsigned int index) {
    arr->error = false;

    if (arr == NULL || !in_bounds(arr, index) || index >= arr->count) {
        arr->error = true;
        return -1;
    }

    return arr->values[index];
}

int insert_at(Array* arr, unsigned int index, int value) {
    arr->error = false;

    if (arr == NULL || !in_bounds(arr, index) || index >= arr->count) {
        arr->error = true;
        return -1;
    }

    arr->values[index] = value;
    return 0;
}

int remove_at(Array* arr, unsigned int index) {
    arr->error = false;

    if (arr == NULL || !in_bounds(arr, index) || index >= arr->count) {
        arr->error = true;
        return -1;
    }

    for (unsigned int i = index; i < arr->count - 1; i++) {
        arr->values[i] = value_at(arr, i + 1);
    }

    arr->count -= 1;
    return 0;
}

int append(Array* arr, int value) {
    arr->error = false;

    if (arr == NULL) {
        arr->error = true;
        return -1;
    }

    if (!in_bounds(arr, arr->count)) {
        increase_capacity(arr);
        if (arr->error) {
            return -1;
        }
    }

    arr->count += 1;
    return insert_at(arr, arr->count - 1, value);
}

int swap(Array* arr, unsigned int index_a, unsigned int index_b) {
    arr->error = false;

    if (arr == NULL) {
        arr->error = true;
        return -1;
    }

    int value_a = value_at(arr, index_a);
    if (arr->error) {
        return -1;
    }

    int value_b = value_at(arr, index_b);
    if (arr->error) {
        return -1;
    }

    insert_at(arr, index_a, value_b);
    insert_at(arr, index_b, value_a);

    if (arr->error) {
        return -1;
    }

    return 0;
}

int fill(Array* arr, int value) {
    arr->error = false;

    if (arr == NULL) {
        arr->error = true;
        return -1;
    }

    for (unsigned int i = 0; i < arr->count; i++) {
        insert_at(arr, i, value);
        if (arr->error) {
            return -1;
        }
    }
    return 0;
}

int increase_capacity(Array* arr) {
    arr->error = false;

    if (arr == NULL) {
        arr->error = true;
        return -1;
    }
    unsigned int new_capacity = arr->capacity * 2;
    int* new_values = (int*)malloc(new_capacity * sizeof(int));

    if (new_values == NULL) {
        free(new_values);
        arr->error = true;
        return -1;
    }

    for (size_t i = 0; i < arr->count; i++) {
        new_values[i] = value_at(arr, i);
    }

    free(arr->values);

    arr->values = new_values;
    arr->capacity = new_capacity;
    return 0;
}
