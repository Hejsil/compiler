//
// Created by jimmi on 12/21/16.
//

#include <stdlib.h>
#include <memory.h>
#include "string.h"

char* allocate_string_copy_without_strlen(char *string, int64_t length) {
    char* result = malloc(length + 1);
    memcpy(result, string, length);
    result[length] = '\0';

    return result;
}

char* allocate_string_copy(char* string) {
    return allocate_string_copy_without_strlen(string, strlen(string));
}
