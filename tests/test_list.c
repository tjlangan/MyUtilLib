#include "test_list.h"

void print_list(const void* element) { printf("%d ", *((int*)element)); }
int compare_list(const ListNode* a, const ListNode* b) {
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

// int compare_int_list()

void double_list_val(const void* element) { *((int*)element) *= 2; }

void test_list() {
    // Test Creation
    List* list = List_create(sizeof(int));
    assert(list != NULL);
    assert(list->data_size == sizeof(int));
    assert(list->size == 0);
    assert(list->head != NULL);

    // Test Basics
    assert(List_size(list) == 0);

    // Test Adding element
    List_append(list, &(int){42});  // {42}
    assert(list != NULL);
    assert(list->head != NULL);
    assert(List_size(list) == 1);
    assert(*((int*)(List_get(list, 0)->data)) == 42);

    // Test Adding a bunch
    List_prepend(list, &(int){7});     // insert in front {7, 42}
    List_append(list, &(int){98});     // insert at back {7, 42, 98}
    List_insert(list, &(int){15}, 1);  // insert in middle {7, 15, 42 98}
    assert(List_size(list) == 4);
    assert(*((int*)(List_get(list, 0)->data)) == 7);
    assert(*((int*)(List_get(list, List_size(list) - 1)->data)) == 98);
    assert(*((int*)(List_get(list, 1)->data)) == 15);

    // Test removing
    List_remove(list, 1);                    // remove middle {7, 42, 98}
    List_remove(list, List_size(list) - 1);  // remove back {7, 42}
    List_remove(list, 0);                    // remove front {42}
    assert(List_size(list) == 1);
    assert(*((int*)(List_get(list, 0)->data)) == 42);

    // Test clearing
    List_clear(list);
    assert(list != NULL);
    assert(list->head != NULL);
    assert(*(list->head) == NULL);
    assert(List_size(list) == 0);

    int vals[] = {37, -12, 94, 0, -56, 789, 23, -987, 456, -72};
    int sorted[] = {-987, -72, -56, -12, 0, 23, 37, 94, 456, 789};
    int doubled[] = {-1974, -144, -112, -24, 0, 46, 74, 188, 912, 1578};

    // Test adding a bunch
    for (size_t i = 0; i < 10; i++) {
        List_append(list, &vals[i]);
        assert(List_size(list) == (i + 1));
        assert(*((int*)(List_get(list, i)->data)) == vals[i]);
    }

    // Test find
    assert(List_find(list, &(int){23}) == 6);

    // Test sort
    List_sort(list, compare_list);
    for (size_t i = 0; i < 10; i++) {
        assert(*((int*)(List_get(list, i)->data)) == sorted[i]);
    }

    // Test Iterate
    List_iterate(list, double_list_val);
    for (size_t i = 0; i < 10; i++) {
        assert(*((int*)(List_get(list, i)->data)) == doubled[i]);
    }

    // Test Destroy
    List_destroy(&list);
    assert(list == NULL);
}

void test_int_list() {
    // Test Creation
    List* list = IntList_create();
    assert(list != NULL);
    assert(list->data_size == sizeof(int));
    assert(list->size == 0);
    assert(list->head != NULL);

    // Test Basics
    assert(IntList_size(list) == 0);

    // Test Adding element
    IntList_append(list, 42);  // {42}
    assert(list != NULL);
    assert(list->head != NULL);
    assert(IntList_size(list) == 1);
    assert(IntList_get(list, 0) == 42);

    // Test Adding a bunch
    IntList_prepend(list, 7);     // insert in front {7, 42}
    IntList_append(list, 98);     // insert at back {7, 42, 98}
    IntList_insert(list, 15, 1);  // insert in middle {7, 15, 42 98}
    assert(IntList_size(list) == 4);
    assert(IntList_get(list, 0) == 7);
    assert(IntList_get(list, IntList_size(list) - 1) == 98);
    assert(IntList_get(list, 1) == 15);

    // Test removing
    IntList_remove(list, 1);                       // remove middle {7, 42, 98}
    IntList_remove(list, IntList_size(list) - 1);  // remove back {7, 42}
    IntList_remove(list, 0);                       // remove front {42}
    assert(IntList_size(list) == 1);
    assert(IntList_get(list, 0) == 42);

    // Test clearing
    IntList_clear(list);
    assert(list != NULL);
    assert(list->head != NULL);
    assert(*(list->head) == NULL);
    assert(IntList_size(list) == 0);

    int vals[] = {37, -12, 94, 0, -56, 789, 23, -987, 456, -72};
    int sorted[] = {-987, -72, -56, -12, 0, 23, 37, 94, 456, 789};
    int doubled[] = {-1974, -144, -112, -24, 0, 46, 74, 188, 912, 1578};

    // Test adding a bunch
    for (size_t i = 0; i < 10; i++) {
        IntList_append(list, vals[i]);
        assert(IntList_size(list) == (i + 1));
        assert(IntList_get(list, i) == vals[i]);
    }

    // Test find
    assert(IntList_find(list, 23) == 6);

    // Test sort
    IntList_sort(list, compare_list);
    for (size_t i = 0; i < 10; i++) {
        assert(IntList_get(list, i) == sorted[i]);
    }

    // Test Iterate
    IntList_iterate(list, double_list_val);
    for (size_t i = 0; i < 10; i++) {
        assert(IntList_get(list, i) == doubled[i]);
    }

    // Test Destroy
    IntList_destroy(&list);
    assert(list == NULL);
}