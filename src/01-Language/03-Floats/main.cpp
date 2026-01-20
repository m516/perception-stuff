#include <iostream>
#include <iomanip> // For std::setprecision
#include <cstdint>
#include "main.hpp"

int main() {
    // 1. Basics: float vs double
    // 'float' is usually 32-bit, 'double' is usually 64-bit.
    // The 'f' suffix tells the compiler to treat the literal as a float.
    float f = 3.1415926f;
    double d = 3.141592653589793;

    std::cout << "01: sizeof(float)  = " << sizeof(float) << " bytes" << std::endl;
    std::cout << "02: sizeof(double) = " << sizeof(double) << " bytes" << std::endl;

    // 2. Precision
    // Floats have limited precision. Notice how 'f' loses accuracy compared to 'd'.
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "03: f = " << f << std::endl;
    std::cout << "04: d = " << d << std::endl;

    // 3. Floating point math is tricky
    // Because 0.1 and 0.2 cannot be exactly represented in binary,
    // their sum is not exactly 0.3.
    float a = 0.1f;
    float b = 0.2f;
    float sum = a + b;
    std::cout << "05: 0.1f + 0.2f = " << sum << std::endl;
    
    if (sum == 0.3f) {
        std::cout << "06: sum == 0.3f is TRUE" << std::endl;
    } else {
        std::cout << "06: sum == 0.3f is FALSE (actually " << sum << ")" << std::endl;
    }

    // 4. Special values
    // Floating point numbers can represent Infinity and Not-a-Number (NaN).
    float zero = 0.0f;
    float inf = 1.0f / zero;
    float nan = 0.0f / zero;

    std::cout << "07: 1.0 / 0.0 = " << inf << std::endl;
    std::cout << "08: 0.0 / 0.0 = " << nan << std::endl;

    // 5. Binary representation (IEEE 754)
    // Floats are stored as: Sign bit | Exponent | Mantissa (fraction)
    std::cout << "09:  1.5 in binary: ";
    print_float_binary(1.5f);
    std::cout << std::endl;

    std::cout << "10: -1.5 in binary: ";
    print_float_binary(-1.5f);
    std::cout << std::endl;

    return 0;
}