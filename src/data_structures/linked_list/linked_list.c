#include "linked_list.h"

/**
 * @brief Creates a new list node.
 * @param element: The data to be stored in the new node.
 * @return ListNode*: Pointer to the newly created node, NULL if memory
 * allocation fails.
 */
ListNode* List_create_node(void* element) {
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (!new_node) {
        return (ListNode*)NULL;
    }

    new_node->data = element;
    new_node->next = NULL;
    return new_node;
}

/**
 * @brief Destroys the entire linked list.
 * @param head: Pointer to the head of the linked list.
 */
void List_destroy(ListNode** head) {
    if (head == NULL || *head == NULL) {
        return;
    }

    ListNode* current = *head;
    ListNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

/**
 * @brief Returns the size of the linked list.
 * @param head: Pointer to the head of the linked list.
 * @return size_t: Number of nodes in the list.
 */
size_t List_size(ListNode** head) {
    size_t count = 0;
    ListNode* current = *head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

/**
 * @brief Inserts a new node with the provided element at the specified index in
 * the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param element: Element to be inserted.
 * @param index: Index at which the element needs to be inserted.
 */
void List_insert(ListNode** head, void* element, size_t index) {
    if (head == NULL || *head == NULL) {
        return;
    }

    ListNode* new_node = List_create_node(element);
    if (new_node == NULL) {
        return;
    }

    if (index == 0) {
        new_node->next = *head;
        *head = new_node;
    } else {
        size_t count = 1;
        ListNode* current = *head;

        while (count < index && current->next != NULL) {
            count++;
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;
    }
}

/**
 * @brief Inserts an element at the beginning of the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param element: Element to be inserted.
 */
void List_prepend(ListNode** head, void* element) {
    List_insert(head, element, 0);
}

/**
 * @brief Inserts an element at the end of the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param element: Element to be inserted.
 */
void List_append(ListNode** head, void* element) {
    List_insert(head, element, SIZE_MAX);
}

/**
 * @brief Finds the index of the specified element in the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param element: Element to be found.
 * @param data_size: Size of the element's data.
 * @return size_t: Index of the element in the list, SIZE_MAX if not found.
 */
size_t List_find(ListNode** head, void* element, size_t data_size) {
    if (head == NULL || *head == NULL || element == NULL) {
        return SIZE_MAX;
    }

    size_t index = 0;
    ListNode* current = *head;

    while (current != NULL) {
        if (memcmp(current->data, element, data_size) == 0) {
            return index;
        }

        index++;
        current = current->next;
    }

    return SIZE_MAX;
}

/**
 * @brief Retrieves the node at the specified index in the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param index: Index of the node to be retrieved.
 * @return ListNode*: Pointer to the node at the given index, NULL if index is
 * out of bounds.
 */
ListNode* List_get(ListNode** head, size_t index) {
    if (head == NULL || *head == NULL) {
        return (ListNode*)NULL;
    }

    ListNode* current = *head;
    size_t i = 0;
    while (current != NULL) {
        if (i == index) {
            return current;
        }
        i++;
        current = current->next;
    }

    return (ListNode*)NULL;
}

/**
 * @brief Removes the node at the specified index from the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param index: Index of the node to be removed.
 */
void List_remove(ListNode** head, size_t index) {
    if (head == NULL || *head == NULL) {
        return;
    }

    if (index == 0) {
        ListNode* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    ListNode* previous = List_get(head, index - 1);
    if (previous == NULL) {
        return;
    }

    ListNode* current = previous->next;
    previous->next = current->next;
    free(current);
}

/**
 * @brief Iterates through the linked list and performs the callback function on
 * each element.
 * @param head: Pointer to the head of the linked list.
 * @param callback: Function to be called on each element in the list.
 */
void List_iterate(ListNode** head, void (*callback)(const void* element)) {
    ListNode* current = *head;
    while (current != NULL) {
        callback(current->data);
        current = current->next;
    }
}

/**
 * @brief Swaps the positions of two elements in the linked list.
 * @param head: Pointer to the head of the linked list.
 * @param index_a: Index of the first element to swap.
 * @param index_b: Index of the second element to swap.
 */
void List_swap(ListNode** head, size_t index_a, size_t index_b) {
    if (head == NULL || *head == NULL) {
        return;
    }

    if (index_a == index_b) {
        return;
    }

    ListNode *prev_a = NULL, *prev_b = NULL;
    ListNode *curr_a = NULL, *curr_b = NULL;

    prev_a = List_get(head, index_a - 1);
    if (prev_a != NULL) {
        curr_a = prev_a->next;
    } else if (prev_a == NULL && index_a == 0) {
        curr_a = *head;
    }

    prev_b = List_get(head, index_b - 1);
    if (prev_b != NULL) {
        curr_b = prev_b->next;
    } else if (prev_b == NULL && index_b == 0) {
        curr_b = *head;
    }

    if (curr_a != NULL && curr_b != NULL) {
        if (prev_a != NULL) {
            prev_a->next = curr_b;
        } else {
            *head = curr_b;
        }
        if (prev_b != NULL) {
            prev_b->next = curr_a;
        } else {
            *head = curr_a;
        }

        ListNode* temp = curr_b->next;
        curr_b->next = curr_a->next;
        curr_a->next = temp;
    }
}

static size_t partition(ListNode** head, size_t low, size_t high,
                        CompareFunction compare) {
    ListNode* pivot = List_get(head, high);
    size_t i = low - 1;

    for (size_t j = low; j < high; j++) {
        if (compare(List_get(head, j), pivot) < 0) {
            i++;
            List_swap(head, i, j);
        }
    }
    List_swap(head, i + 1, high);
    return i + 1;
}

static void quick_sort(ListNode** head, size_t low, size_t high,
                       CompareFunction compare) {
    if (low < high) {
        size_t pi = partition(head, low, high, compare);

        if (pi > 0) {
            quick_sort(head, low, pi - 1, compare);
        }

        quick_sort(head, pi + 1, high, compare);
    }
}

/**
 * @brief Sorts the linked list using QuickSort algorithm.
 * @param head: Pointer to the head of the linked list.
 * @param compare: Function pointer to a comparison function for sorting.
 */
void List_sort(ListNode** head, CompareFunction compare) {
    if (head == NULL || *head == NULL || compare == NULL) {
        return;
    }
    quick_sort(head, 0, List_size(head) - 1, compare);
}
