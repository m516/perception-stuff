# Project 01-00: Hello World

Take a look at `main.cpp` and `CMakeLists.txt`. These files have been reduced as much as possible. Every sketch you find later will include those lines in those files. The goal for this sketch is to understand the purpose for the files and their contents. 

Let's address the C++ file (ending with `.cpp`) first, then the CMake file (CMakeLists.txt)

## About the C++ file

### How is it used?

Computers (specifically Central Processing Units, or CPUs) are usually described as data processors, designed to use programs to decide what outputs correspond to a certain set of inputs. Their inputs, outputs, and programs are all bits and bytes. How do bits and bytes tell a computer how to process data?

Generally speaking, each computer
* is designed so that certain bit sequences map to *instructions*, fundamental number-processing routines.
* runs one instruction at a time*
* has a small scratch space of 16-1k numbers called *registers*.
* has some standard length for these registers, e.g. 16 bits, 64 bits, usually some power-of-two of bytes called a *word*
* has a larger amount of *memory* (usually RAM) that's a long string of bits, usually split into words
* stores the program (as a sequence of instructions encoded as bytes) and input data (as a string of numbers encoded as bytes) in that memory (sometimes side-by-side).
* keeps track of the address of the current instruction as a register.

*meaningful for this discussion but usually not true due to [pipelining](https://en.wikipedia.org/wiki/Instruction_pipelining)

Common instructions include:
* arithmetic (addition, negation, ...)
* comparisons (is greater than, is equal to, ...)
* moving data between memory and registers
* jumping to another instruction besides the next one
* *conditionally* jumping to another instruction based on the contents of a register

The set of rules that map a bit sequence to an instruction is called an Instruction Set Architecture (ISA).

Let's briefly take a look at a relatively new ISA called [RISC-V](https://docs.riscv.org/reference/isa/_attachments/riscv-unprivileged.pdf). While a 700+ page document can be intimidating to read, notice this standard set of instructions within the first 50 pages of the document:
* arithmetic and comparisons: section 2.4
* moving data between memory and registers: section 2.6
* unconditional jumping: section 2.5.1
* conditional jumping: section 2.5.2

We can use these specs to craft a program, (a list of bits and bytes) that a computer can execute to compute whatever we want, assuming that computer is properly designed to interpret instructions using the RISC-V ISA.

For example, suppose we want to compute the solution to 2+3. That's possible with four instructions:
1. Load the constant 2 into register 5.
2. load the constant 3 into register 4.
3. add the values of registers 5 and 4, and put the result in register 5.
4. store the contents of register 5 in memory somewhere for processing later.

Each of those instructions has a short name and a pattern in the ISA, called *assembly code*. Let's translate:
```asm
li     a5,2
li     a5,3
add    a5,a5,a4
sw     a5,-20(s0)
```

Using the ISA, we can then translate from assembly to a set of bits. 
```
01000111 10001001 
01000111 10001101 
10010111 10111010 
11111110 11110100 00100110 00100011
```

Take away the whitespace we're using to make the program easier for us to read, and we're left with
```
01000111100010010100011110001101100101111011101011111110111101000010011000100011
```

1s and 0s are hard for us to read. We can compress them for viewing purposes with *hexidecimal*, where each group of four bits (called a nibble) is grouped together into one character as follows:

| Decimal | Hex  | Binary   |
|---------|------|----------|
| 0       | 0    | 0000     |
| 1       | 1    | 0001     |
| 2       | 2    | 0010     |
| 3       | 3    | 0011     |
| 4       | 4    | 0100     |
| 5       | 5    | 0101     |
| 6       | 6    | 0110     |
| 7       | 7    | 0111     |
| 8       | 8    | 1000     |
| 9       | 9    | 1001     |
| 10      | A    | 1010     |
| 11      | B    | 1011     |
| 12      | C    | 1100     |
| 13      | D    | 1101     |
| 14      | E    | 1110     |
| 15      | F    | 1111     |

Condense our program in hexadecimal and the machine code for our little program is `4789478D97BAFEF42623`.

The most tedious part of creating this program was finding what sequence of instructions brings about the value we want to compute. Unfortunately, all that work is meaningless if suddenly we decide we need this program to work on a PC: Most PCs are designed around [AMD/Intel x86-64](https://cdrdv2.intel.com/v1/dl/getContent/671200) or [Arm A64](https://developer.arm.com/documentation/107829/0201/?lang=en), two ISAs that are not compatible with RISC-V.

Fortunately, part of this process can be automated! Programs exist that convert your ideas into machine code, so long as you can translate your ideas into their language. These programs are called *compilers*. 

We will use a C++ compiler to convert code we write in the C++ language into machine code for our system, so we never have to look at the ISA again, and we can just focus on learning the C++ language.

In C++, our little program can be written as:
```cpp
int twoPlusThree() {
    int a = 2;
    int b = 3;
    int c = a + b;
    return c;
}
```

Let's focus on this part (the surrounding brackets will make more senses later):
```cpp
int a = 2;
int b = 3;
int c = a + b;
```

We can use a compiler (in this case x86-64 Clang 21.1.0, via [Godbolt](https://godbolt.org/)) to convert machine code compatable with my laptop (which is designed to interpret x86-64 programs):
```asm
55
48 89 e5
c7 45 fc 02 00 00 00
c7 47 f8 03 00 00 00
8b 45 fc
03 45 f8
89 45 f4
8b 45 f4
5d
c3
```

It also lets us pop the hood and see the assembly it generated:
```asm
_Z12twoPlusThreev:
 push   %rbp
 mov    %rsp,%rbp
 movl   $0x2,-0x4(%rbp)
 movl   $0x3,-0x8(%rbp)
 mov    -0x4(%rbp),%eax
 add    -0x8(%rbp),%eax
 mov    %eax,-0xc(%rbp)
 mov    -0xc(%rbp),%eax
 pop    %rbp
 ret
```

Want to run this program on a Nintendo Switch 2? It might look like this. (compiled from armv8-a Clang 21.1.0 via Godbolt)
```
D1 00 43 FF
52 80 00 48
B9 00 0F E8
52 80 00 68
B9 00 0B E8
B9 40 0F E8
B9 40 0B E9
0B 09 01 08
B9 40 07 E0
91 00 43 FF
D6 5F 03 C0
```

### What's inside?

There is just one C++ source code file in this project. It contains the smallest program possible (doing nothing):
```cpp
int main() {
}
```

To invoke the compiler to build the executable, run this command in your terminal or command prompt after navigating to the project folder:
```bash
gcc main.cpp
```

All C/C++ compilers look for a function called `main`. This is the entry point into the program. Take it away and you get an error message like this:
```
gcc main.cpp
/usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/11/../../../x86_64-linux-gnu/Scrt1.o: in function `_start':
(.text+0x1b): undefined reference to `main'
collect2: error: ld returned 1 exit status
```

Here, GCC failed to compile the code in our c++ file. Let's peek behind the covers for a bit to see why:

Most C++ projects are organized into multiple files. If I had two files `a.cpp` and `b.cpp`, I could tell GCC to compile them both by calling `gcc a.cpp b.cpp`. For each file to compile, GCC calls an assembler that translates it from the C++ language to the appropriate assembly language. The output is a list of assembly files. Those files are linked together by a separate program called a *linker*. That linker is `/usr/bin/ld` in this case, and it expects the function `main` as an entry point when building an executable. When it doesn't find one in the object compiled from `main.cpp`, it quits.

The moral of this story is: wherever there is a `main` function, that is where the program starts.

## About the CMake file

CMake is a cross-platform way to manage large C++ projects that span many files, including files other people write and publish called *libraries*

We won't worry too much about CMake. Unless creating writing your own sketch and it's wildly different from one any existing sketch, it isn't too hard to copy and paste.

If you're curious how they work, feel free to poke around at some of the other files here, or check out the [CMake Reference Documentation](https://cmake.org/cmake/help/latest/index.html).

The standard workflow for C++ executables is:
```cmake
# Define the name of this project. There can only be one project.
project (<sketch_name> C CXX)

# Set minimum standards so people don't get errors if they're on unsupported versions.
cmake_minimum_required (VERSION <minimum_cmake_version>)
set (CMAKE_CXX_STANDARD <C++_version>)

# Find libraries (search how to best include libraries. Someone has probably already done it in CMake)
find_package(<package_name>)
...

# Add source to this project's executable. There can be effectively unlimited executables.
add_executable (<executable_name> <list_of_cpp_files>)

# Advanced
target_link_libraries (<executable_name> <library_list>)
target_include_directories(<executable_name> <path_with_library_headers>)
```
Replace any `<variable>` as appropriate.