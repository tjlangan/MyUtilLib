#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common/data_types.h"

/**
 * @brief Creates a new Array.
 *
 * @param data_size Size of each element in bytes.
 * @param capacity Maximum capacity of the Array.
 *
 * @return ReturnArrayType will either return an ErrorCode or an Array*
 */
ReturnArray Array_create(size_t data_size, size_t capacity);

/**
 * @brief Destroys a Array and frees associated memory.
 *
 * @param arr Pointer to the Array to be destroyed.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_destroy(Array** arr);

/**
 * @brief Appends an element to the end of the Array.
 *
 * @param arr Pointer to the Array.
 * @param element Pointer to the element to be appended.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_append(Array* arr, T* element);

/**
 * @brief Inserts an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index at which the element will be inserted.
 * @param element The element to be inserted.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_insert(Array* arr, size_t index, T* element);

/**
 * @brief Removes an element at a specific index from the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be removed.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_remove(Array* arr, size_t index);

/**
 * @brief Retrieves an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be retrieved.
 *
 * @return ReturnData will return a struct contain an ErrorCode enum and a
 * GenericDataType pointer
 */
ReturnData Array_get(const Array* arr, size_t index);

/**
 * @brief Updates the value of an element at a specific index in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index Index of the element to be updated.
 * @param element Pointer to the new value for the element.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_set(Array* arr, size_t index, T* element);

/**
 * @brief Searches for an element in the Array and returns its index.
 *
 * @param arr Pointer to the Array.
 * @param element Pointer to the element to be searched for.
 *
 * @return The index of the first occurrence of the element, or SIZE_MAX if not
 * found.
 */
ReturnSizeT Array_find(const Array* arr, T* element);

/**
 * @brief Retrieves the current number of elements in the Array.
 *
 * @param arr Pointer to the Array.
 *
 * @return The current number of elements in the Array, or SIZE_MAX if arr is
 * NULL.
 */
ReturnSizeT Array_size(const Array* arr);

/**
 * @brief Retrieves the maximum capacity of the Array.
 *
 * @param arr Pointer to the Array.
 *
 * @return The maximum capacity of the Array, or SIZE_MAX if arr is NULL.
 */
ReturnSizeT Array_capacity(const Array* arr);

/**
 * @brief Checks if the Array is empty.
 *
 * @param arr Pointer to the Array.
 *
 * @return True if the Array is empty, false otherwise.
 */
ReturnBool Array_is_empty(const Array* arr);

/**
 * @brief Checks if the Array is full.
 *
 * @param arr Pointer to the Array.
 *
 * @return True if the Array is full, false otherwise.
 */
ReturnBool Array_is_full(const Array* arr);

/**
 * @brief Resizes the Array to a new capacity.
 *
 * @param arr Pointer to the Array.
 * @param new_capacity New capacity for the Array.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_resize(Array* arr, size_t new_capacity);

/**
 * @brief Clears all elements from the Array.
 *
 * @param arr Pointer to the Array.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_clear(Array* arr);

/**
 * @brief Iterates over the elements of the Array and applies a callback
 * function.
 *
 * @param arr Pointer to the Array.
 * @param callback Callback function to apply to each element.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_iterate(const Array* arr,
                          void (*callback)(const void* element));

/**
 * @brief Swaps the elements at two indices in the Array.
 *
 * @param arr Pointer to the Array.
 * @param index_a Index of the first element.
 * @param index_b Index of the second element.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_swap(Array* arr, size_t index_a, size_t index_b);

/**
 * @brief Sorts the elements of the Array based on a custom comparison
 * function.
 *
 * @param arr Pointer to the Array.
 * @param compare Comparison function for sorting elements.
 *
 * @return ReturnError will return an struct containing an ErrorCode enum
 */
ReturnError Array_sort(Array* arr, CompareFunction compare);

#endif
