#include "int_list.h"

/**
 * @brief Creates a new list.
 * @return List*: Pointer to the newly created list, NULL if memory
 * allocation fails.
 */
List* IntList_create() { return List_create(sizeof(int)); }

/**
 * @brief clears the contents of the list
 * @param list: Pointer to the linked list.
 */
void IntList_clear(List* list) { List_clear(list); }

/**
 * @brief Destroys the entire linked list.
 * @param list: Pointer to a pointer to the linked list.
 */
void IntList_destroy(List** list) { List_destroy(list); }

/**
 * @brief Returns the size of the linked list.
 * @param list: Pointer to the linked list.
 * @return size_t: Number of nodes in the list. SIZE_MAX if list is NULL
 */
size_t IntList_size(List* list) { return List_size(list); }

/**
 * @brief Inserts a new node with the provided element at the specified index in
 * the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 * @param index: Index at which the element needs to be inserted.
 */
void IntList_insert(List* list, int element, size_t index) {
    List_insert(list, &element, index);
}

/**
 * @brief Inserts an element at the beginning of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void IntList_prepend(List* list, int element) { List_prepend(list, &element); }

/**
 * @brief Inserts an element at the end of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void IntList_append(List* list, int element) { List_append(list, &element); }

/**
 * @brief Finds the index of the specified element in the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be found.
 * @return size_t: Index of the element in the list, SIZE_MAX if not found.
 */
size_t IntList_find(List* list, int element) {
    return List_find(list, &element);
}

/**
 * @brief Retrieves the node at the specified index in the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be retrieved.
 * @return ListNode*: Pointer to the node at the given index, NULL if index is
 * out of bounds.
 */
ListNode* IntList_get(List* list, size_t index) {
    return List_get(list, index);
}

/**
 * @brief Removes the node at the specified index from the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be removed.
 */
void IntList_remove(List* list, size_t index) { List_remove(list, index); }

/**
 * @brief Iterates through the linked list and performs the callback function on
 * each element.
 * @param list: Pointer to the linked list.
 * @param callback: Function to be called on each element in the list.
 */
void IntList_iterate(List* list, void (*callback)(const void* element)) {
    List_iterate(list, callback);
}

/**
 * @brief Swaps the positions of two elements in the linked list.
 * @param list: Pointer to the linked list.
 * @param index_a: Index of the first element to swap.
 * @param index_b: Index of the second element to swap.
 */
void IntList_swap(List* list, size_t index_a, size_t index_b) {
    List_swap(list, index_a, index_b);
}

static int __compare(const ListNode* a, const ListNode* b) {
    int value_a = *((int*)(a->data));
    int value_b = *((int*)(b->data));

    if (value_a < value_b) {
        return -1;
    } else if (value_a > value_b) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Sorts the linked list using QuickSort algorithm.
 * @param list: Pointer to the linked list.
 * @param compare: Function pointer to a comparison function for sorting.
 */
void IntList_sort(List* list, ListNodeCompareFunction compare) {
    List_sort(list, __compare);
}

static void __print(const void* element) { printf("%d ", *((int*)element)); }

/**
 * @brief Prints the contents of the list to stdout
 * @param list: The list to be printed
 */
void IntList_print(List* list) { IntList_iterate(list, __print); }