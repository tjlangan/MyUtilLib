#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

/**
 * @file array.h
 *
 * @brief This header file defines a dynamic array module for integer elements.
 *
 * The dynamic array supports various operations, including creation,
 * destruction, element insertion and removal, capacity management, and utility
 * functions.
 */

/**
 * @struct Array_t
 *
 * @brief Represents a dynamic array of integers.
 *
 * The Array_t structure includes information about the array's current count,
 * capacity, error status, and a pointer to the array's data.
 */
typedef struct Array_t {
    unsigned int count;    /**< Number of elements currently in the array. */
    unsigned int capacity; /**< Total capacity of the array. */
    bool error;            /**< Flag indicating an error condition. */
    int* values;           /**< Pointer to the array's data. */
} Array;

/**
 * @brief Create a new array with the given capacity.
 *
 * This function allocates memory for a new array with the specified initial
 * capacity. If the specified capacity is 0, a default capacity of 2 is used.
 *
 * @param capacity The initial capacity of the array.
 * @return A pointer to the newly created array, or NULL if an error occurs.
 */
Array* create(unsigned int capacity);

/**
 * @brief Destroy an array and free its memory.
 *
 * This function deallocates the memory occupied by the array and sets the
 * provided pointer to NULL after destruction.
 *
 * @param arr A pointer to the array to be destroyed. The pointer is set to NULL
 * after destruction.
 * @return 0 on success, -1 on failure.
 */
int destroy(Array** arr);

/**
 * @brief Check if the array is empty.
 *
 * This function returns true if the array is empty (count is 0), false
 * otherwise.
 *
 * @param arr A pointer to the array.
 * @return true if the array is empty, false otherwise.
 */
bool is_empty(Array* arr);

/**
 * @brief Check if the array is full.
 *
 * This function returns true if the array is full (count equals capacity),
 * false otherwise.
 *
 * @param arr A pointer to the array.
 * @return true if the array is full, false otherwise.
 */
bool is_full(Array* arr);

/**
 * @brief Check if a given index is within bounds of the array.
 *
 * This function returns true if the specified index is within the valid bounds
 * of the array, false otherwise.
 *
 * @param arr A pointer to the array.
 * @param index The index to check.
 * @return true if the index is within bounds, false otherwise.
 */
bool in_bounds(Array* arr, unsigned int index);

/**
 * @brief Get the number of elements in the array.
 *
 * @param arr A pointer to the array.
 * @return The number of elements in the array, or -1 if the array is NULL.
 */
int get_count(Array* arr);

/**
 * @brief Get the total capacity of the array.
 *
 * @param arr A pointer to the array.
 * @return The total capacity of the array, or -1 if the array is NULL.
 */
int get_capacity(Array* arr);

/**
 * @brief Get the error status of the array.
 *
 * @param arr A pointer to the array.
 * @return The error status of the array, or true if the array is NULL.
 */
bool get_error(Array* arr);

/**
 * @brief Get the first element of the array.
 *
 * This function returns the value of the first element in the array.
 *
 * @param arr A pointer to the array.
 * @return The value of the first element, or -1 if the array is empty or NULL.
 */
int first(Array* arr);

/**
 * @brief Get the last element of the array.
 *
 * This function returns the value of the last element in the array.
 *
 * @param arr A pointer to the array.
 * @return The value of the last element, or -1 if the array is empty or NULL.
 */
int last(Array* arr);

/**
 * @brief Find the index of the first occurrence of a value in the array.
 *
 * This function searches for the specified value in the array and returns the
 * index of the first occurrence. If the value is not found, it returns -1.
 *
 * @param arr A pointer to the array.
 * @param value The value to search for.
 * @return The index of the first occurrence of the value, or -1 if not found.
 */
int index_of(Array* arr, int value);

/**
 * @brief Get the value at a specific index in the array.
 *
 * This function returns the value at the specified index in the array.
 *
 * @param arr A pointer to the array.
 * @param index The index of the element to retrieve.
 * @return The value at the specified index, or -1 if the index is out of bounds
 * or the array is NULL.
 */
int value_at(Array* arr, unsigned int index);

/**
 * @brief Insert a value at a specific index in the array.
 *
 * This function inserts the specified value at the given index in the array.
 * If the index is out of bounds, the operation fails.
 *
 * @param arr A pointer to the array.
 * @param index The index at which to insert the value.
 * @param value The value to insert.
 * @return 0 on success, -1 on failure.
 */
int insert_at(Array* arr, unsigned int index, int value);

/**
 * @brief Remove the element at a specific index in the array.
 *
 * This function removes the element at the specified index in the array
 * and shifts the remaining elements to fill the gap.
 *
 * @param arr A pointer to the array.
 * @param index The index of the element to remove.
 * @return 0 on success, -1 on failure.
 */
int remove_at(Array* arr, unsigned int index);

/**
 * @brief Append a value to the end of the array.
 *
 * This function appends the specified value to the end of the array.
 * If the array is full, it automatically increases its capacity before
 * appending.
 *
 * @param arr A pointer to the array.
 * @param value The value to append.
 * @return 0 on success, -1 on failure.
 */
int append(Array* arr, int value);

/**
 * @brief Swap the values at two specified indices in the array.
 *
 * This function swaps the values at the specified indices in the array.
 * If the indices are out of bounds, the operation fails.
 *
 * @param arr A pointer to the array.
 * @param index_a The index of the first element to swap.
 * @param index_b The index of the second element to swap.
 * @return 0 on success, -1 on failure.
 */
int swap(Array* arr, unsigned int index_a, unsigned int index_b);

/**
 * @brief Fill the array with a specified value.
 *
 * This function fills the entire array with the specified value.
 *
 * @param arr A pointer to the array.
 * @param value The value to fill the array with.
 * @return 0 on success, -1 on failure.
 */
int fill(Array* arr, int value);

/**
 * @brief Increase the capacity of the array.
 *
 * This function increases the capacity of the array by doubling its current
 * capacity.
 *
 * @param arr A pointer to the array.
 * @return 0 on success, -1 on failure.
 */
int increase_capacity(Array* arr);

#endif
