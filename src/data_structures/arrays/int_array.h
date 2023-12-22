#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include "array.h"

/**
 * @brief Creates a new Array for ints
 *
 * @param capacity Maximum capacity of the Array.
 * @return A pointer to the newly created Array, or NULL on failure.
 */
Array* IntArray_create(size_t capacity);

/**
 * @brief Destroys a Array and frees associated memory.
 *
 * @param arr Pointer to the Array to be destroyed.
 */
void IntArray_destroy(Array** arr);

/**
 * @brief Appends an element to the end of the Array.
 *
 * @param arr Pointer to the Array.
 * @param element The element to be appended.
 */
void IntArray_append(Array* arr, const int element);

/**
 * @brief Inserts an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index at which the element will be inserted.
 * @param element The element to be inserted.
 */
void IntArray_insert(Array* arr, size_t index, const int element);

/**
 * @brief Removes an element at a specific index from the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be removed.
 */
void IntArray_remove(Array* arr, size_t index);

/**
 * @brief Retrieves an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be retrieved.
 * @return The retrieved element, or NULL if the index is out of
 * bounds.
 */
int IntArray_get(const Array* arr, size_t index);

/**
 * @brief Updates the value of an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be updated.
 * @param element Pointer to the new value for the element.
 */
void IntArray_set(Array* arr, size_t index, const int element);

/**
 * @brief Searches for an element in the Array and returns its index.
 *
 * @param arr Pointer to the Array.
 * @param element Pointer to the element to be searched for.
 * @return The index of the first occurrence of the element, or SIZE_MAX if not
 * found.
 */
size_t IntArray_find(const Array* arr, const int element);

/**
 * @brief Retrieves the current number of elements in the Array.
 *
 * @param arr Pointer to the Array.
 * @return The current number of elements in the Array, or SIZE_MAX if arr is
 * NULL.
 */
size_t IntArray_size(const Array* arr);

/**
 * @brief Retrieves the maximum capacity of the Array.
 *
 * @param arr Pointer to the Array.
 * @return The maximum capacity of the Array, or SIZE_MAX if arr is NULL.
 */
size_t IntArray_capacity(const Array* arr);

/**
 * @brief Checks if the Array is empty.
 *
 * @param arr Pointer to the Array.
 * @return True if the Array is empty, false otherwise.
 */
bool IntArray_is_empty(const Array* arr);

/**
 * @brief Checks if the Array is full.
 *
 * @param arr Pointer to the Array.
 * @return True if the Array is full, false otherwise.
 */
bool IntArray_is_full(const Array* arr);

/**
 * @brief Resizes the Array to a new capacity.
 *
 * @param arr Pointer to the Array.
 * @param new_capacity New capacity for the Array.
 */
void IntArray_resize(Array* arr, size_t new_capacity);

/**
 * @brief Clears all elements from the Array.
 *
 * @param arr Pointer to the Array.
 */
void IntArray_clear(Array* arr);

/**
 * @brief Iterates over the elements of the Array and applies a callback
 * function.
 *
 * @param arr Pointer to the Array.
 * @param callback Callback function to apply to each element.
 */
void IntArray_iterate(const Array* arr, void (*callback)(const int* element));

/**
 * @brief Swaps the elements at two indices in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index_a Index of the first element.
 * @param index_b Index of the second element.
 */
void IntArray_swap(Array* arr, size_t index_a, size_t index_b);

/**
 * @brief Sorts the elements of the Array
 *
 * @param arr Pointer to the Array.
 */
void IntArray_sort(Array* arr);

void IntArray_print(Array* arr);

#endif