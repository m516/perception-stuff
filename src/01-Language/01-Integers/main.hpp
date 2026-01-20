/*
Feel free to look around, but there isn't anything super interesting to see here.
*/

#pragma once
#include <iostream>

// A helper function to print the binary representation of a number.
// We'll discuss how functions work in detail later, but for now,
// just know we'll use this later to print the binary value of a
// number.
//
// It'll look like this:
// print_binary(a); for any integer "a"
void print_binary(int value) {
    for (int i = 7; i >= 0; i--) {
        std::cout << ((value >> i) & 1);
    }
}