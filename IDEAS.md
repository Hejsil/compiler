# Language Ideas
## The Language
This language is inspired by C for low level development. It will allow you to do all the unsafe stuff you love, but with a overhalled syntax designed to be more readable and consistent. The language will also have more high level constructs, that are hopefully alot simpler than the same alternatives you can find in C++.

## C vs Language
### C
```C
typedef struct vector_s {
    int x, y;
} vector_t;

int main(int argc, char **argv) {
    int number = 5;
    int array[3] = { 3, 2, 1 };
    vector_t vec = { 3, 2 };
    vector_t *vec_ptr = &vec;

    for (int i = 0; i < sizeof(array); i++) {
        array[i] *= 2;
    }

    vec.x *= 2;
    vec_ptr->y *= 2;

    return 0;
}
```

### Language
Idea 1:
```
Vector :: struct {
    x, y : Int;
}

main :: Int (args: String[]) {
    number := 5;
    array := [3 .. 1, 1];
    vec := Vector{ x = 3, y = 2 };
    vec_ptr := @vec;

    for i in [0 .. array.length[ {
        array[i] *= 2;
    }

    vec.x *= 2;
    vec_ptr.y *= 2;

    return 0;
}
```

## Basic syntax
### Declaration and Assignment
Inspired by Jai

The full declaration syntax are as followed:
```
<declaration> -> <name> : <type> ;
              | <name> : <maybe type> = <expression> ;
              | <name> : <maybe type> : <const expression> ;
```

This is an othogonal syntax that allows a declaration to be expressed in several different ways. For simple variable declaration, the first syntax rule will apply.
```
x : Int;
y : Double;
```

Here, `x` is a variable of type `Int` and `y` a variable of type `Double`.

These variables can then be assigned values to, at a later stage in the code.
```
x = 5;
y = 5.5;
```

There are however many times, where a varable should be initialized at the same time as it was declared. For this, the second syntax rule can be used:
```
x : Int = 5;
y : Double = 5.5;
```

The reason the `<type>` changed to `<maybe type>` is, that when a declaration is initialized, the type can be infered. The type can therefor be omitted if the programmer does not want to document the type.
```
x := 5;
y := 5.5;
```

The third syntax rule are for constants.
```
x : Int : 5;
y :: 5.5;
```

Constants are required to be initialized on declaration. Constants also allows `<const expression>` instead of `<expression>`. This is because functions, types and other language constructs are constant declarations.
```
Vector3 :: struct {
    x, y, z : Int;
}

mul :: Int(x: Int, y: Int) {
    return x * y;
}
```

Here, we use the infered type syntax for constant, but these declarations also have a type:
```
Vector3 : Type : struct {
    x, y, z: Int;
}

mul : Int (Int, Int) : Int(x: Int, y: Int) {
    return x * y;
}
```

### Expressions
Binary operators:
```
a + b
a - b
a * b
a / b

a < b
a > b
a <= b
a >= b

// Small idea:
// These might give more readabillity
a !< b // a >= b
a !> b // a <= b
a !<= b // a > b
a !>= b // a < b

// And/Or operator ideas
// Idea 1:
a and b
a or b

// Idea 2:
a && b
a || b
```

Unary operators:
```
// Reference dereference ideas:
// Idea 1:
->a // ref
<-a // deref

// Idea 2:
@a // ref
*a // deref

// Idea 3:
ref a
deref a
```

## Build in Types
### Basic Types
| Types   | Size                                                    |
|---------|---------------------------------------------------------|
| Int     | 64-bits                                                 |
| Int8    | 8-bits                                                  |
| Int16   | 16-bits                                                 |
| Int32   | 32-bits                                                 |
| Int64   | 64-bits                                                 |
| UInt    | 64-bits                                                 |
| UInt8   | 8-bits                                                  |
| UInt16  | 16-bits                                                 |
| UInt32  | 32-bits                                                 |
| UInt64  | 64-bits                                                 |
| Float   | 64-bits                                                 |
| Float32 | 32-bits                                                 |
| Float64 | 64-bits                                                 |
| Bool    | 8-bits                                                  |
| Bool1   | 1-bit when stored in an array. 8-bits alone.            |
| Bool8   | 8-bits                                                  |
| Char    | Variadic when stored in an array (UTF8). 32-bits alone. |
| Nothing | 0-bits                                                  |

