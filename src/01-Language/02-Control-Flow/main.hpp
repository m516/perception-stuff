#pragma once
#include <iostream>
#include <string>

// A helper to print section headers to make the output cleaner.
// We use this in main.cpp to separate the different examples.
void print_section(std::string title) {
    std::cout << std::endl << "=== " << title << " ===" << std::endl;
}