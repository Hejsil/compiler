//
// Created by jimmi on 12/20/16.
//

#ifndef GOODLANG_PARSING_H
#define GOODLANG_PARSING_H

#include "../compiler.h"
#include "../ast/tree.h"

AST_Node* parse(Compiler* compiler);
AST_Node* parse_type(Compiler* compiler, Scanner* scanner);
AST_Node* parse_expression(Compiler* compiler, Scanner* scanner);

#endif //GOODLANG_PARSING_H
