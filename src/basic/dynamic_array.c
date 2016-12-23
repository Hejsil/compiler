//
// Created by jimmi on 12/23/16.
//

#include "dynamic_array.h"

void dynamic_array_init(Dynamic_Array *array, int64_t element_size, int64_t capacity) {
    assert(capacity > 0);
    assert(element_size > 0);

    array->count = 0;
    array->element_size = element_size;
    array->capacity = capacity;
    array->data = malloc(element_size * capacity);
}

void dynamic_array_deinit(Dynamic_Array *array) {
    assert(array->capacity > 0);
    assert(array->element_size > 0);
    assert(array->data != NULL);

    array->count = 0;
    array->element_size = 0;
    array->capacity = 0;
    free(array->data);
    array->data = NULL;
}

void dynamic_array_add(Dynamic_Array *array, int64_t index, void *element) {
    assert(index >= 0);
    assert(array->element_size > 0);
    assert(array->capacity > 0);
    assert(array->count >= index);
    assert(array->count <= array->capacity);

    if (array->capacity == array->count) {
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * array->element_size);
    }

    memmove(&array->data[(index + 1) * array->element_size],
           &array->data[index * array->element_size],
           (array->count - index) * array->element_size);
    memcpy(&array->data[index * array->element_size], element, array->element_size);
    array->count++;
}

void inline dynamic_array_add_last(Dynamic_Array *array, void *element) {
    dynamic_array_add(array, array->count, element);
}

void dynamic_array_remove(Dynamic_Array *array, int64_t index) {
    assert(index >= 0);
    assert(array->element_size > 0);
    assert(array->count > 0);
    assert(index < array->count);
    array->count--;
    memmove(&array->data[index * array->element_size],
           &array->data[(index + 1) * array->element_size],
           (array->count - index) * array->element_size);

#if !NDEBUG
    memset(&array->data[array->count * array->element_size], 0, array->capacity - array->count);
#endif
}

void inline dynamic_array_remove_last(Dynamic_Array *array) {
    dynamic_array_remove(array, array->count - 1);
}

void dynamic_array_get(Dynamic_Array *array, int64_t index, void *result) {
    assert(array->element_size > 0);
    assert(index >= 0);
    assert(index < array->count);
    memcpy(result, array->data + (index * array->element_size), array->element_size);
}

void inline dynamic_array_get_last(Dynamic_Array *array, void *result) {
    dynamic_array_get(array, array->count - 1, result);
}
