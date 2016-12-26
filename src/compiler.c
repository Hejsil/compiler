//
// Created by jimmi on 12/19/16.
//

#include <stdlib.h>
#include "compiler.h"
#include "basic/string.h"
#include "basic/file.h"
#include "basic/message.h"

void compiler_init(Compiler *compiler) {
    dynamic_array_init(&compiler->file_names, sizeof(char*), 16);
    dynamic_array_init(&compiler->scanners, sizeof(Scanner), 16);
    dynamic_array_init(&compiler->messages, sizeof(Message), 16);
}

bool compiler_add_scanner_from_file(Compiler *compiler, char *filename, int64_t filename_length) {
    char* content = read_all_text_from_file(filename);

    if (content == NULL)
        return false;

    Scanner* scanner = dynamic_array_allocate_next(&compiler->scanners);
    scanner_init(scanner, allocate_string_copy_without_strlen(filename, filename_length), content);
    dynamic_array_add_last(&compiler->file_names, &scanner->position.source);

    return true;
}

void compiler_add_scanner_from_text(Compiler *compiler, char *text, int64_t text_length) {
    Scanner* scanner = dynamic_array_allocate_next(&compiler->scanners);
    scanner_init(scanner, NULL, allocate_string_copy_without_strlen(text, text_length));
}

void compiler_deinit(Compiler *compiler) {
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

        scanner_deinit(&scanner);
    }

    dynamic_array_deinit(&compiler->file_names);
    dynamic_array_deinit(&compiler->scanners);
}

void compiler_add_message(Compiler *compiler, Position position, uint8_t type, char *string) {
    Message message;
    message_init(&message, position, type, string);
    dynamic_array_add_last(&compiler->messages, &message);
}
