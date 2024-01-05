#include "array.h"

ReturnArray Array_create(size_t data_size, size_t capacity) {
    ReturnArray result = {.error = NO_ERROR, .arr = NULL};

    // Check valid arguments
    if (data_size == 0 || capacity == 0) {
        result.error = ERROR;
        return result;
    }

    // Allocate memory and check for NULL
    Array* arr = (Array*)malloc(sizeof(Array));
    if (arr == NULL) {
        result.error = ERROR_ALLOCATION;
        return result;
    }

    // Assign arguments to array params
    arr->size = 0;
    arr->capacity = capacity;
    arr->data_size = data_size;

    // Allocate memory and check for NULL
    arr->values = (T*)malloc(capacity * sizeof(T));
    if (arr->values == NULL) {
        result.error = ERROR_ALLOCATION;
        free(arr);
        return result;
    }

    // For each element in array allocate memory and check for NULL
    for (size_t i = 0; i < capacity; i++) {
        arr->values[i].size = data_size;
        arr->values[i].data = malloc(data_size);
        if (arr->values[i].data == NULL) {
            result.error = ERROR_ALLOCATION;

            // Free allocated memory
            for (size_t j = 0; j < i; j++) {
                free(arr->values[j].data);
            }
            free(arr->values);
            free(arr);
            return result;
        }
    }

    // Everything went good
    result.arr = arr;

    return result;
}

