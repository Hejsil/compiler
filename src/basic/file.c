//
// Created by jimmi on 12/21/16.
//

#include <sys/stat.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "file.h"

int64_t get_file_size(char* filename) {
    struct stat file_stat;

    if (stat(filename, &file_stat) == 0)
        return file_stat.st_size;

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

bool is_same_file(char *file1, char *file2) {
    struct stat file1_stat, file2_stat;
    stat(file1, &file1_stat);
    stat(file2, &file2_stat);

    return file1_stat.st_ino == file2_stat.st_ino;
}
