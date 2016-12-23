//
// Created by jimmi on 12/20/16.
//

#include "parsing.h"
#include "scanning.h"
#include "../compiler.h"
#include "../basic/dynamic_array.h"

bool parse(Compiler *compiler) {
    Scanner current_scanner;

    if (compiler->scanners.count == 0) {
        return true;
    }

    dynamic_array_get_last(&compiler->scanners, &current_scanner);
    dynamic_array_remove_last(&compiler->scanners);

    for (;;) {
        Token peeked_token = peek_next_token(&current_scanner);

        switch (peeked_token.type) {
            case TOKEN_END_OF_FILE:
                if (compiler->scanners.count == 0) {
                    return true;
                }

                dynamic_array_get_last(&compiler->scanners, &current_scanner);
                dynamic_array_remove_last(&compiler->scanners);
                break;

            case TOKEN_IDENTIFIER:

                break;

            case TOKEN_DIRECTIVE:

                break;

            default:
                // TODO: Compile errors
                return false;
        }
    }

    return true;
}