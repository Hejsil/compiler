//
// Created by jimmi on 12/21/16.
//

#ifndef GOODLANG_POSITION_H
#define GOODLANG_POSITION_H

#include <stdint.h>

typedef struct {
    char* source;
    int64_t index;
    int64_t line;
    int64_t column;
} Position;

#endif //GOODLANG_POSITION_H
