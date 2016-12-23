#include <string.h>
#include <stdio.h>
#include "compiler.h"
#include "basic/dynamic_array.h"
#include "syntax/scanning.h"

int main() {
    char* text = "Hello World\n";
    char* source = "/home/jimmi/Documents/test";

    Compiler compiler;
    init_compiler(&compiler);
    make_scanner_from_file(&compiler, source, strlen(source));
    make_scanner_from_text(&compiler, text, strlen(text));

    Scanner file_scanner;
    dynamic_array_get(&compiler.scanners, 0, &file_scanner);
    printf("%s\n", file_scanner.text_to_scan);

    deinit_compiler(&compiler);
    return 0;
}