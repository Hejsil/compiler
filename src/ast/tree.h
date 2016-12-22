//
// Created by jimmi on 12/20/16.
//

#ifndef GOODLANG_TREE_H
#define GOODLANG_TREE_H

#include <stdint.h>

enum {
    AST_CODE_BLOCK,

    AST_FUNCTION_DECLARATION,

    AST_BINARY_ADD,
    AST_BINARY_SUB,
    AST_BINARY_MUL,
    AST_BINARY_DIV,
    AST_BINARY_AND,
    AST_BINARY_OR,
    AST_BINARY_GREATER_THAN,
    AST_BINARY_LESSER_THAN,
    AST_BINARY_GREATER_OR_EQUAL_THAN,
    AST_BINARY_LESSER_OR_EQUAL_THAN,

    AST_UNARY_MINUS,
    AST_UNARY_NEGATION
};

typedef struct AST_Node_S {
    uint8_t type;

    union {
        struct {
            struct AST_Node_S* left;
            struct AST_Node_S* right;
        } binary;

        struct {
            struct AST_Node_S* child;
        } unary;
    };
} AST_Node;

#endif //GOODLANG_TREE_H
