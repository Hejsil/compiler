//
// Created by jimmi on 12/19/16.
//

#include "scanning.h"
#include "../basic/string.h"
#include <ctype.h>
#include <stdlib.h>

void deinit_scanner(Scanner *scanner) {
    free(scanner->text_to_scan);
}

Token get_next_token(Scanner *scanner) {
    Token result;

    skip_whitespace(scanner);
    result.position = scanner->position;

    char current = get_next_char(scanner);

    if (isalpha(current)) {
        result.type = TOKEN_IDENTIFIER;

        while (isalnum(peek_next_char(scanner)))
            get_next_char(scanner);

        int64_t start_index = result.position.index;
        int64_t lenght = scanner->position.index - start_index;
        result.value = allocate_string_copy(&scanner->text_to_scan[start_index], lenght);
        
    } else if (isdigit(current)) {
        while (isdigit(peek_next_char(scanner)))
            get_next_char(scanner);

        if (peek_next_char(scanner) == '.' && isdigit(peek_char(scanner, 1))) {
            result.type = TOKEN_NUMBER_FLOAT;

            while (isdigit(peek_next_char(scanner)))
                get_next_char(scanner);
        } else {
            result.type = TOKEN_NUMBER_INT;
        }

        int64_t start_index = result.position.index;
        int64_t length = scanner->position.index - start_index;
        char* str = allocate_string_copy(&scanner->text_to_scan[start_index], length);

        if (result.type == TOKEN_NUMBER_FLOAT) {
            result.number_float = atof(str);
        } else {
            result.number_int = atoi(str);
        }

        free(str);
    } else {
        // TODO: More cases
        switch (current) {
            case '"': {
                result.type = TOKEN_STRING;

                // TODO: Handle escape characters
                while (get_next_char(scanner) != '"');

                int64_t start_index = result.position.index + 1;
                int64_t length = scanner->position.index - start_index;
                result.value = allocate_string_copy(&scanner->text_to_scan[start_index], length - 1);
                break;
            }
            case '#': {
                result.type = TOKEN_DIRECTIVE;

                while (isalnum(peek_next_char(scanner)))
                    get_next_char(scanner);

                int64_t start_index = result.position.index;
                int64_t length = scanner->position.index - start_index;
                result.value = allocate_string_copy(&scanner->text_to_scan[start_index], length);
                break;
            }
            case '(':
                result.type = TOKEN_PAR_LEFT;
                break;
            case ')':
                result.type = TOKEN_PAR_RIGHT;
                break;
            case '{':
                result.type = TOKEN_CURLY_LEFT;
                break;
            case '}':
                result.type = TOKEN_CURLY_RIGHT;
                break;
            case '[':
                result.type = TOKEN_SQUARE_LEFT;
                break;
            case ']':
                result.type = TOKEN_SQUARE_RIGHT;
                break;
            case '<':
                if (peek_next_char(scanner) == '=') {
                    get_next_char(scanner);
                    result.type = TOKEN_LESSER_OR_EQUAL_TO;
                    break;
                }
                result.type =TOKEN_LESS_THAN;
                break;
            case '>':
                if (peek_next_char(scanner) == '=') {
                    get_next_char(scanner);
                    result.type = TOKEN_GREATER_OR_EQUAL_TO;
                    break;
                }
                result.type = TOKEN_GREATER_THAN;
                break;
            case '+':
                result.type = TOKEN_ADD;
                break;
            case '-':
                result.type = TOKEN_SUB;
                break;
            case '*':
                result.type = TOKEN_MUL;
                break;
            case '/':
                result.type = TOKEN_DIV;
                break;
            case '\0':
                result.type = TOKEN_END_OF_FILE;
                break;
            default: 
                result.type = TOKEN_UNKNOWN;
                break;
        }
    }

    return result;
}

char get_next_char(Scanner *scanner) {
    char result = peek_next_char(scanner);

    if (result != '\0')
        scanner->position.index++;

    return result;
}

char peek_next_char(Scanner *scanner) {
    return scanner->text_to_scan[scanner->position.index];
}

void skip_whitespace(Scanner *scanner) {
    while (isspace(peek_next_char(scanner)))
        get_next_char(scanner);
}

void deinit_token(Token *token) {
    switch (token->type) {
        case TOKEN_STRING:
        case TOKEN_IDENTIFIER:
            free(token->value);
            break;
    }
}

char peek_char(Scanner *scanner, int64_t offset) {
    return scanner->text_to_scan[scanner->position.index + offset];
}