### Other Types

| Types             | Description                                             |
|-------------------|---------------------------------------------------------|
| T[]/[]T           | An array with elements of type T.                       |
| T@/@T             | A pointer to a type T.                                  |
| own@ T / T @own   | An owned pointer to type T.                             |
| T imut / imut T   | An imutable of type T. This should be a super strict type. | 
| T err / err T     | Error or T?                                             |
| String            | Alias for Char[]                                        |
| Type              | The runtime reprensentation of a type.                  |

## Language Constructs 
### Control Flow
#### If
TODO: Describe 
```
<if_statement> -> if <expression> <code_block> ( else if <expression> <code_block> )* ( else <code_block> )?
```

```
if a > b {

} else if a < b {

} else {

}
```

#### Switch 
TODO: Describe
```
<switch_statement> -> switch <expression> { ( ( case <literal> | default ) <code_block> )* }
```

#### Foreach loop
General syntax:
```
foreach item, index in collection
```

In C, loops will be used to count up some number, and doing something until this numter reaches a max. We can express this too, with this loop.
```
// C for loop
for (int i = 0; i < 5; i++)

// Our language alternatives
foreach i in [0 .. 4]

// or if using enumerable or similar
array := Int[]{ 1, 2, 3, 4, 5 };
foreach i in array
```

### Array Literals

The following things are only possible at compile time.

```
// Array literal syntax:
array1 := Int[]{ 1, 2, 3, 4, 5 };
array2 := Int[]{ 2, 4, 6, 8 };
array3 := Double[]{ 1.0, 1.5, 2.0 };
array4 := Int[]{ 5, 2, 8, 1 };

// Array sequense syntax:
array1 := [1 .. 5];
array2 := [2 .. 8, 2];
array3 := [1.0 .. 2.0, 0.5];
// array4 have no array sequense alternative.

// Array sequenses can be inclusive and exclusice
// Inspired by math syntax:
// http://www.mathwords.com/e/exclusive.htm
// http://www.mathwords.com/i/inclusive.htm
array1 := [1 .. 6[;
array1 := ]0 .. 5];
array1 := ]0 .. 6[;

// What will happen in this case?
// In my opinion, we should either simulate how a for loop in C would assign these elements, or give an error.
array5 := [1 .. 4, 2];
// array5 := Int[]{ 1, 3 };
```

#### Declaring array before setting size
An array can be declared, and then initialized with size later:
```
array1 : Int[];
array1 = [4];
```

Or it can have its type and size initialized by at once.

```
array1 := Int[4]
```

By just initializing the array, all elements are set according to standard.
But since this may contradict with the above array literals a few changes could be made:
```
// Array literals:
Remain as is, and dont have to specify the size as it can be determined by the size of the input

// Array sequense syntax:
array1 := [1 .. 5];
array2 := [2 .. 8, 2];
etc.

```

### Generics
TODO: Think about syntax
```
Bad_List :: struct<T_Element: Type> {
    head: @Node;
    tail: @Node;

    Node :: struct {
        value: T_Element;
        next: @Node;
        prev: @Node;
    }
}

get_sum :: T_Sum (list: @Bad_List<T_Sum>)<T_Sum: Type> {
    get_sum_node :: T_Sum (node: @Bad_List<T_Sum>.Node) {
        if node.next == Null
            return node.value;

        return node.value + get_sum_node(node.next);
    }

    if list.head == Null
        return T_Sum{};
    
    return get_sum_node(list.head);
}
```

