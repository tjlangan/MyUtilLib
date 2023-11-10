#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct Array_t {
    unsigned int count;
    unsigned int capacity;
    bool error;
    int* values;
} Array;

Array* create(unsigned int capacity);
int destroy(Array** arr);

bool is_empty(Array* arr);
bool is_full(Array* arr);
bool in_bounds(Array* arr, unsigned int index);

int get_count(Array* arr);
int get_capacity(Array* arr);
bool get_error(Array* arr);

int first(Array* arr);
int last(Array* arr);

int index_of(Array* arr, int value);
int value_at(Array* arr, unsigned int index);
int insert_at(Array* arr, unsigned int index, int value);
int remove_at(Array* arr, unsigned int index);

int append(Array* arr, int value);
int swap(Array* arr, unsigned int index_a, unsigned int index_b);
int fill(Array* arr, int value);

int increase_capacity(Array* arr);

#endif