//
// Created by jimmi on 12/19/16.
//

#ifndef GOODLANG_COMPILER_H
#define GOODLANG_COMPILER_H

#include <stdbool.h>
#include "syntax/scanning.h"

typedef struct {
    // OWN: The compiler owns both levels pointers
    char** sources;
    int64_t sources_capacity;
    int64_t sources_count;

    // OWN:
    Scanner* scanners;
    int64_t scanner_capacity;
    int64_t scanner_count;
} Compiler;

void init_compiler(Compiler* compiler);
void deinit_compiler(Compiler* compiler);
Scanner* allocate_next_scanner(Compiler* compiler, char* filename, int64_t length);
bool make_scanner_from_file(Compiler* compiler, char* filename, int64_t length);
void make_scanner_from_text(Compiler* compiler, char* text, int64_t text_length);
bool pop_scanner(Compiler* compiler, Scanner* result);

#endif //GOODLANG_COMPILER_H
