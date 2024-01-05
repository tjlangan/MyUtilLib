#include "array.h"

ReturnArray Array_create(size_t data_size, size_t capacity) {
    ReturnArray result = {.error = NO_ERROR, .arr = NULL};

    // Check valid arguments
    if (data_size == 0 || capacity == 0) {
        result.error = ERROR;
        return result;
    }

    // Allocate memory and check for NULL
    Array* arr = (Array*)malloc(sizeof(Array));
    if (arr == NULL) {
        result.error = ERROR_ALLOCATION;
        return result;
    }

    // Assign arguments to array params
    arr->size = 0;
    arr->capacity = capacity;
    arr->data_size = data_size;

    // Allocate memory and check for NULL
    arr->values = (T*)malloc(capacity * sizeof(T));
    if (arr->values == NULL) {
        result.error = ERROR_ALLOCATION;
        free(arr);
        return result;
    }

    // For each element in array allocate memory and check for NULL
    for (size_t i = 0; i < capacity; i++) {
        arr->values[i].size = data_size;
        arr->values[i].data = malloc(data_size);
        if (arr->values[i].data == NULL) {
            result.error = ERROR_ALLOCATION;

            // Free allocated memory
            for (size_t j = 0; j < i; j++) {
                free(arr->values[j].data);
            }
            free(arr->values);
            free(arr);
            return result;
        }
    }

    // Everything went good
    result.arr = arr;

    return result;
}

