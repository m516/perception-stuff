// Control Flow: How we make decisions and repeat tasks.

#include <iostream>
#include "main.hpp"

int main() {
    // 1. If / Else
    // The most basic form of control flow.
    // If the condition in the parentheses is true, the code block executes.
    print_section("If / Else");
    int a = 10;
    int b = 20;
    
    std::cout << "01: Checking if " << a << " < " << b << "..." << std::endl;
    
    if (a < b) {
        std::cout << "02: a is less than b" << std::endl;
    } else {
        std::cout << "02: a is NOT less than b" << std::endl;
    }

    // 2. While Loop
    // Repeats a block of code as long as the condition is true.
    print_section("While Loop");
    int count = 3;
    std::cout << "03: Counting down..." << std::endl;
    while (count > 0) {
        std::cout << "    " << count << std::endl;
        count--; // Decrement count
    }
    std::cout << "04: Liftoff!" << std::endl;

    // 3. Do / While Loop
    // Similar to while, but checks the condition AFTER the block runs.
    // This guarantees the code runs at least once.
    print_section("Do / While Loop");
    int number = 0;
    do {
        std::cout << "05: This prints at least once. number = " << number << std::endl;
        number++;
    } while (number < 0); // Condition is false immediately, but loop ran once.

    // 4. For Loop
    // A compact way to iterate.
    // Structure: for (initialization; condition; update)
    print_section("For Loop");
    std::cout << "06: Loop from 0 to 4:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "    i = " << i << std::endl;
    }

    // 5. Switch Statement
    // Useful for checking a variable against multiple specific values (cases).
    print_section("Switch Statement");
    int choice = 2;
    std::cout << "07: Choice is " << choice << std::endl;

    switch (choice) {
        case 1:
            std::cout << "08: You chose option 1." << std::endl;
            break; // 'break' prevents falling through to the next case
        case 2:
            std::cout << "08: You chose option 2." << std::endl;
            break;
        default:
            std::cout << "08: Unknown choice." << std::endl;
            break;
    }

    return 0;
}