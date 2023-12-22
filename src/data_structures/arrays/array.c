#include "array.h"

/**
 * @brief Creates a new Array.
 *
 * @param data_size Size of each element in bytes.
 * @param capacity Maximum capacity of the Array.
 * @return A pointer to the newly created Array, or NULL on failure.
 */
Array* Array_create(size_t data_size, size_t capacity) {
    if (data_size == 0 || capacity == 0) {
        return NULL;
    }
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->data_size = data_size;
    arr->size = 0;
    arr->capacity = capacity;
    arr->data = malloc(data_size * capacity);

    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    return arr;
}

/**
 * @brief Destroys a Array and frees associated memory.
 *
 * @param arr Pointer to the Array to be destroyed.
 */
void Array_destroy(Array** arr) {
    if (*arr != NULL) {
        free((*arr)->data);
        free(*arr);
        *arr = NULL;
    }
}

/**
 * @brief Appends an element to the end of the Array.
 *
 * @param arr Pointer to the Array.
 * @param element Pointer to the element to be appended.
 */
void Array_append(Array* arr, const void* element) {
    if (arr != NULL) {
        if (Array_is_full(arr)) {
            Array_resize(arr, arr->capacity * 2 + 1);
        }
        Array_set(arr, arr->size, element);
        arr->size += 1;
    }
}

/**
 * @brief Inserts an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index at which the element will be inserted.
 * @param element Pointer to the element to be inserted.
 */
void Array_insert(Array* arr, size_t index, const void* element) {
    if (arr != NULL && index <= arr->size) {
        if (Array_is_full(arr)) {
            Array_resize(arr, arr->capacity * 2 + 1);
        }

        for (size_t i = arr->size; i > index; i--) {
            Array_set(arr, i, Array_get(arr, i - 1));
        }

        Array_set(arr, index, element);
        arr->size += 1;
    }
}

/**
 * @brief Removes an element at a specific index from the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be removed.
 */
void Array_remove(Array* arr, size_t index) {
    if (arr != NULL && index < arr->size) {
        for (size_t i = index; i < arr->size - 1; i++) {
            Array_set(arr, i, Array_get(arr, i + 1));
        }

        Array_set(arr, arr->size - 1, &(int){0});
        arr->size -= 1;
    }
}

/**
 * @brief Retrieves an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be retrieved.
 * @return A pointer to the retrieved element, or NULL if the index is out of
 * bounds.
 */
const void* Array_get(const Array* arr, size_t index) {
    if (arr == NULL || arr->data == NULL || index >= arr->size) {
        fprintf(
            stderr,
            "Array_get Failed! Return value is NULL. Attempted index = %ld\n",
            index);
        return NULL;
    }
    return &((const char*)arr->data)[index * arr->data_size];
}

/**
 * @brief Updates the value of an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be updated.
 * @param element Pointer to the new value for the element.
 */
void Array_set(Array* arr, size_t index, const void* element) {
    if (arr != NULL && arr->data != NULL && index <= arr->size) {
        memcpy(&((char*)arr->data)[index * arr->data_size], element,
               arr->data_size);
    }
}

/**
 * @brief Searches for an element in the Array and returns its index.
 *
 * @param arr Pointer to the Array.
 * @param element Pointer to the element to be searched for.
 * @return The index of the first occurrence of the element, or SIZE_MAX if not
 * found.
 */
size_t Array_find(const Array* arr, const void* element) {
    if (arr == NULL || arr->data == NULL || element == NULL) {
        return SIZE_MAX;
    }
    for (size_t i = 0; i < arr->size; i++) {
        if (memcmp(&((char*)arr->data)[i * arr->data_size], element,
                   arr->data_size) == 0) {
            return i;
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Retrieves the current number of elements in the Array.
 *
 * @param arr Pointer to the Array.
 * @return The current number of elements in the Array, or SIZE_MAX if arr is
 * NULL.
 */
size_t Array_size(const Array* arr) {
    return (arr != NULL) ? arr->size : SIZE_MAX;
}

/**
 * @brief Retrieves the maximum capacity of the Array.
 *
 * @param arr Pointer to the Array.
 * @return The maximum capacity of the Array, or SIZE_MAX if arr is NULL.
 */
size_t Array_capacity(const Array* arr) {
    return (arr != NULL) ? arr->capacity : SIZE_MAX;
}

/**
 * @brief Checks if the Array is empty.
 *
 * @param arr Pointer to the Array.
 * @return True if the Array is empty, false otherwise.
 */
bool Array_is_empty(const Array* arr) {
    return (arr != NULL) ? (arr->size == 0) : false;
}

/**
 * @brief Checks if the Array is full.
 *
 * @param arr Pointer to the Array.
 * @return True if the Array is full, false otherwise.
 */
bool Array_is_full(const Array* arr) {
    return (arr != NULL) ? (arr->size == arr->capacity) : false;
}

/**
 * @brief Resizes the Array to a new capacity.
 *
 * @param arr Pointer to the Array.
 * @param new_capacity New capacity for the Array.
 */
void Array_resize(Array* arr, size_t new_capacity) {
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
            fprintf(
                stderr,
                "Array_resize Failed! Could not realloc to new_capacity = %ld",
                new_capacity);
        }
    }
}

/**
 * @brief Clears all elements from the Array. Frees memory associated with
 * Array.data
 *
 * @param arr Pointer to the Array.
 */
void Array_clear(Array* arr) {
    if (arr != NULL && arr->data != NULL) {
        free(arr->data);
        arr->data = NULL;
        arr->size = 0;
        arr->capacity = 0;
    }
}

/**
 * @brief Iterates over the elements of the Array and applies a callback
 * function.
 *
 * @param arr Pointer to the Array.
 * @param callback Callback function to apply to each element.
 */
void Array_iterate(const Array* arr, void (*callback)(const void* element)) {
    if (arr != NULL && callback != NULL) {
        for (size_t i = 0; i < arr->size; i++) {
            const void* element = Array_get(arr, i);
            callback(element);
        }
    }
}

/**
 * @brief Swaps the elements at two indices in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index_a Index of the first element.
 * @param index_b Index of the second element.
 */
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

/**
 * @brief Sorts the elements of the Array based on a custom comparison
 * function.
 *
 * @param arr Pointer to the Array.
 * @param compare Comparison function for sorting elements.
 */
void Array_sort(Array* arr, CompareFunction compare) {
    if (arr != NULL && compare != NULL) {
        quick_sort(arr, 0, arr->size - 1, compare);
    }
}