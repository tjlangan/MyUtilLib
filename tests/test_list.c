#include "test_list.h"

void test_list() {
    // Test Creation
    List* list = List_create(sizeof(int));
    assert(list != NULL);
    assert(list->data_size == sizeof(int));
    assert(list->size == 0);
    assert(list->head == NULL);

    // Test Destroy
    List_destroy(list);
    assert(list == NULL);
}