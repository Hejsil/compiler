//
// Created by jimmi on 12/26/16.
//

#include "hash_table.h"

void hash_table_init(Hash_Table *table, int64_t element_size, int64_t (*get_hash)(void*),
                     bool (*are_equal)(void*, void*)) {
    dynamic_array_init(&table->elements, element_size, 2);
    dynamic_array_init(&table->hashes, sizeof(int64_t), 2);
    table->are_equal = are_equal;
    table->get_hash = get_hash;
}

void hash_table_deinit(Hash_Table *table) {
    dynamic_array_deinit(&table->elements);
    dynamic_array_deinit(&table->hashes);
}

int64_t hash_table_get_index(Hash_Table* table, void* element) {
    int64_t element_hash = table->get_hash(element);

    for (int64_t i = 0; i < table->hashes.count; ++i) {
        int64_t hash;
        dynamic_array_get(&table->hashes, i, &hash);

        if (element_hash == hash &&
            table->are_equal(element, dynamic_array_get_ptr(&table->elements, i))) {
            return i;
        }
    }

    return -1;
}

bool hash_table_contains(Hash_Table *table, void *element) {
    return hash_table_get_index(table, element) != -1;
}


bool hash_table_add(Hash_Table* table, void* element) {
    if (hash_table_contains(table, element)) {
        return false;
    }

    int64_t element_hash = table->get_hash(element);
    dynamic_array_add_last(&table->hashes, &element_hash);
    dynamic_array_add_last(&table->elements, element);

    return true;
}

bool hash_table_remove(Hash_Table* table, void* element) {
    int64_t element_index = hash_table_get_index(table, element);

    if (element_index == -1) {
        return false;
    }

    dynamic_array_remove(&table->elements, element_index);
    dynamic_array_remove(&table->hashes, element_index);
}

void hash_table_remove_at(Hash_Table* table, int64_t index) {
    dynamic_array_remove(&table->hashes, index);
    dynamic_array_remove(&table->elements, index);
}
