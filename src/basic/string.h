//
// Created by jimmi on 12/21/16.
//

#ifndef GOODLANG_STRING_H
#define GOODLANG_STRING_H

#include <stdint.h>

char* allocate_string_copy_without_strlen(char* string, int64_t length);
char* allocate_string_copy(char* string);

#endif //GOODLANG_STRING_H
