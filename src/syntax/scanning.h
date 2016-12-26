//
// Created by jimmi on 12/19/16.
//

#ifndef GOODLANG_SCANNING_H
#define GOODLANG_SCANNING_H

#include <stdint.h>
#include <stdbool.h>
#include "../ast/position.h"
#include "../basic/dynamic_array.h"

enum {
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_DIRECTIVE,

    TOKEN_NUMBER_FLOAT,
    TOKEN_NUMBER_INT,

    TOKEN_IF,
    TOKEN_SWITCH,
    TOKEN_WHILE,
    TOKEN_FOREACH,
    TOKEN_BREAK,
    TOKEN_CONTINUE,

    TOKEN_LESS_THAN,
    TOKEN_GREATER_THAN,
    TOKEN_GREATER_OR_EQUAL_TO,
    TOKEN_LESSER_OR_EQUAL_TO,
    TOKEN_OR,
    TOKEN_AND,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,

    TOKEN_PAR_LEFT,
    TOKEN_PAR_RIGHT,
    TOKEN_SQUARE_LEFT,
    TOKEN_SQUARE_RIGHT,
    TOKEN_CURLY_LEFT,
    TOKEN_CURLY_RIGHT,

    TOKEN_COLOL,

    TOKEN_END_OF_FILE,
    TOKEN_UNKNOWN
};

typedef struct {
    // OWN:
    char* text_to_scan;

    // Elements: Token
    Dynamic_Array tokens;
    Position position;
} Scanner;

typedef struct {
    uint8_t type;
    Position position;

    union {
        int64_t number_int;
        double number_float;

        // OWN: Only needs to deallocate when of type:
        // TOKEN_IDENTIFIER,
        // TOKEN_STRING,
        // TOKEN_DIRECTIVE,
        char* value;
    };
} Token;

char peek_char(Scanner* scanner, int64_t offset);
char peek_next_char(Scanner* scanner);
char get_next_char(Scanner* scanner);
void skip_whitespace(Scanner* scanner);
Token peek_token(Scanner* scanner, int64_t offset);
Token peek_next_token(Scanner* scanner);
Token get_next_token(Scanner* scanner);
void init_scanner(Scanner* scanner, char* source, char* text_to_scan);
void deinit_scanner(Scanner* scanner);
void deinit_token(Token* token);

#endif //GOODLANG_SCANNING_H
