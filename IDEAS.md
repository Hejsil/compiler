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
Vector3 : struct { Int, Int, Int } : struct {
    x, y, z: Int;
}

mul : Int(Int, Int) : Int(x: Int, y: Int) {
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

## Basic types
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

## Language Constructs 
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

### Foreach loop
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
array := Int[] {1,2,3,4,5};
foreach i in array
```

### Control Flow


### Built In Functions
The language should support usefull built in functions that can do things which cannot be expressed in the base language without them.

#### Type of

#### Size of

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
