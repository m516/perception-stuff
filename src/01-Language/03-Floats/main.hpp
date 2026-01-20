#pragma once
#include <iostream>
#include <cstring> // For std::memcpy
#include <cstdint>

// Helper to print the binary representation of a float.
// Unlike integers, we can't just use bitwise operators directly on a float.
// We use std::memcpy to copy the raw bits of the float into an unsigned integer
// of the same size (uint32_t), then print those bits.
void print_float_binary(float value) {
    uint32_t int_rep;
    std::memcpy(&int_rep, &value, sizeof(float));

    for (int i = 31; i >= 0; i--) {
        std::cout << ((int_rep >> i) & 1);
        if (i == 31 || i == 23) {
            std::cout << " "; // Separate Sign, Exponent, and Mantissa for readability
        }
    }
}