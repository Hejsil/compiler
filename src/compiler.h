//
// Created by jimmi on 12/19/16.
//

#ifndef GOODLANG_COMPILER_H
#define GOODLANG_COMPILER_H

#include <stdbool.h>
#include <sys/stat.h>
#include "syntax/scanning.h"
#include "basic/dynamic_array.h"
#include "basic/map.h"

typedef struct {
    // Elements: char*
    Dynamic_Array file_names;

    // Elements: Scanner
    Dynamic_Array scanners;

    // Elements: Message
    Dynamic_Array messages;
} Compiler;

void compiler_init(Compiler *compiler);
void compiler_deinit(Compiler *compiler);
void compiler_add_message(Compiler *compiler, Position position, uint8_t type, char* string);
bool compiler_add_scanner_from_file(Compiler *compiler, char* filename, int64_t length);
void compiler_add_scanner_from_text(Compiler *compiler, char* text, int64_t text_length);

#endif //GOODLANG_COMPILER_H
