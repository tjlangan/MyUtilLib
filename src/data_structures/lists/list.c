#include "list.h"

/**
 * @brief Creates a new list.
 * @param data_size: The data size of the elements to be included in this list.
 * @return List*: Pointer to the newly created list, NULL if memory
 * allocation fails.
 */
List* List_create(size_t data_size) {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list == NULL) {
        return (List*)NULL;
    }

    new_list->head = (ListNode**)malloc(sizeof(List*));
    if (new_list->head == NULL) {
        free(new_list);
        return (List*)NULL;
    }

    new_list->data_size = data_size;
    new_list->size = 0;

    return new_list;
}

static ListNode* create_node(void* element, size_t data_size) {
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (new_node == NULL) {
        return (ListNode*)NULL;
    }

    new_node->data = malloc(data_size);
    if (new_node->data == NULL) {
        free(new_node);
        return (ListNode*)NULL;
    }

    memcpy(new_node->data, element, data_size);
    new_node->next = NULL;
    return new_node;
}

/**
 * @brief clears the contents of the list
 * @param list: Pointer to the linked list.
 */
void List_clear(List* list) {
    if (list == NULL || list->head == NULL || *(list->head) == NULL) {
        return;
    }

    ListNode* current = *(list->head);
    ListNode* next;

    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    *(list->head) = NULL;
    list->size = 0;
}

/**
 * @brief Destroys the entire linked list.
 * @param list: Pointer to the linked list.
 */
void List_destroy(List** list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    List_clear(*list);

    free(*list);
    *list = NULL;
}

/**
 * @brief Returns the size of the linked list.
 * @param list: Pointer to the linked list.
 * @return size_t: Number of nodes in the list. SIZE_MAX if list is NULL
 */
size_t List_size(List* list) {
    if (list == NULL) {
        return SIZE_MAX;
    }

    return list->size;
}

/**
 * @brief Inserts a new node with the provided element at the specified index in
 * the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 * @param index: Index at which the element needs to be inserted.
 */
void List_insert(List* list, void* element, size_t index) {
    if (list == NULL) {
        return;
    }

    ListNode* new_node = create_node(element, list->data_size);

    if (new_node == NULL) {
        return;
    }

    if (List_size(list) == 0) {
        *(list->head) = new_node;
    } else {
        if (index == 0) {
            new_node->next = *(list->head);
            *(list->head) = new_node;
        } else {
            ListNode* prev = List_get(list, index - 1);
            new_node->next = prev->next;
            prev->next = new_node;
        }
    }
    list->size++;
}

/**
 * @brief Inserts an element at the beginning of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void List_prepend(List* list, void* element) { List_insert(list, element, 0); }

/**
 * @brief Inserts an element at the end of the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be inserted.
 */
void List_append(List* list, void* element) {
    List_insert(list, element, List_size(list));
}

/**
 * @brief Finds the index of the specified element in the linked list.
 * @param list: Pointer to the linked list.
 * @param element: Element to be found.
 * @return size_t: Index of the element in the list, SIZE_MAX if not found.
 */
size_t List_find(List* list, void* element) {
    if (list == NULL || list->head == NULL || *(list->head) == NULL ||
        element == NULL) {
        return SIZE_MAX;
    }

    size_t index = 0;
    ListNode* current = *(list->head);

    while (current != NULL) {
        if (memcmp(current->data, element, list->data_size) == 0) {
            return index;
        }

        index++;
        current = current->next;
    }

    return SIZE_MAX;
}

/**
 * @brief Retrieves the node at the specified index in the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be retrieved.
 * @return ListNode*: Pointer to the node at the given index, NULL if index is
 * out of bounds.
 */
ListNode* List_get(List* list, size_t index) {
    if (list == NULL || list->head == NULL || *(list->head) == NULL) {
        return (ListNode*)NULL;
    }

    ListNode* current = *(list->head);
    size_t i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (i == index && current != NULL) {
        return current;
    }

    return (ListNode*)NULL;
}

/**
 * @brief Removes the node at the specified index from the linked list.
 * @param list: Pointer to the linked list.
 * @param index: Index of the node to be removed.
 */
void List_remove(List* list, size_t index) {
    if (list == NULL || list->head == NULL || *(list->head) == NULL) {
        return;
    }

    if (index == 0) {
        ListNode* temp = *(list->head);
        *(list->head) = (*(list->head))->next;
        free(temp);
        list->size--;
        return;
    }

    ListNode* previous = List_get(list, index - 1);
    if (previous == NULL) {
        return;
    }

    ListNode* current = previous->next;
    previous->next = current->next;
    free(current);
    list->size--;
}

/**
 * @brief Iterates through the linked list and performs the callback function on
 * each element.
 * @param list: Pointer to the linked list.
 * @param callback: Function to be called on each element in the list.
 */
void List_iterate(List* list, void (*callback)(const void* element)) {
    if (list == NULL || list->head == NULL || *(list->head) == NULL) {
        return;
    }
    ListNode* current = *(list->head);
    while (current != NULL) {
        callback(current->data);
        current = current->next;
    }
}

/**
 * @brief Swaps the positions of two elements in the linked list.
 * @param list: Pointer to the linked list.
 * @param index_a: Index of the first element to swap.
 * @param index_b: Index of the second element to swap.
 */
void List_swap(List* list, size_t index_a, size_t index_b) {
    if (list == NULL || list->head == NULL || *(list->head) == NULL) {
        return;
    }

    if (index_a == index_b) {
        return;
    }

    ListNode *prev_a = NULL, *prev_b = NULL;
    ListNode *curr_a = NULL, *curr_b = NULL;

    prev_a = List_get(list, index_a - 1);
    if (prev_a != NULL) {
        curr_a = prev_a->next;
    } else if (prev_a == NULL && index_a == 0) {
        curr_a = *(list->head);
    }

    prev_b = List_get(list, index_b - 1);
    if (prev_b != NULL) {
        curr_b = prev_b->next;
    } else if (prev_b == NULL && index_b == 0) {
        curr_b = *(list->head);
    }

    if (curr_a != NULL && curr_b != NULL) {
        if (prev_a != NULL) {
            prev_a->next = curr_b;
        } else {
            *(list->head) = curr_b;
        }
        if (prev_b != NULL) {
            prev_b->next = curr_a;
        } else {
            *(list->head) = curr_a;
        }

        ListNode* temp = curr_b->next;
        curr_b->next = curr_a->next;
        curr_a->next = temp;
    }
}

static size_t partition(List* list, size_t low, size_t high,
                        ListNodeCompareFunction compare) {
    ListNode* pivot = List_get(list, high);
    size_t i = low - 1;

    for (size_t j = low; j < high; j++) {
        if (compare(List_get(list, j), pivot) < 0) {
            i++;
            List_swap(list, i, j);
        }
    }
    List_swap(list, i + 1, high);
    return i + 1;
}

static void quick_sort(List* list, size_t low, size_t high,
                       ListNodeCompareFunction compare) {
    if (low < high) {
        size_t pi = partition(list, low, high, compare);

        if (pi > 0) {
            quick_sort(list, low, pi - 1, compare);
        }

        quick_sort(list, pi + 1, high, compare);
    }
}

/**
 * @brief Sorts the linked list using QuickSort algorithm.
 * @param list: Pointer to the linked list.
 * @param compare: Function pointer to a comparison function for sorting.
 */
void List_sort(List* list, ListNodeCompareFunction compare) {
    if (list == NULL || list->head == NULL || *(list->head) == NULL) {
        return;
    }
    quick_sort(list, 0, List_size(list) - 1, compare);
}