### Memory Interfaces
Sometimes a programmer might want to implement a function that can operate on any type that contains certain fields. In this language, an interface would be used.
```
IVector2 :: interface {
    x, y : Int;
}

Vector3 :: struct {
    x, y, z : Int;
}

[ensure_interface(IVector2)]
Animal :: struct {
    is_dead: Bool;

    [interface_entry(IVector2)]
    position_x: Int;
    position_y: Int;
}

vector2_add_fields :: Int (vector: IVector2) {
    return vector.x + vector.y;
}

main :: Nothing () {
    vector3 := Vector3{ x = 1, y = 2, z = 3 };
    animal := Animal{ is_dead = false, position_x = 24, position_y = 33 };
    
    result1 := vector2_add_fields(vector3);
    result2 := vector2_add_fields(animal);
}
```

The way the interfaces work is simple. They are a way of telling the compiler that at a certain offset in memory, on type is structually identical to the interface. For the `Vector3` struct, the compiler is able to deduce that `Vector3` upholds the `IVector2` interface. For `Animal`, the attribute `interface_entry` was used to specify the entry at which it upholds `IVector2`. The `ensure_interface` attribute can also be used in the code to force the compiler to give an error if a type doesn't uphold a interface.


### Function Interfaces
TODO: Think this more through

```
IIterable :: functionality<T_This, T_Element, T_Iterator> {
    make_iterator: T_Iterator (@T_This);
    iterator_next: @T_Element (@T_This, @T_Iterator);
}

[ensure_interface(IIterable<Array<T_Element>, T_Element, Int)]
Array :: struct<T_Element> {
    data: T_Element[];
}

[interface_function(IIterable<Array<T_Element>, T_Element, Int>)]
make_iterator :: Int (this: @Array<T_Element>)<T_Element> {
    return -1;
}

[interface_function(IIterable<Array<T_Element>, T_Element, Int>)]
iterator_next :: @T_Element (this: @Array<T_Element>, iterator: @Int)<T_Element> {
    (*iterator) += 1;

    if this.data.length <= iterator
        return Null;

    return @this.data[iterator];
}


main :: Nothing () {
    array := Array<Float>{ data = new Float[]{ 5.1, 2.5, 2.77 } };
    iterator_sum := 0;
    float_sum := 0.0;

    foreach item, iterator in array {
        iterator_sum += iterator;
        float_sum += item;
    }

    delete array.data;
}
```

### Tagged Unions
In C, often structures are made which contains unions. Often these structs will have some enum assosiated with each union memeber to ensure "safe" access. This is however not safe, as the compiler cannot catch errors in the code that uses this structure. This language solves this problem by having tagged unions, with compile time checks, to ensure safe access.

```
Tree<T_Value> :: tagged_union {
    Node {
        value: T_Value;
        left, right: @Tree<T_Value>;
    },
    Leaf {
        value: T_Value;
    }
}

main :: Nothing () {
    tree := Tree<Int>.Node{ 
        value = 5, 
        left = new Tree<Int>.Leaf{ value = 6 }, 
        right = new Tree<Int>.Node {
            value = 2,
            left = new Tree<Int>.Leaf{ value = 9 },
            right = new Tree<Int>.Leaf{ value = 7 }
        } 
    };

    sum := get_sum<Int>(@tree);
}

get_sum<T_Sum> :: T_Sum (tree: @Tree<T_Sum>) {
    if tree is Tree<T_Sum>.Node {
        // Trees type has been check, so tree values for Node can be accessed.
        return tree.value + get_sum(tree.left) + get_sum(tree.right);
    } else {
        // Here, all but one tag has been exhausted, so the compiler should be able to 
        // deduce what fields are safe to access.
        return tree.value;
    }
}

```

### Error handling
TODO: Look at zig http://ziglang.org/#parse
```
IntParseError :: error;

parse_int :: Int (string: String) {
    if string.length == Null
        return IntParseError{};

    return 10;
}

main :: Nothing () {
    result: Int;

    // Idea 1. Just use if/switch statment
    // Problems. Very not verbose. What if we need to handle 15 functions that
    // can return some error, and all we want is to pass it to the next function.
    switch (parse_int("")) {
        case IntParseError: 
            // Handle Error
        default:
            result = value;
    }

    // Idea 2. Have a handle statment?
    // Problems. How exactly would it work?
    result = handle(parse_int("")) IntParseError => \*Handle Error*\;

    // Idea 3. Zig does something like this
    result = parse_int("") |IntParseError| => 
}
```

