#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Represents a node in a linked list containing generic data.
 */
typedef struct ListNode {
    void* data;            /**< Pointer to the stored data in the node. */
    struct ListNode* next; /**< Pointer to the next node in the list. */
} ListNode;

/**
 * @brief Represents a linked list along with metadata.
 */
typedef struct List {
    size_t data_size; /**< Size of the data stored in each node. */
    size_t size;      /**< Current size of the linked list. */
    ListNode** head;  /**< Pointer to the pointer to the list's head node. */
} List;

/**
 * @brief Creates a new list.
 * @param data_size: The data size of the elements to be included in this list.
 * @return List*: Pointer to the newly created list, NULL if memory
 * allocation fails.
 */
List* List_create(size_t data_size);

/**
 * @brief clears the contents of the list
 * @param list: Pointer to the linked list.
 */
void List_clear(List* list);

/**
 * @brief Destroys the entire linked list.
 * @param list: Pointer to the linked list.
 */
void List_destroy(List* list);

/**
 * @brief Returns the size of the linked list.
 * @param list: Pointer to the linked list.
 * @return size_t: Number of nodes in the list. SIZE_MAX if list is NULL
 */
size_t List_size(List* list);

/**
 * @brief Inserts a new node with the provided element at the specified index in
 * the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 * @param index: Index at which the element needs to be inserted.
 */
void List_insert(List* list, void* element, size_t index);

/**
 * @brief Inserts an element at the beginning of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void List_prepend(List* list, void* element);

/**
 * @brief Inserts an element at the end of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void List_append(List* list, void* element);

/**
 * @brief Finds the index of the specified element in the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be found.
 * @param data_size: Size of the element's data.
 * @return size_t: Index of the element in the list, SIZE_MAX if not found.
 */
size_t List_find(List* list, void* element, size_t data_size);

/**
 * @brief Retrieves the node at the specified index in the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be retrieved.
 * @return ListNode*: Pointer to the node at the given index, NULL if index is
 * out of bounds.
 */
ListNode* List_get(List* list, size_t index);

/**
 * @brief Removes the node at the specified index from the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be removed.
 */
void List_remove(List* list, size_t index);

/**
 * @brief Iterates through the linked list and performs the callback function on
 * each element.
 * @param list: Pointer to the linked list.
 * @param callback: Function to be called on each element in the list.
 */
void List_iterate(List* list, void (*callback)(const void* element));

/**
 * @brief Swaps the positions of two elements in the linked list.
 * @param list: Pointer to the linked list.
 * @param index_a: Index of the first element to swap.
 * @param index_b: Index of the second element to swap.
 */
void List_swap(List* list, size_t index_a, size_t index_b);

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
void List_sort(List* list, ListNodeCompareFunction compare);

#endif
