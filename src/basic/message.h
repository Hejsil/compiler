//
// Created by jimmi on 12/26/16.
//

#ifndef COMPILER_MESSAGE_H
#define COMPILER_MESSAGE_H

#include <stdint.h>
#include "../ast/position.h"

enum {
    MESSAGE_ERROR,
    MESSAGE_WARNING,
    MESSAGE_NOTE
};

typedef struct {
    Position position;
    uint8_t type;

    // OWN:
    char* message;
} Message;

void message_init(Message* message, Position position, uint8_t type, char* string);
void message_deinit(Message* message);
void message_print(Message* message);

#endif //COMPILER_MESSAGE_H
