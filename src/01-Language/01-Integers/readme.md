# Sketch 01-01: Integers

Here is the little program we used in our thought experiment in the [previous sketch](/src/01-Language/00-HelloWorld).
```cpp
int a = 2;
int b = 3;
int c = a + b;
```

## Why is the symbol `int` being thrown around everywhere?

Think of an `int` as a signed number for now. In that example, we create three variables of the `int` type: `a`, `b`, and `c`. These variables are mutable, i.e. can change over time as code is executed from top to bottom. For example, this works:
```cpp
int a;  // a can be any int
a = 0;  // assign a to 0
a + 1;  // 0 + 1 = 1
a = 1;  // assign a to 1
a + 1;  // 1 + 1 = 2;
a = -1; // assign a to -1
a + 1;  // -1 + 1 = 0
```

Each line (more specifically, each group of characters separated by a semicolon) is a *statement*, telling the C++ compiler should do something after the previous statement and before the next one.

Remember how computers generally have some standard length for the registers, and a number with that many bits is a "word"? An "integer" or `int` is a signed integer that consumes the space of a word.

## Theres a new file!

The new file (ending in `.hpp`) is also a C++ file called a *header* file. Unlike the *implementation* file (ending in .cpp), GCC does not compile it into an object by itself. Instead, the header's contents are copy-pasted any time the compiler encounters the line
```cpp
#include "main.hpp"
```
when compiling a `.cpp` file.