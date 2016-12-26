//
// Created by jimmi on 12/26/16.
//

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "message.h"
#include "../ast/position.h"

#define RED "\x1b[31;1m"
#define YELLOW  "\x1b[33m"
#define GREEN "\x1b[32;1m"
#define CYAN "\x1b[36;1m"
#define WHITE "\x1b[37;1m"
#define RESET "\x1b[0m"

void message_init(Message* message, Position position, uint8_t type, char* string) {
    message->type = type;
    message->message = string;
    message->position = position;
}

void message_deinit(Message* message) {
    if (message->message != NULL)
        free(message->message);
}

void message_print(Message* message) {
    if (message->position.source == NULL) {
        fprintf(stdout, "NULL:");
    } else {
        fprintf(stdout, "%s:", message->position.source);
    }

    fprintf(stdout, "%" PRId64 ":%" PRId64 ": ",
            message->position.line + 1,
            message->position.column + 1);

    switch (message->type) {
        case MESSAGE_ERROR:
            fprintf(stdout, RED "Error: " RESET);
            break;
        case MESSAGE_WARNING:
            fprintf(stdout, YELLOW "Warning: " RESET);
            break;
        case MESSAGE_NOTE:
            fprintf(stdout, RED "Note: " RESET);
            break;
    }

    if (message->message == NULL) {
        fprintf(stdout, "NULL\n");
    } else {
        fprintf(stdout, "%s", message->message);
    }

    // TODO: print some code and ^~~~~
}
