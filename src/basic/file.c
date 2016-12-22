//
// Created by jimmi on 12/21/16.
//

#include <sys/stat.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"

int64_t get_file_size(char* filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1;
}

char* read_all_text_from_file(char* filename) {
    FILE* file;
    int64_t file_size = get_file_size(filename);

    if (file_size == -1)
        return NULL;

    file = fopen(filename, "r");

    char* result = malloc(file_size);
    fread(result, 1, file_size, file);

    fclose(file);

    return result;
}
