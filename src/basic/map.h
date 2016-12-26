//
// Created by jimmi on 12/26/16.
//

#ifndef COMPILER_MAP_H
#define COMPILER_MAP_H

#include "hash_table.h"

typedef struct {
    Hash_Table keys;
    Dynamic_Array values;
} Map;

void map_init(Map* map, int64_t key_size, int64_t value_size, int64_t (*get_hash)(void*), bool (*are_equal)(void*, void*));
void map_deinit(Map* map);
bool map_add(Map* map, void* key, void* value);
bool map_remove(Map* map, void* key);
bool map_contains_key(Map* map, void* key);
bool map_get_value(Map* map, void* key, void* result);

#endif //COMPILER_MAP_H
