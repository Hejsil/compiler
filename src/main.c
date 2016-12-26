#include <string.h>
#include <stdio.h>
#include "compiler.h"
#include "basic/message.h"
#include "syntax/scanning.h"
#include "syntax/parsing.h"

int main(int argc, char** argv) {
    char* text =
            "main :: Nothing () {\n"
            "    int1: Int;\n"
            "    int1 = 7;\n"
            "    int2 := 3;\n"
            "\n"
            "    if int1 > int2 {\n"
            "        print(int1);\n"
            "    } else if int1 < int2 {\n"
            "        print(int2);\n"
            "    } else {\n"
            "        print(int1 + int2);\n"
            "    }\n"
            "}";

    Compiler compiler;
    compiler_init(&compiler);
    compiler_add_scanner_from_text(&compiler, text, strlen(text));

    parse(&compiler);

    compiler_deinit(&compiler);
    return 0;
}