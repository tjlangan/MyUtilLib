#include "dlist.h"

/**
 * @brief Creates a new list.
 * @param data_size: The data size of the elements to be included in this list.
 * @return List*: Pointer to the newly created list, NULL if memory
 * allocation fails.
 */
DList* DList_create(size_t data_size);

/**
 * @brief clears the contents of the list
 * @param list: Pointer to the linked list.
 */
void DList_clear(DList* list);

/**
 * @brief Destroys the entire linked list.
 * @param list: Pointer to a pointer to the linked list.
 */
void DList_destroy(DList** list);

/**
 * @brief Returns the size of the linked list.
 * @param list: Pointer to the linked list.
 * @return size_t: Number of nodes in the list. SIZE_MAX if list is NULL
 */
size_t DList_size(DList* list);

/**
 * @brief Inserts a new node with the provided element at the specified index in
 * the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 * @param index: Index at which the element needs to be inserted.
 */
void DList_insert(DList* list, void* element, size_t index);

/**
 * @brief Inserts an element at the beginning of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void DList_prepend(DList* list, void* element);

/**
 * @brief Inserts an element at the end of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void DList_append(DList* list, void* element);

/**
 * @brief Finds the index of the specified element in the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be found.
 * @return size_t: Index of the element in the list, SIZE_MAX if not found.
 */
size_t DList_find(DList* list, void* element);

/**
 * @brief Retrieves the node at the specified index in the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be retrieved.
 * @return DListNode*: Pointer to the node at the given index, NULL if index is
 * out of bounds.
 */
DListNode* DList_get(DList* list, size_t index);

/**
 * @brief Removes the node at the specified index from the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be removed.
 */
void DList_remove(DList* list, size_t index);

/**
 * @brief Iterates through the linked list and performs the callback function on
 * each element.
 * @param list: Pointer to the linked list.
 * @param callback: Function to be called on each element in the list.
 */
void DList_iterate(DList* list, void (*callback)(const void* element));

/**
 * @brief Swaps the positions of two elements in the linked list.
 * @param list: Pointer to the linked list.
 * @param index_a: Index of the first element to swap.
 * @param index_b: Index of the second element to swap.
 */
void DList_swap(DList* list, size_t index_a, size_t index_b);

/**
 * @brief Represents a function pointer type used for comparing nodes in a
 * doubly linked list.
 *
 * This function pointer type is used to compare nodes in a linked list. It
 * takes two `DListNode` pointers as arguments and returns an integer indicating
 * the comparison result. The function should follow the convention of returning
 * a negative value if the first node should precede the second node, zero if
 * they are equivalent, and a positive value if the second node should precede
 * the first node.
 *
 * @param a Pointer to the first `DListNode` to compare.
 * @param b Pointer to the second `DListNode` to compare.
 * @return An integer representing the comparison result.
 */
typedef int (*DListNodeCompareFunction)(const DListNode* a, const DListNode* b);

/**
 * @brief Sorts the linked list using QuickSort algorithm.
 * @param list: Pointer to the linked list.
 * @param compare: Function pointer to a comparison function for sorting.
 */
void DList_sort(DList* list, DListNodeCompareFunction compare);