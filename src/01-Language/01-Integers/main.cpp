// The compiler ignores any text after two forward slashes.
// This space lets us write whatever we want.

/*
This is a multi-line comment, in case we want to write
comments that span multiple lines without writing "//"
on every line.
*/

// Anything that starts with a pound sign tells the compiler something
// it needs to know. We don't need to get too thick in the woods yet,
// but for now it's sufficient to know this is for including code
// we'll use later to print stuff.
#include <iostream>
// For fixed-width integer types like int8_t, int16_t, etc. (discussed below)
#include <cstdint>
// This means "copy and paste everything from "main.hpp" right here 
// if it hasn't been copied before
#include "main.hpp" 

int main() { 
    // the first statement in this function is the first
    // statement to ever run in this program.

    /////////////// Declaring and printing variables ////////////////

    // Let's declare a new variable and assign it the name "a".
    // Give it a value of 0 for now.
    int a = 0;

    // Every time we declare a name for something, it will always
    // be preceeded by the data type (in this case, "a" is
    // of type "int")

    // Let's print something to the terminal.
    std::cout << "00: Hello world!";

    // This syntax is weird, and it bothers even some professional
    // C++ developers. In this case, imagine you're using the "<<" 
    // characters to flush text or numbers or special characters 
    // down a pipe into the output terminal from left to right.

    // This time, let's tell the terminal that this is the END of 
    // the Line (endl)
    std::cout << std::endl;
    // The terminal prints "00: Hello World!"

    // Let's print multiple strings of text together.
    // This is syntactic sugar, a fun trick to make code easier to read
    std::cout << "01: duck " << "duck " << "goose" << std::endl;
    // The terminal prints "01: duck duck goose"

    // Here's where everything ties together. Besides just printing
    // text and special characters, we can also print values of
    // numbers:
    std::cout << "02: a = " << a << std::endl;
    // The terminal prints "02: a = 0"

    // Let's declare a new number called "my_byte". Let it also be a 
    // signed integer, but constrain its value to whatever fits
    // in 8 bits.
    int8_t my_byte;

    // Let our new variable be the value of a+1
    my_byte = a + 1; // 0 + 1 = 1

    // Now we have two variables:
    // a = 0
    // my_byte = 1

    // Print the results: 
    std::cout << "03: a="<< a << " my_byte="<<(int)my_byte << std::endl;
    // The terminal prints "03: a=0 my_byte=1"

    /////////////// Numeric operators ////////////////

    // We can do basic math using standard operators.
    int b = 10;
    int c = 3;
    std::cout << "04: " << b << " + " << c << " = " << (b + c) << std::endl;
    // The terminal prints "04: 10 + 3 = 13"
    std::cout << "05: " << b << " - " << c << " = " << (b - c) << std::endl;
    // The terminal prints "05: 10 - 3 = 7"
    std::cout << "06: " << b << " * " << c << " = " << (b * c) << std::endl;
    // The terminal prints "06: 10 * 3 = 30"
    // Integer division truncates the decimal part (10 / 3 = 3).
    std::cout << "07: " << b << " / " << c << " = " << (b / c) << std::endl;
    // The terminal prints "07: 10 / 3 = 3"
    // The modulo operator (%) gives the remainder (10 / 3 = 3 remainder 1).
    std::cout << "08: " << b << " % " << c << " = " << (b % c) << std::endl;
    // The terminal prints "08: 10 % 3 = 1"

    /////////////// Bitwise operators ////////////////

    // Computers represent numbers as bits (0s and 1s).
    // We can see the binary representation using our helper function.
    std::cout << "09: 5 in binary: ";
    print_binary(5); // a routine we define in main.hpp
    std::cout << std::endl;
    // The terminal prints "5 in binary: 00000101"
    
    // AND (&): Both bits must be 1. (0101 & 0011 = 0001 -> 1)
    std::cout << "10: 5 & 3 = " << (5 & 3) << std::endl;
    // The terminal prints "09: 5 & 3 = 1"
    // OR (|): Either bit can be 1. (0101 | 0011 = 0111 -> 7)
    std::cout << "11: 5 | 3 = " << (5 | 3) << std::endl;
    // The terminal prints "10: 5 | 3 = 7"
    // XOR (^): Bits must be different. (0101 ^ 0011 = 0110 -> 6)
    std::cout << "12: 5 ^ 3 = " << (5 ^ 3) << std::endl;
    // The terminal prints "11: 5 ^ 3 = 6"
    // Left Shift (<<): Shift bits left, or multiply by 2^n (0101 << 2 = 10100 -> 20).
    std::cout << "13: 5 << 2 = " << (5 << 2) << std::endl;
    // The terminal prints "12: 5 << 1 = 10"

    /////////////// Integer overflow ////////////////

    // int8_t is 8 bits. The max value is 127 (binary 01111111).
    int8_t max_val = 127;
    std::cout << "14: max_val = " << (int)max_val << std::endl;
    // The terminal prints "13: max_val = 127"

    // Adding 1 to the max value causes overflow.
    // 01111111 + 1 = 10000000. In 2s complement, the first bit is the sign.
    // 10000000 represents -128.
    max_val = max_val + 1;
    std::cout << "15: max_val + 1 = " << (int)max_val << " (Overflow!)" << std::endl;
    // The terminal prints "14: max_val + 1 = -128 (Overflow!)"

    /////////////// Two's complement ////////////////

    // How are negative numbers represented?
    // The most significant bit (the leftmost bit) is the "sign bit".
    // If it's 1, the number is negative.
    //
    // One way to make a negative number is "1s complement": just flip all bits.
    // 00000001 (1) -> 11111110 (-1)
    // But this gives us two zeros: 00000000 (+0) and 11111111 (-0).
    // This makes arithmetic hard for the computer.
    //
    // Instead, we use "2s complement".
    // Step 1: Flip all bits (1s complement).
    // Step 2: Add 1.
    // This eliminates -0 and makes addition work naturally for negative numbers.

    int val = 5;
    std::cout << "16: ~5 + 1 = " << (~val + 1) << " (which is -5)" << std::endl;
    // The terminal prints "15: ~5 + 1 = -5 (which is -5)"

    /////////////// Measuring the size of a piece of data ////////////////
    // The size of some types can vary depending on the system (e.g., 32-bit vs. 64-bit).
    // The `sizeof` operator returns the size in bytes.

    // Standard integer types (sizes can vary by system/compiler)
    std::cout << "17: sizeof(char)      = " << sizeof(char)      << " bytes" << std::endl;
    // The terminal prints "17: sizeof(char)      = 1 bytes"
    std::cout << "18: sizeof(short)     = " << sizeof(short)     << " bytes" << std::endl;
    // The terminal prints "18: sizeof(short)     = 2 bytes"
    std::cout << "19: sizeof(int)       = " << sizeof(int)       << " bytes" << std::endl;
    // The terminal prints "19: sizeof(int)       = 4 bytes"
    std::cout << "20: sizeof(long)      = " << sizeof(long)      << " bytes" << std::endl;
    // The terminal prints "20: sizeof(long)      = 8 bytes"
    std::cout << "21: sizeof(long long) = " << sizeof(long long) << " bytes" << std::endl;
    // The terminal prints "21: sizeof(long long) = 8 bytes"

    // Fixed-width integer types (guaranteed size across systems, from <cstdint>)
    std::cout << "22: sizeof(int8_t)    = " << sizeof(int8_t)    << " bytes" << std::endl;
    // The terminal prints "22: sizeof(int8_t)    = 1 bytes"
    std::cout << "23: sizeof(int16_t)   = " << sizeof(int16_t)   << " bytes" << std::endl;
    // The terminal prints "23: sizeof(int16_t)   = 2 bytes"
    std::cout << "24: sizeof(int32_t)   = " << sizeof(int32_t)   << " bytes" << std::endl;
    // The terminal prints "24: sizeof(int32_t)   = 4 bytes"
    std::cout << "25: sizeof(int64_t)   = " << sizeof(int64_t)   << " bytes" << std::endl;
    // The terminal prints "25: sizeof(int64_t)   = 8 bytes"

    return 0; // We'll understand this part better later.
}