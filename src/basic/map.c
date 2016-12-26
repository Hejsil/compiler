//
// Created by jimmi on 12/26/16.
//

#include "map.h"

void map_init(Map* map, int64_t key_size, int64_t value_size, int64_t (*get_hash)(void*),
              bool (*are_equal)(void*, void*)) {
    hash_table_init(&map->keys, key_size, get_hash, are_equal);
    dynamic_array_init(&map->values, value_size, 2);
}

void map_deinit(Map* map) {
    hash_table_deinit(&map->keys);
    dynamic_array_deinit(&map->values);
}

bool map_add(Map* map, void* key, void* value) {
    bool success = hash_table_add(&map->keys, key);

    if (!success) {
        return false;
    }

    dynamic_array_add_last(&map->values, value);

    return true;
}

bool map_remove(Map* map, void* key) {
    int64_t index = hash_table_get_index(&map->keys, key);

    if (index == -1) {
        return false;
    }

    hash_table_remove_at(&map->keys, index);
    dynamic_array_remove(&map->values, index);

    return true;
}

bool map_contains_key(Map* map, void* key) {
    return hash_table_contains(&map->keys, key);
}

bool map_get_value(Map *map, void *key, void *result) {
    int64_t index = hash_table_get_index(&map->keys, key);

    if (index == -1) {
        return false;
    }

    dynamic_array_get(&map->values, index, result);

    return true;
}


