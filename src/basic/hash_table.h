//
// Created by jimmi on 12/26/16.
//

#ifndef COMPILER_HASH_TABLE_H
#define COMPILER_HASH_TABLE_H

#include <stdbool.h>
#include "dynamic_array.h"

typedef struct {
    Dynamic_Array hashes;
    Dynamic_Array elements;
    int64_t (*get_hash)(void*);
    bool (*are_equal)(void*, void*);
} Hash_Table;

void hash_table_init(Hash_Table* table, int64_t element_size, int64_t (*get_hash)(void*), bool (*are_equal)(void*, void*));
void hash_table_deinit(Hash_Table* table);
int64_t hash_table_get_index(Hash_Table* table, void* element);
bool hash_table_contains(Hash_Table* table, void* element);
bool hash_table_add(Hash_Table* table, void* element);
bool hash_table_remove(Hash_Table* table, void* element);
void hash_table_remove_at(Hash_Table* table, int64_t index);


#endif //COMPILER_HASH_TABLE_H
