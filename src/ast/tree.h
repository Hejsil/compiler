//
// Created by jimmi on 12/20/16.
//

#ifndef GOODLANG_TREE_H
#define GOODLANG_TREE_H

#include <stdint.h>
#include <stdbool.h>
#include "../basic/dynamic_array.h"

typedef struct Type_S {
    uint8_t type;
    int64_t size;

    union {
        struct {
            bool is_signed;
        } integer;

        struct {
            struct Type_S* element_type;
        } array;

        struct {
            struct Type_S* pointed_to_type;
        } pointer;

        struct {
            struct Type_S* return_type;

            // Elements: Type*
            Dynamic_Array argument_types;
        } function;

        struct {
            // OWN:
            char* name;

            // Elements: char*
            Dynamic_Array field_names;
            // Elements: Type*
            Dynamic_Array field_types;
        } struct_type;
    };
} Type;

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

enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_NOTHING,
    TYPE_ARRAY,
    TYPE_POINTER,
    TYPE_FUNCTION,
    TYPE_STRUCT
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

Type* make_type(uint8_t type);
void init_int_type(Type* node, int64_t size, bool is_signed);
void init_float_type(Type* node, int64_t size);
void init_char_type(Type* node);
void init_bool_type(Type* node, int64_t size);
void init_array_type(Type* node, AST_Node* element_type);
void init_pointer_type(Type* node, AST_Node* pointed_to_type);
void init_function_type(Type* node, AST_Node* return_type);
void deinit_node(AST_Node* node);

#endif //GOODLANG_TREE_H
