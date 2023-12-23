#include "linked_list.h"

LLNode* LL_create_node(void* element) {
    LLNode* new_node = (LLNode*)malloc(sizeof(LLNode));
    if (!new_node) {
        return (LLNode*)NULL;
    }

    new_node->data = element;
    new_node->next = NULL;
    return new_node;
}

void LL_destroy(LLNode** head) {
    if (*head == NULL) {
        return;
    }

    LLNode* current = *head;
    LLNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

size_t LL_size(LLNode** head) {
    if (*head == NULL) {
        return SIZE_MAX;
    }

    LLNode* current = *head;
    size_t size = 0;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

void LL_prepend(LLNode** head, void* element) {
    if (*head == NULL) {
        return;
    }

    LLNode* new_node = LL_create_node(element);
}

void LL_append(LLNode** head, void* element);

void LL_insert_after(LLNode* prev, void* element);

void LL_remove_element(LLNode** head, void* element);

void LL_remove_index(LLNode** head, size_t index);

LLNode* LL_search(LLNode** head, void* element);

void LL_reverse(LLNode** head);

void LL_iterate(LLNode** head, void (*callback)(const void* element));

void LL_swap(LLNode* a, LLNode* b);

typedef int (*CompareFunction)(const LLNode* a, const LLNode* b);

void LL_sort(LLNode** head, CompareFunction compare);
