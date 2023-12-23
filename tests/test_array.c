#include "test_array.h"

#include "string.h"

typedef struct Person {
    int age;
    float height;
    char name[64];
} Person;

void print_arr(const void* element) { printf("%d ", *((int*)element)); }

void double_int(const void* element) { *((int*)element) *= 2; }

int compare_int(const void* a, const void* b) {
    int int_a = *((const int*)a);
    int int_b = *((const int*)b);

    if (int_a < int_b) {
        return -1;  // a should come before b
    } else if (int_a > int_b) {
        return 1;  // a should come after b
    } else {
        return 0;  // a and b are equal
    }
}

int compare_person(const void* a, const void* b) {
    int age_a = (*((const Person*)a)).age;
    int age_b = (*((const Person*)b)).age;

    if (age_a < age_b) {
        return -1;
    } else if (age_a > age_b) {
        return 1;
    } else {
        return 0;
    }
}

void new_year(const void* element) { (*((Person*)element)).age++; }

void test_array() {
    // Test creation
    Array* arr = Array_create(sizeof(int), 5);
    assert(arr != NULL);
    assert(arr->capacity == 5);
    assert(arr->data != NULL);
    assert(arr->size == 0);
    assert(arr->data_size == sizeof(int));

    // Test basics
    assert(Array_size(arr) == 0);
    assert(Array_capacity(arr) == 5);
    assert(Array_is_empty(arr) == true);
    assert(Array_is_full(arr) == false);

    // Test appending
    Array_append(arr, &(int){42});  // {42}
    assert(Array_size(arr) == 1);
    assert(*((int*)Array_get(arr, 0)) == 42);

    // Test inserting
    Array_insert(arr, 0, &(int){7});  // insert in front {7, 42}
    Array_insert(arr, Array_size(arr),
                 &(int){98});          // insert at back {7, 42, 98}
    Array_insert(arr, 1, &(int){15});  // insert in middle {7, 15, 42 98}
    assert(Array_size(arr) == 4);
    assert(*((int*)Array_get(arr, 0)) == 7);
    assert(*((int*)Array_get(arr, Array_size(arr) - 1)) == 98);
    assert(*((int*)Array_get(arr, 1)) == 15);

    // Test removing
    Array_remove(arr, 1);                    // remove middle {7, 42, 98}
    Array_remove(arr, Array_size(arr) - 1);  // remove back {7, 42}
    Array_remove(arr, 0);                    // remove front {42}

    assert(Array_size(arr) == 1);
    assert(*((int*)Array_get(arr, 0)) == 42);

    // Test setting
    Array_set(arr, 0, &(int){99});
    assert(Array_size(arr) == 1);
    assert(*((int*)Array_get(arr, 0)) == 99);

    // Test clearing
    Array_clear(arr);
    assert(arr != NULL);
    assert(Array_size(arr) == 0);
    assert(Array_capacity(arr) == 0);

    int vals[] = {37, -12, 94, 0, -56, 789, 23, -987, 456, -72};
    int sorted[] = {-987, -72, -56, -12, 0, 23, 37, 94, 456, 789};
    int doubled[] = {-1974, -144, -112, -24, 0, 46, 74, 188, 912, 1578};

    // Test adding a bunch of vals
    for (size_t i = 0; i < 10; i++) {
        Array_append(arr, &vals[i]);
        assert(Array_size(arr) == (i + 1));
        assert(*((int*)Array_get(arr, i)) == vals[i]);
    }

    // Test find
    assert(Array_find(arr, &(int){23}) == 6);

    // Test sort
    Array_sort(arr, compare_int);
    for (size_t i = 0; i < 10; i++) {
        assert(*((int*)Array_get(arr, i)) == sorted[i]);
    }

    // Test iterate
    Array_iterate(arr, double_int);
    for (size_t i = 0; i < 10; i++) {
        assert(*((int*)Array_get(arr, i)) == doubled[i]);
    }

    // Test Delete
    Array_destroy(&arr);
    assert(arr == NULL);
}

void test_int_array() {
    // Test creation
    Array* arr = IntArray_create(5);
    assert(arr != NULL);
    assert(arr->capacity == 5);
    assert(arr->data != NULL);
    assert(arr->size == 0);
    assert(arr->data_size == sizeof(int));

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
    assert(IntArray_get(arr, Array_size(arr) - 1) == 98);
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
    Array* arr = Array_create(sizeof(Person), 5);
    assert(arr != NULL);
    assert(arr->capacity == 5);
    assert(arr->data != NULL);
    assert(arr->size == 0);
    assert(arr->data_size == sizeof(Person));

    // Test basics
    assert(Array_size(arr) == 0);
    assert(Array_capacity(arr) == 5);
    assert(Array_is_empty(arr) == true);
    assert(Array_is_full(arr) == false);

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

    Person* temp = (Person*)malloc(sizeof(Person));

    // Test appending
    Array_append(arr, &renee);  // {renee}
    assert(Array_size(arr) == 1);
    temp = (Person*)Array_get(arr, 0);
    assert(temp->age == renee.age);
    assert(temp->height == renee.height);
    assert(strcmp(temp->name, renee.name) == 0);

    // Test inserting
    Array_insert(arr, 0, &tj);  // insert in front {tj, renee}
    Array_insert(arr, Array_size(arr),
                 &hunter);        // insert at back {tj, renee, hunter}
    Array_insert(arr, 1, &anna);  // insert in middle {tj, anna, renee, hunter}

    assert(Array_size(arr) == 4);
    temp = (Person*)Array_get(arr, 0);
    assert(strcmp(temp->name, tj.name) == 0);
    temp = (Person*)Array_get(arr, Array_size(arr) - 1);
    assert(strcmp(temp->name, hunter.name) == 0);
    temp = (Person*)Array_get(arr, 1);
    assert(strcmp(temp->name, anna.name) == 0);

    // Test removing
    Array_remove(arr, 1);  // remove middle {tj, renee, hunter}
    Array_remove(arr, Array_size(arr) - 1);  // remove back {tj renee}
    Array_remove(arr, 0);                    // remove front {renee}

    assert(Array_size(arr) == 1);
    temp = (Person*)Array_get(arr, 0);
    assert(strcmp(temp->name, renee.name) == 0);

    // Test setting
    Array_set(arr, 0, &brewski);
    assert(Array_size(arr) == 1);
    temp = (Person*)Array_get(arr, 0);
    assert(strcmp(temp->name, brewski.name) == 0);

    // Test clearing
    Array_clear(arr);
    assert(arr != NULL);
    assert(Array_size(arr) == 0);
    assert(Array_capacity(arr) == 0);

    Person people[] = {renee, tj, hunter, anna, emily, brewski};
    Person sorted[] = {brewski, hunter, anna, renee, tj, emily};

    // Test adding a bunch of vals
    for (size_t i = 0; i < 6; i++) {
        Array_append(arr, &people[i]);
        assert(Array_size(arr) == (i + 1));
        temp = (Person*)Array_get(arr, i);
        assert(strcmp(temp->name, people[i].name) == 0);
    }

    // Test find
    assert(Array_find(arr, &anna) == 3);

    // Test sort
    Array_sort(arr, compare_person);
    for (size_t i = 0; i < 6; i++) {
        temp = (Person*)Array_get(arr, i);
        assert(strcmp(temp->name, sorted[i].name) == 0);
    }

    Array_iterate(arr, new_year);
    for (size_t i = 0; i < 6; i++) {
        temp = (Person*)Array_get(arr, i);
        assert(temp->age == (sorted[i].age + 1));
    }

    // Test Delete
    Array_destroy(&arr);
    assert(arr == NULL);
}