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

Declaration:
```
// Syntax <name> : <type>
x : Int;
y : Double;
```

Assignment:
```
// Syntax <variable> = <expr>
x = 5;
y = 5.5;
```

We can combine these, if we want to initialize at declaration:
```
x : Int = 5;
y : Double = 5.5;
```

And the types can be infered by omitting the type:
```
x := 5;
y := 5.5;
```


#### Complex Declaration and Assignment
Simple declaration:
```
<name> : <type> <maybe assignment> ;
```
Simple declarations follow the syntax as above.

Complex declaration:
```
<name> :: <complextype> {
    // Body
}
```

Where in the above the complex type can be one of:

* Struct/Record: A data structure that can contain one or more simple declarations
* Class: A data structure that can contain both simple and advanced data structures. (This is not guaranteed to be supported)
* Function signature: A signature for a function or procedure, following the construction
    ```<return type> (<arg1> : <type1>, ..., <argn> : <typen>)```
* Type: Not yet sure if this is allowed
Etc...

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
// array4 has no array sequense alternative.

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
array1 := {1 .. 5};
array2 := {2 .. 8, 2};
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

### Language options

It should be possible for the user to control what the compiler should and shouldn't allow. This will most likely be in a separate file.
For complex programs over multiple folders, multiple files could be used, where the rules apply to that folder and all sub-folders of source files.

```
// Using the example from "Array Literals"
rule(arraysequeseremainder) = try warning
```

In the above example a rule ```arraysequenseremainder``` is set. This rule have the following options:

* try: It will try to fill the array as shown in the comment from the example
* ceiling: The compiler will include the next number in the array as well, making it one element larger```array5 := Int{1,3,5}```.
* warn: It will show a warning when it happens. ```warn``` cannot be called without ```try``` or ```ceiling```.
* error: The compiler will throw an error, because the program does not allow it

other ideas could include:

* Disallow heap allocation
* No classes
* Recursion rules
* Memory Management
* Out of bounds
* Exceptions
* And a lot more

This may add a lot of complexity to the compiler, but it also gives a lot more power to the programmer to control the behavior of their code.
It also allows the programmer to decide how unsafe the code should be.