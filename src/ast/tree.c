//
// Created by jimmi on 12/20/16.
//

#include "tree.h"

AST_Node* make_node(uint8_t type) {
    AST_Node* result = malloc(sizeof(AST_Node));
    result->type = type;

    return result;
}

void init_program(AST_Node *node) {
    dynamic_array_init(&node->code_block.statements, sizeof(AST_Node), 2);
}

void init_code_block(AST_Node *node) {
    dynamic_array_init(&node->code_block.statements, sizeof(AST_Node), 2);
}

void init_binary_operator(AST_Node *node, AST_Node *left, AST_Node *right) {
    assert(node->type == AST_BINARY_ADD ||
           node->type == AST_BINARY_AND ||
           node->type == AST_BINARY_DIV ||
           node->type == AST_BINARY_GREATER_OR_EQUAL_THAN ||
           node->type == AST_BINARY_GREATER_THAN ||
           node->type == AST_BINARY_LESSER_OR_EQUAL_THAN ||
           node->type == AST_BINARY_LESSER_THAN ||
           node->type == AST_BINARY_MUL ||
           node->type == AST_BINARY_OR ||
           node->type == AST_BINARY_SUB);

    node->binary.left = left;
    node->binary.right = right;
}

void init_unary_operator(AST_Node* node, AST_Node *child) {
    assert(node->type == AST_UNARY_MINUS ||
           node->type == AST_UNARY_NEGATION);

    node->unary.child = child;
}

void init_call(AST_Node* node, AST_Node *function) {
    assert(node->type == AST_CALL);
    node->call.function = function;

    dynamic_array_init(&node->call.arguments, sizeof(AST_Node), 2);
}

void init_int_literal(AST_Node* node, int64_t value) {
    assert(node->type == AST_LITERAL_INT);
    node->int_literal.value = value;
}

void init_float_literal(AST_Node* node, double value) {
    assert(node->type == AST_LITERAL_FLOAT);
    node->float_literal.value = value;
}

void init_string_literal(AST_Node* node, char *value) {
    assert(node->type == AST_LITERAL_STRING);
    node->string_literal.value = value;
}

void deinit_node(AST_Node *node) {
    switch (node->type) {
        case AST_PROGRAM:
        case AST_CODE_BLOCK:
            for (int64_t i = 0; i < node->code_block.statements.count; ++i) {
                deinit_node(dynamic_array_get_ptr(&node->code_block.statements, i));
            }

            dynamic_array_deinit(&node->code_block.statements);
            break;

        case AST_FUNCTION_DECLARATION:
            // TODO
            break;

        case AST_BINARY_ADD:
        case AST_BINARY_SUB:
        case AST_BINARY_MUL:
        case AST_BINARY_DIV:
        case AST_BINARY_AND:
        case AST_BINARY_OR:
        case AST_BINARY_GREATER_THAN:
        case AST_BINARY_LESSER_THAN:
        case AST_BINARY_GREATER_OR_EQUAL_THAN:
        case AST_BINARY_LESSER_OR_EQUAL_THAN:
            deinit_node(node->binary.left);
            deinit_node(node->binary.right);
            free(node->binary.left);
            free(node->binary.right);
            break;

        case AST_UNARY_MINUS:
        case AST_UNARY_NEGATION:
            deinit_node(node->unary.child);
            free(node->unary.child);
            break;

        case AST_LITERAL_STRING:
            free(node->string_literal.value);
            break;

        case AST_CALL:
            deinit_node(node->call.function);
            free(node->call.function);

            for (int64_t i = 0; i < node->call.arguments.count; ++i) {
                deinit_node(dynamic_array_get_ptr(&node->call.arguments, i));
            }

            dynamic_array_deinit(&node->call.arguments);
            break;
    }
}

void init_int_type(AST_Node *node, int64_t size, bool is_signed) {
    assert(node->type == AST_TYPE_INT);

    node->int_type.size = size;
    node->int_type.is_signed = is_signed;
}

void init_float_type(AST_Node *node, int64_t size) {
    // TODO
}

void init_bool_type(AST_Node *node, int64_t size) {
    // TODO
}

void init_array_type(AST_Node *node, AST_Node *element_type) {
    // TODO
}

void init_pointer_type(AST_Node *node, AST_Node *pointed_to_type) {
    // TODO
}

void init_function_type(AST_Node *node, AST_Node *return_type) {
    // TODO
}
