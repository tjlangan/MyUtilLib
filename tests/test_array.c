#include "test_array.h"

#include "string.h"

typedef struct Person {
    int age;
    float height;
    char name[64];
} Person;

void print_arr(T* element) { printf("%d ", *((int*)element->data)); }

void double_int(T* element) { *((int*)element->data) *= 2; }

int compare_int(const T* a, const T* b) {
    int int_a = *((const int*)a->data);
    int int_b = *((const int*)b->data);

    if (int_a < int_b) {
        return -1;  // a should come before b
    } else if (int_a > int_b) {
        return 1;  // a should come after b
    } else {
        return 0;  // a and b are equal
    }
}

int compare_person(const T* a, const T* b) {
    int age_a = (*((const Person*)a->data)).age;
    int age_b = (*((const Person*)b->data)).age;

    if (age_a < age_b) {
        return -1;
    } else if (age_a > age_b) {
        return 1;
    } else {
        return 0;
    }
}

void new_year(T* element) { (*((Person*)element->data)).age++; }

void test_array() {
    // Test creation
    ReturnArray create_result = Array_create(sizeof(int), 5);
    assert(create_result.error == NO_ERROR);
    assert(create_result.arr != NULL);
    Array* arr = create_result.arr;
    assert(arr != NULL);
    assert(arr->size == 0);
    assert(arr->capacity == 5);
    assert(arr->data_size == sizeof(int));
    assert(arr->values != NULL);
    for (size_t i = 0; i < arr->capacity; i++) {
        assert(arr->values[i].size == sizeof(int));
        assert(arr->values[i].data != NULL);
    }

    // Test basics
    ReturnSizeT size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 0);
    ReturnSizeT capacity_result = Array_capacity(arr);
    assert(capacity_result.error == NO_ERROR);
    assert(capacity_result.value == 5);
    ReturnBool is_empty_result = Array_is_empty(arr);
    assert(is_empty_result.error == NO_ERROR);
    assert(is_empty_result.value == true);
    ReturnBool is_full_result = Array_is_full(arr);
    assert(is_full_result.error == NO_ERROR);
    assert(is_full_result.value == false);

    // Test appending
    ReturnError append_result =
        Array_append(arr, &(T){sizeof(int), &(int){42}});  // {42}
    assert(append_result.error == NO_ERROR);
    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 1);
    ReturnData get_result = Array_get(arr, 0);
    assert(get_result.error == NO_ERROR);
    assert(*(int*)get_result.value->data == 42);

    // Test inserting
    ReturnError insert_result = Array_insert(
        arr, 0, &(T){sizeof(int), &(int){7}});  // insert in front {7, 42}
    assert(insert_result.error == NO_ERROR);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 2);

    insert_result = Array_insert(
        arr, size_result.value,
        &(T){sizeof(int), &(int){98}});  // insert at back {7, 42, 98}
    assert(insert_result.error == NO_ERROR);

    insert_result = Array_insert(
        arr, 1,
        &(T){sizeof(int), &(int){15}});  // insert in middle {7, 15, 42 98}
    assert(insert_result.error == NO_ERROR);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 4);

    get_result = Array_get(arr, 0);
    assert(get_result.error == NO_ERROR);
    assert(*(int*)get_result.value->data == 7);

    get_result = Array_get(arr, 1);
    assert(get_result.error == NO_ERROR);
    assert(*(int*)get_result.value->data == 15);

    get_result = Array_get(arr, 2);
    assert(get_result.error == NO_ERROR);
    assert(*(int*)get_result.value->data == 42);

    get_result = Array_get(arr, 3);
    assert(get_result.error == NO_ERROR);
    assert(*(int*)get_result.value->data == 98);

    // Test removing
    ReturnError remove_result =
        Array_remove(arr, 1);  // remove middle {7, 42, 98}
    assert(remove_result.error == NO_ERROR);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 3);

    remove_result =
        Array_remove(arr, size_result.value - 1);  // remove back {7, 42}
    assert(remove_result.error == NO_ERROR);

    remove_result = Array_remove(arr, 0);  // remove front {42}
    assert(remove_result.error == NO_ERROR);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 1);

    get_result = Array_get(arr, 0);
    assert(get_result.error == NO_ERROR);
    assert(*(int*)get_result.value->data == 42);

    // Test setting
    ReturnError set_result = Array_set(arr, 0, &(T){sizeof(int), &(int){99}});
    assert(set_result.error == NO_ERROR);

    get_result = Array_get(arr, 0);
    assert(get_result.error == NO_ERROR);
    assert(*(int*)get_result.value->data == 99);

    // Test clearing
    ReturnError clear_result = Array_clear(arr);
    assert(clear_result.error == NO_ERROR);
    assert(arr != NULL);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 0);

    capacity_result = Array_capacity(arr);
    assert(capacity_result.error == NO_ERROR);
    assert(capacity_result.value == 0);

    int vals[] = {37, -12, 94, 0, -56, 789, 23, -987, 456, -72};
    int sorted[] = {-987, -72, -56, -12, 0, 23, 37, 94, 456, 789};
    int doubled[] = {-1974, -144, -112, -24, 0, 46, 74, 188, 912, 1578};

    // Test adding a bunch of vals
    for (size_t i = 0; i < 10; i++) {
        append_result = Array_append(arr, &(T){sizeof(int), &vals[i]});
        assert(append_result.error == NO_ERROR);

        size_result = Array_size(arr);
        assert(size_result.error == NO_ERROR);
        assert(size_result.value == (i + 1));

        get_result = Array_get(arr, i);
        assert(get_result.error == NO_ERROR);
        assert(*(int*)get_result.value->data == vals[i]);
    }

    // Test find
    ReturnSizeT find_result = Array_find(arr, &(T){sizeof(int), &(int){23}});
    assert(find_result.error == NO_ERROR);
    assert(find_result.value == 6);

    // Test sort
    ReturnError sort_result = Array_sort(arr, compare_int);
    assert(sort_result.error == NO_ERROR);

    for (size_t i = 0; i < 10; i++) {
        get_result = Array_get(arr, i);
        assert(get_result.error == NO_ERROR);
        assert(*(int*)get_result.value->data == sorted[i]);
    }

    // Test iterate
    ReturnError iterate_result = Array_iterate(arr, double_int);
    assert(iterate_result.error == NO_ERROR);

    for (size_t i = 0; i < 10; i++) {
        get_result = Array_get(arr, i);
        assert(get_result.error == NO_ERROR);
        assert(*(int*)get_result.value->data == doubled[i]);
    }

    // Test Delete
    ReturnError destroy_result = Array_destroy(&arr);
    assert(destroy_result.error == NO_ERROR);
    assert(arr == NULL);
}

