#ifndef GENERICS_H
#define GENERICS_H

#include <stddef.h>

typedef struct GenericType {
    bool null;
    size_t data_size;
    void* data;
} T;

#endif