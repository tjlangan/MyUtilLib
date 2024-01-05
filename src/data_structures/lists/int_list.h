#ifndef INT_LIST_H
#define INT_LIST_H

#include "list.h"

/**
 * @brief Creates a new list.
 * @return List*: Pointer to the newly created list, NULL if memory
 * allocation fails.
 */
List* IntList_create();

/**
 * @brief clears the contents of the list
 * @param list: Pointer to the linked list.
 */
void IntList_clear(List* list);

/**
 * @brief Destroys the entire linked list.
 * @param list: Pointer to a pointer to the linked list.
 */
void IntList_destroy(List** list);

/**
 * @brief Returns the size of the linked list.
 * @param list: Pointer to the linked list.
 * @return size_t: Number of nodes in the list. SIZE_MAX if list is NULL
 */
size_t IntList_size(List* list);

/**
 * @brief Inserts a new node with the provided element at the specified index in
 * the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 * @param index: Index at which the element needs to be inserted.
 */
void IntList_insert(List* list, int element, size_t index);

/**
 * @brief Inserts an element at the beginning of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void IntList_prepend(List* list, int element);

/**
 * @brief Inserts an element at the end of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void IntList_append(List* list, int element);

/**
 * @brief Finds the index of the specified element in the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be found.
 * @return size_t: Index of the element in the list, SIZE_MAX if not found.
 */
size_t IntList_find(List* list, int element);

/**
 * @brief Retrieves the node at the specified index in the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be retrieved.
 * @return int: value at the node at the given index, NULL if index is
 * out of bounds.
 */
int IntList_get(List* list, size_t index);

/**
 * @brief Removes the node at the specified index from the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be removed.
 */
void IntList_remove(List* list, size_t index);

/**
 * @brief Iterates through the linked list and performs the callback function on
 * each element.
 * @param list: Pointer to the linked list.
 * @param callback: Function to be called on each element in the list.
 */
void IntList_iterate(List* list, void (*callback)(const void* element));

/**
 * @brief Swaps the positions of two elements in the linked list.
 * @param list: Pointer to the linked list.
 * @param index_a: Index of the first element to swap.
 * @param index_b: Index of the second element to swap.
 */
void IntList_swap(List* list, size_t index_a, size_t index_b);

/**
 * @brief Represents a function pointer type used for comparing nodes in a
 * linked list.
 *
 * This function pointer type is used to compare nodes in a linked list. It
 * takes two `ListNode` pointers as arguments and returns an integer indicating
 * the comparison result. The function should follow the convention of returning
 * a negative value if the first node should precede the second node, zero if
 * they are equivalent, and a positive value if the second node should precede
 * the first node.
 *
 * @param a Pointer to the first `ListNode` to compare.
 * @param b Pointer to the second `ListNode` to compare.
 * @return An integer representing the comparison result.
 */
typedef int (*ListNodeCompareFunction)(const ListNode* a, const ListNode* b);

/**
 * @brief Sorts the linked list using QuickSort algorithm.
 * @param list: Pointer to the linked list.
 * @param compare: Function pointer to a comparison function for sorting.
 */
void IntList_sort(List* list);

/**
 * @brief Prints the contents of the list to stdout
 * @param list: The list to be printed
 */
void IntList_print(List* list);

#endif
