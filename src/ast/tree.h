//
// Created by jimmi on 12/20/16.
//

#ifndef GOODLANG_TREE_H
#define GOODLANG_TREE_H

#include <stdint.h>
#include "../basic/dynamic_array.h"

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
    AST_UNARY_NEGATION,

    AST_LITERAL_INT,
    AST_LITERAL_FLOAT,
    AST_LITERAL_STRING,

    AST_CALL
};

// TODO: Figure out a way to have an cache friendly tree to traverse
typedef struct AST_Node_S {
    uint8_t type;

    union {
        struct {
            // OWN
            struct AST_Node_S* left;
            // OWN
            struct AST_Node_S* right;
        } binary;

        struct {
            // OWN
            struct AST_Node_S* child;
        } unary;

        struct {
            // OWN
            struct AST_Node_S* function;

            // Elements: AST_Node*
            Dynamic_Array arguments;
        } call;

        struct {
            int64_t value;
        } int_literal;

        struct {
            double value;
        } float_literal;

        struct {
            char* value;
        } string_literal;
    };
} AST_Node;

#endif //GOODLANG_TREE_H