### Built In Functions
The language should support useful built in functions that can do things which cannot be expressed in the base language without them.

#### Type of
```
#type_of: Type (expression: #AST_Expression)
```

#### Size of
```
#size_of: Int (type: Type)
```

#### Init
```
#init<T_This>: void (this: @T_This)
```

#### DeInit
```
#deinit<T_This>: void (this: @T_This)
```

### Attribute
It should be possible for the user to control what the compiler should and shouldn't allow. This will most likely be in a separate file.
For complex programs over multiple folders, multiple files could be used, where the rules apply to that folder and all sub-folders of source files.

#### array_sequese_remainder
```
[array_sequese_remainder(WARNING_CEIL)]
main :: Nothing () {
    array := [1 .. 4, 2]; // Int[]{ 1, 3, 5 }
}

[array_sequese_remainder(WARNING_FLOOR)]
main :: Nothing () {
    array := [1 .. 4, 2]; // Int[]{ 1, 3 }
}

[array_sequese_remainder(ERROR)]
main :: Nothing () {
    array := [1 .. 4, 2]; // wont compile
}
```

In the above example a rule ```array_sequese_remainder``` is set. The three examples show what the compiler will do, depending on how the attribute was set.

#### TODO: others
other ideas could include:

* Disallow heap allocation
* No classes
* Recursion rules
* Memory Management
* Out of bounds
* Exceptions
* No Implicit type conversions
* Custom attributes?
* And a lot more

This may add a lot of complexity to the compiler, but it also gives a lot more power to the programmer to control the behavior of their code.
It also allows the programmer to decide how unsafe the code should be.

## Features that has to be covered

To compete with C there are many language features that have to be met, and other have to be considered.
This is a short and incomplete list of things that have yet to be specified.

* Memory management
    * Memory is allocated on the stack unless otherwise specified
    * Memory allocation and deallocation is handled by the user
* Inline Assembly / Calling C code
    * Inline Assembly that map to the C calling
    * Potentially inline LLVM (Compiler should enforce LLVM target language then)
    * Call c code
* C Standard Library vs Own Standard Library
    * Maybe through just calling c code
* Typecasting
    * Possible conversions:
    * ```myint to Float```
    * ```myint as Float```
    * ```typecast(myint, Float)``` or ```#cast(myint,Float)``` and let the compiler do the work from behind.
    * Typecasting custom types?
        * Rules to specify how casting can be done
* Selective/Iterative control flow
* Must return values be used / return void
    * Can return ```Nothing``` if there is nothing to return
    * Rules for whether it is allowed to ignore the return of a function
        * Maybe even specify it per function, fx. printing returns a status (in C), but it is rarely used.
* Enums or other simple abstraction
    * Coming soon
* Pointer Arithmetics / Interacting directly with memory addresses
    * Maybe in the distant future
* Preprocessor?
    * Could be fun to do
    * Could tie into rules
    * But is it a good idea?
* Use of multiple files
    * Keep declarations local / global
        * public private
    * Overwriting global declarations with local
        * Namespace
* I/O, string and memory manipulation
    * UTF8 support
    * Part of libraries
* UI?
    * Let C worry about that
* Debugging
    * When we know more
* Unions?
    * Maybe a better type?
* Error handling
    * Maybe
* Concurrency / Parallelism
    * pthreads until something better arise.
    * Scheduler library?
    * SPPL as target language
        * Oh dear, imperative => functinal => imperative. And the tuples, oh the horror...
* Generics
    * Compile time constrains
* Method overloading
    * Allow it and have rules to control its use
* Target language
    * C
    * LLVM
    * SPPL :D
    * IR
        * Poke to JIT compilation for a subset of the code for running higher level stuff?