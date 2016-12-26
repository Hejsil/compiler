//
// Created by jimmi on 12/20/16.
//

#include "parsing.h"
#include "scanning.h"
#include "../basic/message.h"

AST_Node* parse(Compiler *compiler) {
    Scanner current_scanner;

    if (compiler->scanners.count == 0) {
        return NULL;
    }

    dynamic_array_get_last(&compiler->scanners, &current_scanner);
    dynamic_array_remove_last(&compiler->scanners);

    AST_Node* result = make_node(AST_PROGRAM);
    init_program(result);

    for (;;) {
        Token peeked_token = scanner_peek_next_token(&current_scanner);

        switch (peeked_token.type) {
            case TOKEN_END_OF_FILE:
                scanner_deinit(&current_scanner);
                if (compiler->scanners.count == 0) {
                    return result;
                }

                dynamic_array_get_last(&compiler->scanners, &current_scanner);
                dynamic_array_remove_last(&compiler->scanners);
                break;

            case TOKEN_IDENTIFIER:

                break;

            case TOKEN_DIRECTIVE:

                break;

            default:
                compiler_add_message(compiler, peeked_token.position, MESSAGE_ERROR,
                    "Parser found an unexpected character in global scope, which does "
                    "not translate into either a declaration or directive.");

                deinit_node(result);
                free(result);
                return NULL;
        }
    }
}

AST_Node* parse_global_declaration(Compiler* compiler, Scanner* scanner) {
    AST_Node* type = NULL;
    Token identifier = scanner_get_next_token(scanner);
    assert(identifier.type == TOKEN_IDENTIFIER);

    Token next = scanner_get_next_token(scanner);
    if (next.type != TOKEN_COLOL) {
        compiler_add_message(compiler, next.position, MESSAGE_ERROR,
            "Parse found unexpected character in global declaration. Expected ':'.");

        token_deinit(&next);
        token_deinit(&identifier);
        return NULL;
    }

    if (scanner_peek_next_token(scanner).type != TOKEN_COLOL) {
        type = parse_type(compiler, scanner);

        // If NULL, an error occurred and we just return.
        if (type == NULL)
            return NULL;
    }

    next = scanner_get_next_token(scanner);
    if (next.type != TOKEN_COLOL) {
        compiler_add_message(compiler, next.position, MESSAGE_ERROR,
            "Parse found unexpected character in global declaration. Expected ':'.");

        if (type != NULL) {
            deinit_node(type);
            free(type);
        }

        token_deinit(&next);
        token_deinit(&identifier);
        return NULL;
    }
}

AST_Node* parse_type(Compiler* compiler, Scanner* scanner) {
    AST_Node* result;

    Token current = scanner_get_next_token(scanner);

    switch (current.type) {
        case TOKEN_IDENTIFIER:
    }
}

AST_Node* parse_basic_type(Compiler* compiler, Scanner* scanner) {

}

AST_Node* parse_expression(Compiler* compiler, Scanner* scanner) {
    return NULL;
}