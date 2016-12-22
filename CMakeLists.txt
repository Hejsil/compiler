cmake_minimum_required(VERSION 3.6)
project(compiler C)

set(SOURCE_FILES
        src/main.c
        src/syntax/scanning.c src/syntax/scanning.h
        src/compiler.c src/compiler.h
        src/syntax/parsing.c src/syntax/parsing.h
        src/ast/tree.c src/ast/tree.h
        src/ast/position.h
        src/basic/string.c src/basic/string.h
        src/basic/file.c src/basic/file.h)
add_executable(compiler ${SOURCE_FILES})