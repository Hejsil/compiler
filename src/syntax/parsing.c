//
// Created by jimmi on 12/20/16.
//

#include "parsing.h"

bool parse(Compiler *compiler) {
    for (;;) {
        Scanner current_scanner;
        if (!pop_scanner(compiler, &current_scanner)) {
            return true;
        }


    }

    return true;
}