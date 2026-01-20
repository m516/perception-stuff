#include <iostream>

int main() {
    std::cout << "--- 01_02_Flow: Control Flow Structures ---" << std::endl;

    // 1. If/Else
    // Used to execute code blocks based on boolean conditions.
    std::cout << "\n[1] If/Else Statements" << std::endl;
    int temperature = 25;
    std::cout << "Current temperature: " << temperature << "C" << std::endl;

    if (temperature > 30) {
        std::cout << "It is hot outside." << std::endl;
    } else if (temperature > 20) {
        std::cout << "It is a pleasant day." << std::endl;
    } else {
        std::cout << "It is cold." << std::endl;
    }

    // 2. While Loop
    // Repeats a block of code as long as a condition is true.
    std::cout << "\n[2] While Loop" << std::endl;
    int fuel = 5;
    std::cout << "Starting engine with fuel: " << fuel << std::endl;
    while (fuel > 0) {
        std::cout << "Vroom... (Fuel: " << fuel << ")" << std::endl;
        fuel--;
    }
    std::cout << "Engine stopped (Out of fuel)." << std::endl;

    // 3. Do/While Loop
    // Similar to while, but guarantees the code block runs at least once.
    std::cout << "\n[3] Do/While Loop" << std::endl;
    int retry_count = 0;
    do {
        std::cout << "Connecting to server... (Attempt " << retry_count + 1 << ")" << std::endl;
        retry_count++;
    } while (retry_count < 3);
    std::cout << "Connection failed after 3 attempts." << std::endl;

    // 4. For Loop
    // Ideal for iterating a specific number of times or over arrays.
    std::cout << "\n[4] For Loop" << std::endl;
    std::cout << "Counting even numbers:" << std::endl;
    for (int i = 0; i <= 10; i += 2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // 5. Switch Statement
    // A cleaner way to select between many values for a single variable.
    std::cout << "\n[5] Switch Statement" << std::endl;
    char command = 'S'; // 'S' for Start
    std::cout << "Received command: " << command << std::endl;

    switch (command) {
        case 'S':
            std::cout << "Action: Start System" << std::endl;
            break;
        case 'P':
            std::cout << "Action: Pause System" << std::endl;
            break;
        case 'Q':
            std::cout << "Action: Quit" << std::endl;
            break;
        default:
            std::cout << "Action: Unknown Command" << std::endl;
            break;
    }

    return 0;
}