//
// Created by jimmi on 12/19/16.
//

#ifndef GOODLANG_COMPILER_H
#define GOODLANG_COMPILER_H

#include <stdbool.h>
#include <sys/stat.h>
#include "syntax/scanning.h"
#include "basic/dynamic_array.h"

typedef struct {
    // Elements: char*
    Dynamic_Array file_names;

    // Elements: Scanner
    Dynamic_Array scanners;
} Compiler;

void init_compiler(Compiler* compiler);
void deinit_compiler(Compiler* compiler);
bool make_scanner_from_file(Compiler* compiler, char* filename, int64_t length);
void make_scanner_from_text(Compiler* compiler, char* text, int64_t text_length);
bool pop_scanner(Compiler* compiler, Scanner* result);

#endif //GOODLANG_COMPILER_H