void test_int_array() {
    // Test creation
    Array* arr = IntArray_create(5);
    assert(arr != NULL);
    assert(arr->capacity == 5);
    assert(arr->values != NULL);
    assert(arr->size == 0);
    assert(arr->data_size == sizeof(int));
    for (size_t i = 0; i < arr->capacity; i++) {
        assert(arr->values[i].size == sizeof(int));
        assert(arr->values[i].data != NULL);
    }

    // Test basics
    assert(IntArray_size(arr) == 0);
    assert(IntArray_capacity(arr) == 5);
    assert(IntArray_is_empty(arr) == true);
    assert(IntArray_is_full(arr) == false);

    // Test appending
    IntArray_append(arr, 42);  // {42}
    assert(IntArray_size(arr) == 1);
    assert(IntArray_get(arr, 0) == 42);

    // Test inserting
    IntArray_insert(arr, 0, 7);  // insert in front {7, 42}
    IntArray_insert(arr, IntArray_size(arr),
                    98);          // insert at back {7, 42, 98}
    IntArray_insert(arr, 1, 15);  // insert in middle {7, 15, 42 98}
    assert(IntArray_size(arr) == 4);
    assert(IntArray_get(arr, 0) == 7);
    assert(IntArray_get(arr, IntArray_size(arr) - 1) == 98);
    assert(IntArray_get(arr, 1) == 15);

    // Test removing

    IntArray_remove(arr, 1);                       // remove middle {7, 42, 98}
    IntArray_remove(arr, IntArray_size(arr) - 1);  // remove back {7, 42}
    IntArray_remove(arr, 0);                       // remove front {42}

    assert(IntArray_size(arr) == 1);
    assert(IntArray_get(arr, 0) == 42);

    // Test setting
    IntArray_set(arr, 0, 99);
    assert(IntArray_size(arr) == 1);
    assert(IntArray_get(arr, 0) == 99);

    // Test clearing
    Array_clear(arr);
    assert(arr != NULL);
    assert(IntArray_size(arr) == 0);
    assert(IntArray_capacity(arr) == 0);

    int vals[] = {37, -12, 94, 0, -56, 789, 23, -987, 456, -72};
    int sorted[] = {-987, -72, -56, -12, 0, 23, 37, 94, 456, 789};
    int doubled[] = {-1974, -144, -112, -24, 0, 46, 74, 188, 912, 1578};

    // Test adding a bunch of vals
    for (size_t i = 0; i < 10; i++) {
        IntArray_append(arr, vals[i]);
        assert(IntArray_size(arr) == (i + 1));
        assert(IntArray_get(arr, i) == vals[i]);
    }

    // Test find
    assert(IntArray_find(arr, 23) == 6);

    // Test sort
    IntArray_sort(arr);
    for (size_t i = 0; i < 10; i++) {
        assert(IntArray_get(arr, i) == sorted[i]);
    }

    // Test iterate
    IntArray_iterate(arr, double_int);
    for (size_t i = 0; i < 10; i++) {
        assert(IntArray_get(arr, i) == doubled[i]);
    }

    // Test Delete
    IntArray_destroy(&arr);
    assert(arr == NULL);
}

