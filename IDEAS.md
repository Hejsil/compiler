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
```



### Control Flow

