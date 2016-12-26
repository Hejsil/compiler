//
// Created by jimmi on 12/20/16.
//

#include "parsing.h"
#include "scanning.h"

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
        Token peeked_token = peek_next_token(&current_scanner);

        switch (peeked_token.type) {
            case TOKEN_END_OF_FILE:
                deinit_scanner(&current_scanner);
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
                // TODO: Compile error
                deinit_node(result);
                free(result);
                return NULL;
        }
    }
}

AST_Node* parse_global_declaration(Compiler *compiler, Scanner* current_scanner) {
    Token identifier = get_next_token(current_scanner);
    assert(identifier.type == TOKEN_IDENTIFIER);

    Token next = get_next_token(current_scanner);
    if (next.type != TOKEN_COLOL) {
        // TODO: Compiler error

        deinit_token(&next);
        deinit_token(&identifier);
        return NULL;
    }

    AST_Node* type = parse_type(compiler, current_scanner);
    // TODO: Types can also be explicit.

    next = get_next_token(current_scanner);

    if (next.type != TOKEN_COLOL) {
        // TODO: Compiler error

        deinit_token(&next);
        deinit_token(&identifier);
        return NULL;
    }
}

AST_Node* parse_type(Compiler *compiler, Scanner* current_scanner) {

}

AST_Node* parse_expression(Compiler *compiler, Scanner* current_scanner) {

}