void test_struct_array() {
    // Test creation
    ReturnArray create_result = Array_create(sizeof(Person), 5);
    assert(create_result.error == NO_ERROR);
    assert(create_result.arr != NULL);
    Array* arr = create_result.arr;
    assert(arr != NULL);
    assert(arr->capacity == 5);
    assert(arr->values != NULL);
    assert(arr->size == 0);
    assert(arr->data_size == sizeof(Person));
    for (size_t i = 0; i < arr->capacity; i++) {
        assert(arr->values[i].size == sizeof(Person));
        assert(arr->values[i].data != NULL);
    }

    // Test basics
    ReturnSizeT size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 0);
    ReturnSizeT capacity_result = Array_capacity(arr);
    assert(capacity_result.error == NO_ERROR);
    assert(capacity_result.value == 5);
    ReturnBool is_empty_result = Array_is_empty(arr);
    assert(is_empty_result.error == NO_ERROR);
    assert(is_empty_result.value == true);
    ReturnBool is_full_result = Array_is_full(arr);
    assert(is_full_result.error == NO_ERROR);
    assert(is_full_result.value == false);

    Person renee;
    renee.age = 23;
    renee.height = 5.1;
    strcpy(renee.name, "renee");

    Person tj;
    tj.age = 24;
    tj.height = 5.9;
    strcpy(tj.name, "tj");

    Person hunter;
    hunter.age = 21;
    hunter.height = 5.8;
    strcpy(hunter.name, "hunter");

    Person anna;
    anna.age = 22;
    anna.height = 5.4;
    strcpy(anna.name, "anna");

    Person emily;
    emily.age = 27;
    emily.height = 5.4;
    strcpy(emily.name, "emily");

    Person brewski;
    brewski.age = 1;
    brewski.height = 1.5;
    strcpy(brewski.name, "brewski");

    // Test appending
    ReturnError append_result =
        Array_append(arr, &(T){sizeof(Person), &renee});  // {renee}
    assert(append_result.error == NO_ERROR);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 1);

    ReturnData get_result = Array_get(arr, 0);
    assert(get_result.error == NO_ERROR);
    assert(((Person*)get_result.value->data)->age == renee.age);
    assert(((Person*)get_result.value->data)->height == renee.height);
    assert(strcmp(((Person*)get_result.value->data)->name, renee.name) == 0);

    // Test inserting
    ReturnError insert_result = Array_insert(
        arr, 0, &(T){sizeof(Person), &tj});  // insert in front {tj, renee}
    assert(insert_result.error == NO_ERROR);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 2);

    insert_result = Array_insert(
        arr, size_result.value,
        &(T){sizeof(Person), &hunter});  // insert at back {tj, renee, hunter}
    assert(insert_result.error == NO_ERROR);

    insert_result = Array_insert(
        arr, 1,
        &(T){sizeof(Person),
             &anna});  // insert in middle {tj, anna, renee, hunter}
    assert(insert_result.error == NO_ERROR);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 4);

    get_result = Array_get(arr, 0);
    assert(get_result.error == NO_ERROR);
    assert(((Person*)get_result.value->data)->age == tj.age);
    assert(((Person*)get_result.value->data)->height == tj.height);
    assert(strcmp(((Person*)get_result.value->data)->name, tj.name) == 0);

    get_result = Array_get(arr, 1);
    assert(get_result.error == NO_ERROR);
    assert(((Person*)get_result.value->data)->age == anna.age);
    assert(((Person*)get_result.value->data)->height == anna.height);
    assert(strcmp(((Person*)get_result.value->data)->name, anna.name) == 0);

    get_result = Array_get(arr, 2);
    assert(get_result.error == NO_ERROR);
    assert(((Person*)get_result.value->data)->age == renee.age);
    assert(((Person*)get_result.value->data)->height == renee.height);
    assert(strcmp(((Person*)get_result.value->data)->name, renee.name) == 0);

    get_result = Array_get(arr, 3);
    assert(get_result.error == NO_ERROR);
    assert(((Person*)get_result.value->data)->age == hunter.age);
    assert(((Person*)get_result.value->data)->height == hunter.height);
    assert(strcmp(((Person*)get_result.value->data)->name, hunter.name) == 0);

    // Test removing
    ReturnError remove_result =
        Array_remove(arr, 1);  // remove middle {tj, renee, hunter}
    assert(remove_result.error == NO_ERROR);
    remove_result = Array_remove(arr, 2);  // remove back {tj renee}
    assert(remove_result.error == NO_ERROR);
    remove_result = Array_remove(arr, 0);  // remove front {renee}
    assert(remove_result.error == NO_ERROR);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 1);

    get_result = Array_get(arr, 0);
    assert(get_result.error == NO_ERROR);
    assert(((Person*)get_result.value->data)->age == renee.age);
    assert(((Person*)get_result.value->data)->height == renee.height);
    assert(strcmp(((Person*)get_result.value->data)->name, renee.name) == 0);

    // Test setting
    ReturnError set_result = Array_set(arr, 0, &(T){sizeof(Person), &brewski});
    assert(set_result.error == NO_ERROR);
    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 1);

    get_result = Array_get(arr, 0);
    assert(get_result.error == NO_ERROR);
    assert(((Person*)get_result.value->data)->age == brewski.age);
    assert(((Person*)get_result.value->data)->height == brewski.height);
    assert(strcmp(((Person*)get_result.value->data)->name, brewski.name) == 0);

    // Test clearing
    ReturnError clear_result = Array_clear(arr);
    assert(clear_result.error == NO_ERROR);
    assert(arr != NULL);

    size_result = Array_size(arr);
    assert(size_result.error == NO_ERROR);
    assert(size_result.value == 0);

    capacity_result = Array_size(arr);
    assert(capacity_result.error == NO_ERROR);
    assert(capacity_result.value == 0);

    Person people[] = {renee, tj, hunter, anna, emily, brewski};
    Person sorted[] = {brewski, hunter, anna, renee, tj, emily};

    // Test adding a bunch of vals
    for (size_t i = 0; i < 6; i++) {
        append_result = Array_append(arr, &(T){sizeof(Person), &people[i]});
        assert(append_result.error == NO_ERROR);

        size_result = Array_size(arr);
        assert(size_result.error == NO_ERROR);
        assert(size_result.value == (i + 1));

        get_result = Array_get(arr, i);
        assert(get_result.error == NO_ERROR);
        assert(((Person*)get_result.value->data)->age == people[i].age);
        assert(((Person*)get_result.value->data)->height == people[i].height);
        assert(strcmp(((Person*)get_result.value->data)->name,
                      people[i].name) == 0);
    }

    // Test find
    ReturnSizeT find_result = Array_find(arr, &(T){sizeof(Person), &anna});
    assert(find_result.error == NO_ERROR);
    assert(find_result.value == 3);

    // Test sort
    ReturnError sort_result = Array_sort(arr, compare_person);
    assert(sort_result.error == NO_ERROR);
    for (size_t i = 0; i < 6; i++) {
        get_result = Array_get(arr, i);
        assert(get_result.error == NO_ERROR);
        assert(((Person*)get_result.value->data)->age == sorted[i].age);
        assert(((Person*)get_result.value->data)->height == sorted[i].height);
        assert(strcmp(((Person*)get_result.value->data)->name,
                      sorted[i].name) == 0);
    }

    // Test Iterate
    ReturnError iterate_result = Array_iterate(arr, new_year);
    assert(iterate_result.error == NO_ERROR);
    for (size_t i = 0; i < 6; i++) {
        get_result = Array_get(arr, i);
        assert(get_result.error == NO_ERROR);
        assert(((Person*)get_result.value->data)->age == (sorted[i].age + 1));
    }

    // Test Delete
    ReturnError destroy_result = Array_destroy(&arr);
    assert(destroy_result.error == NO_ERROR);
    assert(arr == NULL);
}
