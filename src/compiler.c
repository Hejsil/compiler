//
// Created by jimmi on 12/19/16.
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "basic/file.h"
#include "basic/string.h"

void init_compiler(Compiler* compiler) {
    compiler->scanner_capacity = 2;
    compiler->scanner_count = 0;
    compiler->scanners = malloc(sizeof(Scanner) * compiler->scanner_capacity);

    compiler->sources_capacity = 2;
    compiler->scanner_count = 0;
    compiler->sources = malloc(sizeof(char*) * compiler->sources_capacity);
}

Scanner* allocate_next_scanner(Compiler* compiler, char* filename, int64_t length) {
    assert(compiler->scanner_capacity > 0);
    assert(compiler->scanner_count <= compiler->scanner_capacity);
    if (compiler->scanner_count == compiler->scanner_capacity) {
        compiler->scanner_capacity *= 2;
        compiler->scanners = realloc(compiler->scanners, sizeof(Scanner) * compiler->scanner_capacity);
    }

    assert(compiler->sources_capacity > 0);
    assert(compiler->sources_count <= compiler->sources_capacity);
    if (compiler->sources_count == compiler->sources_capacity) {
        compiler->sources_capacity *= 2;
        compiler->sources = realloc(compiler->sources, sizeof(char*) * compiler->sources_capacity);
    }

    Scanner* scanner = &compiler->scanners[compiler->scanner_count];

    // We copy the filename, to make sure that the compiler has ownership
    // of this piece of memory. Filenames are needed throught the whole compiler
    // to report errors.
    compiler->sources[compiler->sources_count] = allocate_string_copy(filename, length);
    scanner->position.source = compiler->sources[compiler->sources_count];
    scanner->position.index = 0;
    scanner->position.line = 1;
    scanner->position.column = 1;

    compiler->sources_count++;
    compiler->scanner_count++;

    return scanner;
}

bool make_scanner_from_file(Compiler* compiler, char* filename, int64_t filename_length) {
    char* content = read_all_text_from_file(filename);

    if (content == NULL)
        return false;

    Scanner* scanner = allocate_next_scanner(compiler, filename, filename_length);
    scanner->text_to_scan = content;

    return true;
}

void make_scanner_from_text(Compiler* compiler, char* text, int64_t text_length) {
    Scanner* scanner = allocate_next_scanner(compiler, NULL, 0);
    scanner->text_to_scan = allocate_string_copy(text, text_length);
}

void deinit_compiler(Compiler *compiler) {
    for (int i = 0; i < compiler->sources_count; ++i) {
        free(compiler->sources[i]);
    }

    free(compiler->sources);
    free(compiler->scanners);
    compiler->scanner_count = 0;
    compiler->scanner_capacity = 0;
    compiler->sources_count = 0;
    compiler->sources_capacity = 0;
}

bool pop_scanner(Compiler* compiler, Scanner* result) {
    if (compiler->scanner_count <= 0) {
        return false;
    }

    compiler->scanner_count--;
    (*result) = compiler->scanners[compiler->scanner_count];

    return true;
}
