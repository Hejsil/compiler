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

void* dynamic_array_allocate_at(Dynamic_Array *array, int64_t index) {
    assert(index >= 0);
    assert(array->element_size > 0);
    assert(array->capacity > 0);
    assert(array->count >= index);
    assert(array->count <= array->capacity);

    if (array->capacity == array->count) {
        array->capacity *= 2;
        array->data = realloc(array->data, array->capacity * array->element_size);
    }

    memmove(dynamic_array_unsafe_get_ptr(array, index + 1),
            dynamic_array_unsafe_get_ptr(array, index),
            (array->count - index) * array->element_size);
    return dynamic_array_unsafe_get_ptr(array, index);
}

void* dynamic_array_allocate_next(Dynamic_Array *array) {
    return dynamic_array_allocate_at(array, array->count);
}

void dynamic_array_add(Dynamic_Array *array, int64_t index, void *element) {
    dynamic_array_allocate_at(array, index);
    memcpy(dynamic_array_unsafe_get_ptr(array, index), element, array->element_size);
    array->count++;
}

void dynamic_array_add_last(Dynamic_Array *array, void *element) {
    dynamic_array_add(array, array->count, element);
}

void dynamic_array_remove(Dynamic_Array *array, int64_t index) {
    assert(index >= 0);
    assert(array->element_size > 0);
    assert(array->count > 0);
    assert(index < array->count);
    array->count--;
    memmove(dynamic_array_unsafe_get_ptr(array, index),
            dynamic_array_unsafe_get_ptr(array, index + 1),
            (array->count - index) * array->element_size);

#if !NDEBUG
    memset(dynamic_array_unsafe_get_ptr(array, array->count), 0, array->capacity - array->count);
#endif
}

void dynamic_array_remove_last(Dynamic_Array *array) {
    dynamic_array_remove(array, array->count - 1);
}

void dynamic_array_get(Dynamic_Array *array, int64_t index, void* result) {
    assert(array->element_size > 0);
    assert(index >= 0);
    assert(index < array->count);
    memcpy(result, dynamic_array_unsafe_get_ptr(array, index), array->element_size);
}

void* dynamic_array_get_ptr(Dynamic_Array *array, int64_t index) {
    assert(array->element_size > 0);
    assert(index >= 0);
    assert(index < array->count);
    return dynamic_array_unsafe_get_ptr(array, index);
}

void dynamic_array_get_last(Dynamic_Array *array, void* result) {
    dynamic_array_get(array, array->count - 1, result);
}

void* dynamic_array_get_ptr_last(Dynamic_Array *array) {
    return dynamic_array_get_ptr(array, array->count - 1);
}

void* dynamic_array_unsafe_get_ptr(Dynamic_Array *array, int64_t index) {
    return &array->data[index * array->element_size];
}
