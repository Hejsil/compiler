#include <string.h>
#include <stdio.h>
#include "compiler.h"

int main() {
    char* text = "Hello World\n";
    char* source = "/home/jimmi/Documents/test";

    Compiler compiler;
    init_compiler(&compiler);
    make_scanner_from_file(&compiler, source, strlen(source));
    make_scanner_from_text(&compiler, text, strlen(text));

    printf("%s\n", compiler.scanners[0].text_to_scan);

    deinit_compiler(&compiler);
    return 0;
}