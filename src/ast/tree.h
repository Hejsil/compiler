//
// Created by jimmi on 12/20/16.
//

#ifndef GOODLANG_TREE_H
#define GOODLANG_TREE_H

#include <stdint.h>
#include "../basic/dynamic_array.h"

enum {
    AST_PROGRAM,
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

typedef struct AST_Node_S {
    uint8_t type;

    union {
        struct {
            Dynamic_Array statements;
        } code_block;

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

            // Elements: AST_Node
            Dynamic_Array arguments;
        } call;

        struct {
            int64_t value;
        } int_literal;

        struct {
            double value;
        } float_literal;

        struct {
            // OWN
            char* value;
        } string_literal;
    };
} AST_Node;

AST_Node* make_node(uint8_t type);
void init_program(AST_Node* node);
void init_code_block(AST_Node* node);
void init_binary_operator(AST_Node *node, AST_Node* left, AST_Node* right);
void init_unary_operator(AST_Node *node, AST_Node* child);
void init_call(AST_Node *node, AST_Node* function);
void init_int_literal(AST_Node *node, int64_t value);
void init_float_literal(AST_Node *node, double value);
void init_string_literal(AST_Node *node, char* value);
void deinit_node(AST_Node* node);

#endif //GOODLANG_TREE_H
