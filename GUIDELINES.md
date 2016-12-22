# Guidelines
## Syntax
### Naming
* Files: `lower_case_delimiter_separated`
* Variables: `lower_case_delimiter_separated`
* Functions: `lower_case_delimiter_separated`
* Defines: `ALL_CAPS_DELIMITER_SEPARATED`
* Struct
    * Name: `Camel_Case_Delimiter_Separated`
    * Fields: `lower_case_delimiter_separated`
* Enum
    * Name: `Camel_Case_Delimiter_Separated`
    * Members: `ALL_CAPS_DELIMITER_SEPARATED`
* Names should be productively informative
    * Avoid abriviations
        * When variable names are short
            * `database > db`
        * When variable names are very long, it might be nessesary 
            * `ast > abstract_syntax_tree`
    * Avoid writing types in the names
        * Only add the types when names become very vague without them: 
            * `get_next_char > get_next`
            * `scanner_get_next > get_next`

### Whitespace
* For each layer of scope, the code should be indented by 4 spaces
    ```
    int scope0;

    {
        int scope1;

        {
            int scope2;
        }
    }
    ```

* Prefer the curly brackets on the same line, when using conditional statements
    ```
    if (1) {
        
    }
    ```
* Split long expressions into mutible lines.
    * Assignments should be split into mutilble assignments
        ```
        int part1 = token_container_count * token_container_count;
        int part2 = token_container_count / 33;
        int final = part1 * part2 + 5;
        ```
    * Expressions in conditional statements and parameters should be newlined
        ```
        if (token_container_count < char_container_count ||
            token_container_count == 35) {

        }
        ```

### Comments
* Avoid comments on obviouse behavior
    * ~~`a + b // adding two numbers`~~
* Use "Tags" to indicate that the comment has special meaning
    * `// TODO: This is something that should be done, but I'm not gonna do it now`
    * `// HACK: I'm aware, that this is not at all the best solution, but for now this works`
    * `// OWN: Indication of ownership of a piece of memory, and should not be deallocated from other pointers`
* TODO: Guideline for documentation (maybe use DoxyGen. We are however not a library, so it might not be the best solution, idk.)

### Pointer
* ALWAYS place the pointer symbol, near the type and not the name
    * `char* c > char *c`

## Semantic
### Types
* Always use the integer types defined in `stdint.h`
* Always use the bool defined in `stdbool.h`, when this behavior is needed.

### Return values
* Prefer using the return value for error handling
    * `bool try_parse(int* result) > int try_parse(bool* success)`

### Heap Allocations
* Prefer `malloc` > `calloc` when zero initialization is not nessesary
* Use the `OWN` comment tag to indicate that a pointer owns the memory it points to.
* Prefer stack allocations over heap allocations

### Cache
* NEVER travers a linked list
    * If traversal is needed, don't use a linked list
