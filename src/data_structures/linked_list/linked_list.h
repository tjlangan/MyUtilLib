#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdint.h>
#include <stdlib.h>

typedef struct LLNode {
    void* data;
    struct LLNode* next;
} LLNode;

LLNode* LL_create_node(void* element);

void LL_destroy(LLNode** head);

size_t LL_size(LLNode** head);

void LL_prepend(LLNode** head, void* element);

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

#endif
