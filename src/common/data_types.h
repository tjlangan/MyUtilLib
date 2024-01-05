#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdio.h>

// Enums for various error codes. More to be added later
typedef enum {
    NO_ERROR = 0,
    ERROR = 1,
    ERROR_NULL = 2,
    ERROR_INDEX = 3,
    ERROR_ALLOCATION = 4,
    ERROR_NOT_FOUND = 5,
} ErrorCode;

// Structure representing a generic data type
typedef struct GenericDataType {
    size_t size;  // data size to be used in malloc
    void* data;   // pointer to the data

} T;

// Structure representing a generic Array
typedef struct ArrayDataType {
    size_t size;       ///< Current number of elements in the Array
    size_t capacity;   ///< Maximum capacity of the Array
    size_t data_size;  // data size to be used in malloc
    T* values;         ///< Pointer to the array of GenericDataType
} Array;

typedef struct ReturnErrorCode {
    ErrorCode error;
} ReturnError;

typedef struct ReturnGenericDataType {
    ErrorCode error;
    T* value;
} ReturnData;

typedef struct ReturnArrayType {
    ErrorCode error;
    Array* arr;
} ReturnArray;

typedef struct ReturnBoolType {
    ErrorCode error;
    bool value;
} ReturnBool;

typedef struct ReturnSizeTType {
    ErrorCode error;
    size_t value;
} ReturnSizeT;

/**
 * @brief Comparison function type for custom sorting.
 *
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @return A negative value if a should come before b, zero if a and b are
 * equal, or a positive value if a should come after b.
 */
typedef int (*CompareFunction)(const T* a, const T* b);

#endif