//
// Created by jimmi on 12/25/16.
//

#include "position.h"

void init_position(Position *position, char *source) {
    position->source = source;
    position->column = 0;
    position->line = 0;
    position->index = 0;
}