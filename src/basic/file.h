//
// Created by jimmi on 12/21/16.
//


#ifndef GOODLANG_FILE_H
#define GOODLANG_FILE_H

#include <stdint.h>
#include <stdbool.h>

bool is_same_file(char* file1, char* file2);
int64_t get_file_size(char* filename);
char* read_all_text_from_file(char* filename);

#endif //GOODLANG_FILE_H
