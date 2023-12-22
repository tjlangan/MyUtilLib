#include "int_array.h"

/**
 * @brief Creates a new Array for ints
 *
 * @param capacity Maximum capacity of the Array.
 * @return A pointer to the newly created Array, or NULL on failure.
 */
Array* IntArray_create(size_t capacity) {
    return Array_create(sizeof(int), capacity);
}

/**
 * @brief Destroys a Array and frees associated memory.
 *
 * @param arr Pointer to the Array to be destroyed.
 */
void IntArray_destroy(Array** arr) { Array_destroy(arr); }

/**
 * @brief Appends an element to the end of the Array.
 *
 * @param arr Pointer to the Array.
 * @param element The element to be appended.
 */
void IntArray_append(Array* arr, const int element) {
    Array_append(arr, &element);
}

/**
 * @brief Inserts an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index at which the element will be inserted.
 * @param element The element to be inserted.
 */
void IntArray_insert(Array* arr, size_t index, const int element) {
    Array_insert(arr, index, &element);
}

/**
 * @brief Removes an element at a specific index from the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be removed.
 */
void IntArray_remove(Array* arr, size_t index) { Array_remove(arr, index); }

/**
 * @brief Retrieves an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be retrieved.
 * @return The retrieved element, or NULL if the index is out of
 * bounds.
 */
int IntArray_get(const Array* arr, size_t index) {
    return *(int*)Array_get(arr, index);
}

/**
 * @brief Updates the value of an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be updated.
 * @param element Pointer to the new value for the element.
 */
void IntArray_set(Array* arr, size_t index, const int element) {
    Array_set(arr, index, &element);
}

/**
 * @brief Searches for an element in the Array and returns its index.
 *
 * @param arr Pointer to the Array.
 * @param element Pointer to the element to be searched for.
 * @return The index of the first occurrence of the element, or SIZE_MAX if not
 * found.
 */
size_t IntArray_find(const Array* arr, const int element) {
    return Array_find(arr, &element);
}

/**
 * @brief Retrieves the current number of elements in the Array.
 *
 * @param arr Pointer to the Array.
 * @return The current number of elements in the Array, or SIZE_MAX if arr is
 * NULL.
 */
size_t IntArray_size(const Array* arr) { return Array_size(arr); }

/**
 * @brief Retrieves the maximum capacity of the Array.
 *
 * @param arr Pointer to the Array.
 * @return The maximum capacity of the Array, or SIZE_MAX if arr is NULL.
 */
size_t IntArray_capacity(const Array* arr) { return Array_capacity(arr); }

/**
 * @brief Checks if the Array is empty.
 *
 * @param arr Pointer to the Array.
 * @return True if the Array is empty, false otherwise.
 */
bool IntArray_is_empty(const Array* arr) { return Array_is_empty(arr); }

/**
 * @brief Checks if the Array is full.
 *
 * @param arr Pointer to the Array.
 * @return True if the Array is full, false otherwise.
 */
bool IntArray_is_full(const Array* arr) { return Array_is_full(arr); }

/**
 * @brief Resizes the Array to a new capacity.
 *
 * @param arr Pointer to the Array.
 * @param new_capacity New capacity for the Array.
 */
void IntArray_resize(Array* arr, size_t new_capacity) {
    Array_resize(arr, new_capacity);
}

/**
 * @brief Clears all elements from the Array.
 *
 * @param arr Pointer to the Array.
 */
void IntArray_clear(Array* arr) { Array_clear(arr); }

/**
 * @brief Iterates over the elements of the Array and applies a callback
 * function.
 *
 * @param arr Pointer to the Array.
 * @param callback Callback function to apply to each element.
 */
void IntArray_iterate(const Array* arr, void (*callback)(const void* element)) {
    Array_iterate(arr, callback);
}

/**
 * @brief Swaps the elements at two indices in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index_a Index of the first element.
 * @param index_b Index of the second element.
 */
void IntArray_swap(Array* arr, size_t index_a, size_t index_b) {
    Array_swap(arr, index_a, index_b);
}

static int __compare(const void* a, const void* b) {
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

/**
 * @brief Sorts the elements of the Array
 *
 * @param arr Pointer to the Array.
 */
void IntArray_sort(Array* arr) { Array_sort(arr, __compare); }

static void __print(const void* element) { printf("%d ", *(int*)element); }

void IntArray_print(Array* arr) { IntArray_iterate(arr, __print); }