ReturnError Array_destroy(Array** arr) {
    ReturnError result = {.error = NO_ERROR};

    if (*arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    for (size_t i = 0; i < (*arr)->capacity; i++) {
        free((*arr)->values[i].data);
    }
    free((*arr)->values);
    free(*arr);
    *arr = NULL;

    return result;
}

ReturnError Array_append(Array* arr, T* element) {
    ReturnError result = {.error = NO_ERROR};

    // Check if array or element is NULL
    if (arr == NULL || element == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    // Check if array is full and check for errors
    ReturnBool is_full_result = Array_is_full(arr);
    if (is_full_result.error > 0) {
        result.error = is_full_result.error;
        return result;
    }

    // If array is full, resize it and check for errors
    if (is_full_result.value == true) {
        ReturnError resize_result = Array_resize(arr, arr->capacity * 2 + 1);
        if (resize_result.error > 0) {
            result.error = resize_result.error;
            return result;
        }
    }

    // Set the last value in the array to the element and check for errors
    ReturnError set_result = Array_set(arr, arr->size, element);
    if (set_result.error > 0) {
        result.error = set_result.error;
        return result;
    }

    // increment size counter
    arr->size += 1;

    return result;
}

ReturnError Array_insert(Array* arr, size_t index, T* element) {
    ReturnError result = {.error = NO_ERROR};

    // Check if array or element is NULL
    if (arr == NULL || element == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    // Check index is in bounds
    if (index > arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    // Check if array is full
    ReturnBool is_full_result = Array_is_full(arr);
    if (is_full_result.error > 0) {
        result.error = is_full_result.error;
        return result;
    }

    // if array is full resize it
    if (is_full_result.value == true) {
        ReturnError resize_result = Array_resize(arr, arr->capacity * 2 + 1);
        if (resize_result.error > 0) {
            result.error = resize_result.error;
            return result;
        }
    }

    ReturnData get_result;
    ReturnError set_result;

    // Loop starting at end shifting elements to the right
    for (size_t i = arr->size; i > index; i--) {
        get_result = Array_get(arr, i - 1);
        if (get_result.error > 0) {
            result.error = get_result.error;
            return result;
        }
        set_result = Array_set(arr, i, get_result.value);
        if (set_result.error > 0) {
            result.error = set_result.error;
            return result;
        }
    }

    // Set the element at specified index
    set_result = Array_set(arr, index, element);
    if (set_result.error > 0) {
        result.error = set_result.error;
        return result;
    }

    // increment counter
    arr->size += 1;

    return result;
}

ReturnError Array_remove(Array* arr, size_t index) {
    ReturnError result = {.error = NO_ERROR};

    // Check if array is null
    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    if (index >= arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    ReturnData get_result;
    ReturnError set_result;

    // Loop start at index and shift to left
    for (size_t i = index; i < arr->size - 1; i++) {
        get_result = Array_get(arr, i + 1);
        if (get_result.error > 0) {
            result.error = get_result.error;
            return result;
        }
        set_result = Array_set(arr, i, get_result.value);
        if (set_result.error > 0) {
            result.error = set_result.error;
            return result;
        }
    }

    // idk if this will work
    T temp;
    temp.size = arr->data_size;
    temp.data = &(int){0};

    set_result = Array_set(arr, arr->size - 1, &temp);
    if (set_result.error > 0) {
        result.error = set_result.error;
        return result;
    }

    // decrement size counter
    arr->size -= 1;

    return result;
}

ReturnData Array_get(const Array* arr, size_t index) {
    ReturnData result = {.error = NO_ERROR, .value = NULL};

    if (arr == NULL || arr->values == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    if (index >= arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    // who tf knows
    // return &((const char*)arr->data)[index * arr->data_size];
    result.value = &(arr->values[index]);

    return result;
}

ReturnError Array_set(Array* arr, size_t index, T* element) {
    ReturnError result = {.error = NO_ERROR};

    if (arr == NULL || element == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    if (index >= arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    if (element->size != arr->data_size) {
        result.error = ERROR;
        return result;
    }

    arr->values[index].size = element->size;
    memcpy(arr->values[index].data, element->data, element->size);

    return result;

    // if (arr != NULL && arr->data != NULL && index <= arr->size) {
    //     memcpy(&((char*)arr->data)[index * arr->data_size], element,
    //            arr->data_size);
    // }
}

ReturnSizeT Array_find(const Array* arr, T* element) {
    ReturnSizeT result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL || arr->values == NULL || element == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    for (size_t i = 0; i < arr->size; i++) {
        if (memcmp(&(arr->values[i]), element, arr->data_size) == 0) {
            result.value = i;
            break;
        }
    }

    // Assume nobody has a 18 quintillion long array
    if (result.value == SIZE_MAX) {
        result.error = ERROR_NOT_FOUND;
    }

    return result;
}

ReturnSizeT Array_size(const Array* arr) {
    ReturnSizeT result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    result.value = arr->size;
    return result;
}

ReturnSizeT Array_capacity(const Array* arr) {
    ReturnSizeT result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    result.value = arr->capacity;
    return result;
}

ReturnBool Array_is_empty(const Array* arr) {
    ReturnBool result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    result.value = arr->size == 0;
    return result;
}

ReturnBool Array_is_full(const Array* arr) {
    ReturnBool result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    result.value = arr->size == arr->capacity;
    return result;
}

ReturnError Array_resize(Array* arr, size_t new_capacity) {
    if (arr != NULL) {
        if (new_capacity < arr->size) {
            arr->size = new_capacity;
        }

        void* new_data = realloc(arr->data, new_capacity * arr->data_size);
        if (new_data != NULL) {
            arr->data = new_data;
            arr->capacity = new_capacity;
        } else {
            // TODO
            fprintf(stderr,
                    "Array_resize Failed! Could not realloc to "
                    "new_capacity = %ld",
                    new_capacity);
        }
    }
}

void Array_clear(Array* arr) {
    if (arr != NULL && arr->data != NULL) {
        free(arr->data);
        arr->data = NULL;
        arr->size = 0;
        arr->capacity = 0;
    }
}

void Array_iterate(const Array* arr, void (*callback)(const void* element)) {
    if (arr != NULL && callback != NULL) {
        for (size_t i = 0; i < arr->size; i++) {
            const void* element = Array_get(arr, i);
            callback(element);
        }
    }
}

void Array_swap(Array* arr, size_t index_a, size_t index_b) {
    if (arr != NULL && index_a < arr->size && index_b < arr->size) {
        void* temp = malloc(arr->data_size);
        memcpy(temp, Array_get(arr, index_a), arr->data_size);

        Array_set(arr, index_a, Array_get(arr, index_b));
        Array_set(arr, index_b, temp);

        free(temp);
    }
}

static size_t partition(Array* arr, size_t low, size_t high,
                        CompareFunction compare) {
    const void* pivot = Array_get(arr, high);
    size_t i = low - 1;

    for (size_t j = low; j < high; j++) {
        if (compare(Array_get(arr, j), pivot) < 0) {
            i++;
            Array_swap(arr, i, j);
        }
    }

    Array_swap(arr, i + 1, high);
    return i + 1;
}

static void quick_sort(Array* arr, size_t low, size_t high,
                       CompareFunction compare) {
    if (low < high) {
        size_t pi = partition(arr, low, high, compare);

        if (pi > 0) {
            quick_sort(arr, low, pi - 1, compare);
        }

        quick_sort(arr, pi + 1, high, compare);
    }
}

void Array_sort(Array* arr, CompareFunction compare) {
    if (arr != NULL && compare != NULL) {
        quick_sort(arr, 0, arr->size - 1, compare);
    }
}