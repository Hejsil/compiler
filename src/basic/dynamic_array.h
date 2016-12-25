//
// Created by jimmi on 12/23/16.
//

#ifndef COMPILER_DYNAMIC_ARRAY_H
#define COMPILER_DYNAMIC_ARRAY_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

typedef struct {
    // OWN
    int8_t* data;
    int64_t count, capacity, element_size;
} Dynamic_Array;

void dynamic_array_init(Dynamic_Array* array, int64_t element_size, int64_t capacity);
void dynamic_array_deinit(Dynamic_Array *array);
void* dynamic_array_allocate_at(Dynamic_Array* array, int64_t index);
void* dynamic_array_allocate_next(Dynamic_Array* array);
void dynamic_array_add(Dynamic_Array* array, int64_t index, void* element);
void dynamic_array_add_last(Dynamic_Array* array, void* element);
void dynamic_array_remove(Dynamic_Array* array, int64_t index);
void dynamic_array_remove_last(Dynamic_Array* array);
void dynamic_array_get(Dynamic_Array* array, int64_t index, void* result);
void* dynamic_array_get_ptr(Dynamic_Array* array, int64_t index);
void dynamic_array_get_last(Dynamic_Array* array, void* result);
void* dynamic_array_get_ptr_last(Dynamic_Array* array);




#endif //COMPILER_DYNAMIC_ARRAY_H
