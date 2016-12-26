//
// Created by jimmi on 12/19/16.
//

#include "scanning.h"
#include "../basic/string.h"
#include "../ast/position.h"
#include <ctype.h>


Token scanner_peek_next_token(Scanner *scanner) {
    return scanner_peek_token(scanner, 0);
}

Token scanner_peek_token(Scanner *scanner, int64_t offset) {
    Token result;
    while (scanner->tokens.count <= offset) {
        result = scanner_get_next_token(scanner);
        dynamic_array_add_last(&scanner->tokens, &result);
    }

    dynamic_array_get(&scanner->tokens, offset, &result);
    return result;
}

Token scanner_get_next_token(Scanner *scanner) {
    Token result;

    if (scanner->tokens.count > 0) {
        // HACK: Here, an efficient queue structure would be better than a dynamic array
        dynamic_array_get(&scanner->tokens, 0, &result);
        dynamic_array_remove(&scanner->tokens, 0);

        return result;
    }

    scanner_skip_whitespace(scanner);
    result.position = scanner->position;

    char current = scanner_get_next_char(scanner);

    if (isalpha(current)) {

        while (isalnum(scanner_peek_next_char(scanner)))
            scanner_get_next_char(scanner);

        int64_t start_index = result.position.index;
        int64_t length = scanner->position.index - start_index;
        char* value = allocate_string_copy_without_strlen(&scanner->text_to_scan[start_index], length);

        // HACK: This should probably be replaced with a map lookup
        if (strcmp(value, "struct")) {
            result.type = TOKEN_KEYWORD_STRUCT;
        } else if (strcmp(value, "union")) {
            result.type = TOKEN_KEYWORD_UNION;
        } else if (strcmp(value, "while")) {
            result.type = TOKEN_KEYWORD_WHILE;
        } else if (strcmp(value, "foreach")) {
            result.type = TOKEN_KEYWORD_FOREACH;
        } else if (strcmp(value, "switch")) {
            result.type = TOKEN_KEYWORD_SWITCH;
        } else if (strcmp(value, "if")) {
            result.type = TOKEN_KEYWORD_IF;
        } else if (strcmp(value, "break")) {
            result.type = TOKEN_KEYWORD_BREAK;
        } else if (strcmp(value, "continue")) {
            result.type = TOKEN_KEYWORD_CONTINUE;

        } else if (strcmp(value, "Int")) {
            result.type = TOKEN_KEYWORD_INT;
        } else if (strcmp(value, "Int8")) {
            result.type = TOKEN_KEYWORD_INT8;
        } else if (strcmp(value, "Int16")) {
            result.type = TOKEN_KEYWORD_INT16;
        } else if (strcmp(value, "Int32")) {
            result.type = TOKEN_KEYWORD_INT32;
        } else if (strcmp(value, "Int64")) {
            result.type = TOKEN_KEYWORD_INT64;
        } else if (strcmp(value, "UInt")) {
            result.type = TOKEN_KEYWORD_UINT;
        } else if (strcmp(value, "UInt8")) {
            result.type = TOKEN_KEYWORD_UINT8;
        } else if (strcmp(value, "UInt16")) {
            result.type = TOKEN_KEYWORD_UINT16;
        } else if (strcmp(value, "UInt32")) {
            result.type = TOKEN_KEYWORD_UINT32;
        } else if (strcmp(value, "UInt64")) {
            result.type = TOKEN_KEYWORD_UINT64;
        } else if (strcmp(value, "Float")) {
            result.type = TOKEN_KEYWORD_FLOAT;
        } else if (strcmp(value, "Float32")) {
            result.type = TOKEN_KEYWORD_CONTINUE;
        } else if (strcmp(value, "Float64")) {
            result.type = TOKEN_KEYWORD_CONTINUE;
        } else if (strcmp(value, "Bool")) {
            result.type = TOKEN_KEYWORD_CONTINUE;
        } else if (strcmp(value, "Bool1")) {
            result.type = TOKEN_KEYWORD_CONTINUE;
        } else if (strcmp(value, "Bool8")) {
            result.type = TOKEN_KEYWORD_CONTINUE;
        } else {
            result.type = TOKEN_IDENTIFIER;
            result.value = value;
        }

        if (result.type != TOKEN_IDENTIFIER) {
            free(value);
        }
    } else if (isdigit(current)) {
        while (isdigit(scanner_peek_next_char(scanner)))
            scanner_get_next_char(scanner);

        if (scanner_peek_next_char(scanner) == '.' && isdigit(scanner_peek_char(scanner, 1))) {
            result.type = TOKEN_NUMBER_FLOAT;

            while (isdigit(scanner_peek_next_char(scanner)))
                scanner_get_next_char(scanner);
        } else {
            result.type = TOKEN_NUMBER_INT;
        }

        int64_t start_index = result.position.index;
        int64_t length = scanner->position.index - start_index;
        char* str = allocate_string_copy_without_strlen(&scanner->text_to_scan[start_index], length);

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
                while (scanner_get_next_char(scanner) != '"');

                int64_t start_index = result.position.index + 1;
                int64_t length = scanner->position.index - start_index;
                result.value = allocate_string_copy_without_strlen(&scanner->text_to_scan[start_index], length - 1);
                break;
            }
            case '#': {
                result.type = TOKEN_DIRECTIVE;

                while (isalnum(scanner_peek_next_char(scanner)))
                    scanner_get_next_char(scanner);

                int64_t start_index = result.position.index;
                int64_t length = scanner->position.index - start_index;
                result.value = allocate_string_copy_without_strlen(&scanner->text_to_scan[start_index], length);
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
                if (scanner_peek_next_char(scanner) == '=') {
                    scanner_get_next_char(scanner);
                    result.type = TOKEN_LESSER_OR_EQUAL_TO;
                    break;
                }
                result.type =TOKEN_LESS_THAN;
                break;
            case '>':
                if (scanner_peek_next_char(scanner) == '=') {
                    scanner_get_next_char(scanner);
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
            case ':':
                result.type = TOKEN_COLOL;
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

char scanner_get_next_char(Scanner *scanner) {
    char result = scanner_peek_next_char(scanner);

    if (result != '\0') {
        scanner->position.index++;

        if (result == '\n') {
            scanner->position.line++;
            scanner->position.column = 0;
        } else {
            scanner->position.column++;
        }
    }

    return result;
}

char scanner_peek_next_char(Scanner *scanner) {
    return scanner->text_to_scan[scanner->position.index];
}

void scanner_skip_whitespace(Scanner *scanner) {
    while (isspace(scanner_peek_next_char(scanner)))
        scanner_get_next_char(scanner);
}

void scanner_deinit(Scanner *scanner) {
    free(scanner->text_to_scan);
}

void token_deinit(Token *token) {
    switch (token->type) {
        case TOKEN_STRING:
        case TOKEN_IDENTIFIER:
        case TOKEN_DIRECTIVE:
            if (token->value != NULL)
                free(token->value);

            break;
    }
}

char scanner_peek_char(Scanner *scanner, int64_t offset) {
    return scanner->text_to_scan[scanner->position.index + offset];
}

void scanner_init(Scanner *scanner, char *source, char *text_to_scan) {
    init_position(&scanner->position, source);
    scanner->text_to_scan = text_to_scan;
    dynamic_array_init(&scanner->tokens, sizeof(Token), 2);
}