ReturnError Array_destroy(Array** arr) {
    ReturnError result = {.error = NO_ERROR};

    if (*arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    for (size_t i = 0; i < (*arr)->capacity; i++) {
        free((*arr)->values[i].data);
    }
    free((*arr)->values);
    free(*arr);
    *arr = NULL;

    return result;
}

ReturnError Array_append(Array* arr, T* element) {
    ReturnError result = {.error = NO_ERROR};

    // Check if array or element is NULL
    if (arr == NULL || element == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    // Check if array is full and check for errors
    ReturnBool is_full_result = Array_is_full(arr);
    if (is_full_result.error > 0) {
        result.error = is_full_result.error;
        return result;
    }

    // If array is full, resize it and check for errors
    if (is_full_result.value == true) {
        ReturnError resize_result = Array_resize(arr, arr->capacity * 2 + 1);
        if (resize_result.error > 0) {
            result.error = resize_result.error;
            return result;
        }
    }

    // Set the last value in the array to the element and check for errors
    ReturnError set_result = Array_set(arr, arr->size, element);
    if (set_result.error > 0) {
        result.error = set_result.error;
        return result;
    }

    // increment size counter
    arr->size += 1;

    return result;
}

ReturnError Array_insert(Array* arr, size_t index, T* element) {
    ReturnError result = {.error = NO_ERROR};

    // Check if array or element is NULL
    if (arr == NULL || element == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    // Check index is in bounds
    if (index > arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    // Check if array is full
    ReturnBool is_full_result = Array_is_full(arr);
    if (is_full_result.error > 0) {
        result.error = is_full_result.error;
        return result;
    }

    // if array is full resize it
    if (is_full_result.value == true) {
        ReturnError resize_result = Array_resize(arr, arr->capacity * 2 + 1);
        if (resize_result.error > 0) {
            result.error = resize_result.error;
            return result;
        }
    }

    ReturnData get_result;
    ReturnError set_result;

    // Loop starting at end shifting elements to the right
    for (size_t i = arr->size; i > index; i--) {
        get_result = Array_get(arr, i - 1);
        if (get_result.error > 0) {
            result.error = get_result.error;
            return result;
        }
        set_result = Array_set(arr, i, get_result.value);
        if (set_result.error > 0) {
            result.error = set_result.error;
            return result;
        }
    }

    // Set the element at specified index
    set_result = Array_set(arr, index, element);
    if (set_result.error > 0) {
        result.error = set_result.error;
        return result;
    }

    // increment counter
    arr->size += 1;

    return result;
}

ReturnError Array_remove(Array* arr, size_t index) {
    ReturnError result = {.error = NO_ERROR};

    // Check if array is null
    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    if (index >= arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    ReturnData get_result;
    ReturnError set_result;

    // Loop start at index and shift to left
    for (size_t i = index; i < arr->size - 1; i++) {
        get_result = Array_get(arr, i + 1);
        if (get_result.error > 0) {
            result.error = get_result.error;
            return result;
        }
        set_result = Array_set(arr, i, get_result.value);
        if (set_result.error > 0) {
            result.error = set_result.error;
            return result;
        }
    }

    // idk if this will work
    T temp;
    temp.size = arr->data_size;
    temp.data = &(int){0};

    set_result = Array_set(arr, arr->size - 1, &temp);
    if (set_result.error > 0) {
        result.error = set_result.error;
        return result;
    }

    // decrement size counter
    arr->size -= 1;

    return result;
}

ReturnData Array_get(const Array* arr, size_t index) {
    ReturnData result = {.error = NO_ERROR, .value = NULL};

    if (arr == NULL || arr->values == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    if (index >= arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    // who tf knows
    // return &((const char*)arr->data)[index * arr->data_size];
    result.value = &(arr->values[index]);

    return result;
}

ReturnError Array_set(Array* arr, size_t index, T* element) {
    ReturnError result = {.error = NO_ERROR};

    if (arr == NULL || element == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    if (index >= arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    if (element->size != arr->data_size) {
        result.error = ERROR;
        return result;
    }

    arr->values[index].size = element->size;
    memcpy(arr->values[index].data, element->data, element->size);

    return result;

    // if (arr != NULL && arr->data != NULL && index <= arr->size) {
    //     memcpy(&((char*)arr->data)[index * arr->data_size], element,
    //            arr->data_size);
    // }
}

ReturnSizeT Array_find(const Array* arr, T* element) {
    ReturnSizeT result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL || arr->values == NULL || element == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    for (size_t i = 0; i < arr->size; i++) {
        if (memcmp(&(arr->values[i]), element, arr->data_size) == 0) {
            result.value = i;
            break;
        }
    }

    // Assume nobody has a 18 quintillion long array
    if (result.value == SIZE_MAX) {
        result.error = ERROR_NOT_FOUND;
    }

    return result;
}

ReturnSizeT Array_size(const Array* arr) {
    ReturnSizeT result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    result.value = arr->size;
    return result;
}

ReturnSizeT Array_capacity(const Array* arr) {
    ReturnSizeT result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    result.value = arr->capacity;
    return result;
}

ReturnBool Array_is_empty(const Array* arr) {
    ReturnBool result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    result.value = arr->size == 0;
    return result;
}

ReturnBool Array_is_full(const Array* arr) {
    ReturnBool result = {.error = NO_ERROR, .value = SIZE_MAX};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    result.value = arr->size == arr->capacity;
    return result;
}

ReturnError Array_resize(Array* arr, size_t new_capacity) {
    ReturnError result = {.error = NO_ERROR};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    // might wanna check that new_capacity isnt like 100 quadrillion or some
    // stupid large number

    // Re-allocate new_values array
    T* new_values = (T*)realloc(arr->values, new_capacity * sizeof(T));
    if (new_values == NULL) {
        result.error = ERROR_ALLOCATION;
        return result;
    }

    // free or allocate T.data pointers whether the array is shrinking or
    // growing
    if (new_capacity < arr->capacity) {
        for (size_t i = new_capacity; i < arr->capacity; i++) {
            free(arr->values[i].data);
            arr->values[i].data = NULL;
        }
    } else {
        for (size_t i = arr->capacity; i < new_capacity; i++) {
            new_values[i].size = arr->data_size;
            new_values[i].data = mallloc(arr->data_size);
            if (new_values[i].data == NULL) {
                result.error = ERROR_ALLOCATION;
                return result;
            }
        }
    }

    // Assign new values
    if (new_capacity < arr->size) {
        arr->size = new_capacity;
    }
    arr->capacity = new_capacity;
    arr->values = new_values;

    return result;
}

ReturnError Array_clear(Array* arr) {
    ReturnError result = {.error = NO_ERROR};

    if (arr == NULL || arr->values == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    // Free the T.data pointers
    for (size_t i = 0; i < arr->capacity; i++) {
        free(arr->values[i].data);
        arr->values[i].data = NULL;
    }

    // Free Array.values and set counters to 0
    free(arr->values);
    arr->values = NULL;
    arr->size = 0;
    arr->capacity = 0;

    return result;
}

ReturnError Array_iterate(const Array* arr, CallbackFunction callback) {
    ReturnError result = {.error = NO_ERROR};

    if (arr == NULL || callback == NULL) {
        result.error == ERROR_NULL;
        return result;
    }

    ReturnData get_result;
    for (size_t i = 0; i < arr->size; i++) {
        get_result = Array_get(arr, i);
        if (get_result.error > 0) {
            result.error = get_result.error;
            return result;
        }
        callback(get_result.value);
    }
}

ReturnError Array_swap(Array* arr, size_t index_a, size_t index_b) {
    ReturnError result = {.error = NO_ERROR};

    if (arr == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    if (index_a >= arr->size || index_b >= arr->size) {
        result.error = ERROR_INDEX;
        return result;
    }

    // Allocate a temp variable
    T* temp = (T*)malloc(sizeof(T));
    if (temp == NULL) {
        result.error = ERROR_ALLOCATION;
        return result;
    }
    temp->data = malloc(arr->data_size);
    if (temp->data == NULL) {
        result.error = ERROR_ALLOCATION;
        return result;
    }

    // Get value at index a
    ReturnData get_result;
    get_result = Array_get(arr, index_a);
    if (get_result.error > 0) {
        result.error = get_result.error;
        return result;
    }

    // assign temp = a
    temp->size = get_result.value->size;
    memcpy(temp->data, get_result.value->data, get_result.value->size);

    // get value at index b
    get_result = Array_get(arr, index_b);
    if (get_result.error > 0) {
        result.error = get_result.error;
        return result;
    }

    // Set index a = value b
    ReturnError set_result;
    set_result = Array_set(arr, index_a, get_result.value);
    if (set_result.error > 0) {
        result.error = set_result.error;
        return result;
    }

    // Set index b = value a (temp)
    set_result = Array_set(arr, index_b, temp);
    if (set_result.error > 0) {
        result.error = set_result.error;
        return result;
    }

    // Free temp
    free(temp->data);
    free(temp);

    return result;
}

static size_t partition(Array* arr, size_t low, size_t high,
                        CompareFunction compare) {
    ReturnData get_result;
    get_result = Array_get(arr, high);
    T* pivot = get_result.value;
    size_t i = low - 1;

    for (size_t j = low; j < high; j++) {
        get_result = Array_get(arr, j);
        if (compare(get_result.value, pivot) < 0) {
            i++;
            Array_swap(arr, i, j);
        }
    }

    Array_swap(arr, i + 1, high);
    return i + 1;
}

static void quick_sort(Array* arr, size_t low, size_t high,
                       CompareFunction compare) {
    if (low < high) {
        size_t pi = partition(arr, low, high, compare);

        if (pi > 0) {
            quick_sort(arr, low, pi - 1, compare);
        }

        quick_sort(arr, pi + 1, high, compare);
    }
}

ReturnError Array_sort(Array* arr, CompareFunction compare) {
    ReturnError result = {.error = NO_ERROR};

    if (arr == NULL || compare == NULL) {
        result.error = ERROR_NULL;
        return result;
    }

    if (arr != NULL && compare != NULL) {
        quick_sort(arr, 0, arr->size - 1, compare);
    }
}