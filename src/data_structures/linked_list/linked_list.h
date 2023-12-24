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
    void* data;
    struct ListNode* next;
} ListNode;

/**
 * @brief Creates a new list node.
 * @param element: The data to be stored in the new node.
 * @return ListNode*: Pointer to the newly created node, NULL if memory
 * allocation fails.
 */
ListNode* List_create_node(void* element);

/**
 * @brief Destroys the entire linked list.
 * @param head: Pointer to the head of the linked list.
 */
void List_destroy(ListNode** head);

/**
 * @brief Returns the size of the linked list.
 * @param head: Pointer to the head of the linked list.
 * @return size_t: Number of nodes in the list.
 */
size_t List_size(ListNode** head);

/**
 * @brief Inserts a new node with the provided element at the specified index in
 * the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param element: Element to be inserted.
 * @param index: Index at which the element needs to be inserted.
 */
void List_insert(ListNode** head, void* element, size_t index);

/**
 * @brief Inserts an element at the beginning of the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param element: Element to be inserted.
 */
void List_prepend(ListNode** head, void* element);

/**
 * @brief Inserts an element at the end of the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param element: Element to be inserted.
 */
void List_append(ListNode** head, void* element);

/**
 * @brief Finds the index of the specified element in the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param element: Element to be found.
 * @param data_size: Size of the element's data.
 * @return size_t: Index of the element in the list, SIZE_MAX if not found.
 */
size_t List_find(ListNode** head, void* element, size_t data_size);

/**
 * @brief Retrieves the node at the specified index in the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param index: Index of the node to be retrieved.
 * @return ListNode*: Pointer to the node at the given index, NULL if index is
 * out of bounds.
 */
ListNode* List_get(ListNode** head, size_t index);

/**
 * @brief Removes the node at the specified index from the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param index: Index of the node to be removed.
 */
void List_remove(ListNode** head, size_t index);

/**
 * @brief Iterates through the linked list and performs the callback function on
 * each element.
 * @param head: Pointer to the head of the linked list.
 * @param callback: Function to be called on each element in the list.
 */
void List_iterate(ListNode** head, void (*callback)(const void* element));

/**
 * @brief Swaps the positions of two elements in the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param index_a: Index of the first element to swap.
 * @param index_b: Index of the second element to swap.
 */
void List_swap(ListNode** head, size_t index_a, size_t index_b);

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
typedef int (*CompareFunction)(const ListNode* a, const ListNode* b);

/**
 * @brief Sorts the linked list using QuickSort algorithm.
 * @param head: Pointer to the head of the linked list.
 * @param compare: Function pointer to a comparison function for sorting.
 */
void List_sort(ListNode** head, CompareFunction compare);

#endif
