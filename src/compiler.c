//
// Created by jimmi on 12/19/16.
//

#include <stdlib.h>
#include "compiler.h"
#include "basic/string.h"
#include "basic/file.h"

void init_compiler(Compiler* compiler) {
    dynamic_array_init(&compiler->file_names, sizeof(char*), 16);
    dynamic_array_init(&compiler->scanners, sizeof(Scanner), 16);
}

bool make_scanner_from_file(Compiler* compiler, char* filename, int64_t filename_length) {
    char* content = read_all_text_from_file(filename);

    if (content == NULL)
        return false;

    Scanner scanner;
    init_scanner(&scanner, allocate_string_copy(filename, filename_length), content);
    dynamic_array_add_last(&compiler->scanners, &scanner);
    dynamic_array_add_last(&compiler->file_names, &scanner.position.source);

    return true;
}

void make_scanner_from_text(Compiler* compiler, char* text, int64_t text_length) {
    Scanner scanner;
    init_scanner(&scanner, NULL, allocate_string_copy(text, text_length));
    dynamic_array_add_last(&compiler->scanners, &scanner);
}

void deinit_compiler(Compiler *compiler) {
    while (compiler->file_names.count != 0) {
        char* file_name;
        dynamic_array_get_last(&compiler->file_names, &file_name);
        dynamic_array_remove_last(&compiler->file_names);
        free(file_name);
    }

    while (compiler->scanners.count != 0) {
        Scanner scanner;
        dynamic_array_get_last(&compiler->scanners, &scanner);
        dynamic_array_remove_last(&compiler->scanners);

        deinit_scanner(&scanner);
    }

    dynamic_array_deinit(&compiler->file_names);
    dynamic_array_deinit(&compiler->scanners);
}
