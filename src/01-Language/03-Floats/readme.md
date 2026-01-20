# Sketch 01-03: Floats

Sketch [01-01](/src/01-Language/01-Integers/) introduced integers, which work nicely for counting how many things there unless fractional values are possible, like using 2 1/2 apples for a recipe or measuring the angular velocity of a car. Also, all the integer types we discussed are bound between += 2^64, so we can't express the number of atoms in the universe. At the expense of precision, we can account for a much wider range of values by storing them in a **floating point** type (`float` and `double`).

## What are floating point numbers, and when should I use them?

Imagine writing a number in scientific notation, like $1.234 \times 10^5$. The decimal point "floats" based on the exponent. Most computers do something similar, using the standard IEEE 754 (https://en.wikipedia.org/wiki/IEEE_754), defined as follows:

$$ \text{Value} = (-1)^{\text{sign}} \times (1 + \text{mantissa}) \times 2^{\text{exponent} - \text{bias}} $$

This formula may be hard to parse, so let's walk through two examples: -7.5 and 0.1.

### Converting -0.75 to a float
First, convert the absolute value of the number to binary:
$0.75 = 0.5 + 0.25 = 2^{-1} + 2^{-2} = 0.11_2$

Now, write it in "scientific notation" (normalized form), so there's a 1 before the binary point:
$0.11_2 = 1.1_2 \times 2^{-1}$

From this, we can extract the components:
*   **Sign:** The number is negative, so the sign bit is `1`.
*   **Exponent:** The exponent is -1. For a `float`, the bias is 127. So, the stored exponent is $-1 + 127 = 126$. In binary, $126 = 01111110_2$.
*   **Mantissa:** The part after the binary point in the normalized form is `1`. Since the mantissa is 23 bits, we pad with zeros: `10000000000000000000000`.

Combining these, the 32-bit float representation of -0.75 is:
`1 01111110 10000000000000000000000`

### Converting 0.1 to a float

This one is trickier because 0.1 is a repeating decimal in binary.
First, convert 0.1 to binary:
$0.1_{10} = 0.0001100110011..._2$

Now, normalize it:
$0.0001100110011..._2 = 1.100110011..._2 \times 2^{-4}$

Extract the components:
*   **Sign:** The number is positive, so the sign bit is `0`.
*   **Exponent:** The exponent is -4. With a bias of 127, the stored exponent is $-4 + 127 = 123$. In binary, $123 = 01111011_2$.
*   **Mantissa:** The part after the binary point in the normalized form is `1.10011001...`. Since the mantissa is 23 bits, we pad with zeros: `11001100110011001100110`

Combining these, the 32-bit float representation of 0.1 is:
`0 01111011 110011001100110011001`

### Special numbers

IEE 754 also supports Infinity, -Infinity, and NaN (not a number, usually a divide-by-zero error).
Those have special codes:
* **Infinity**: `0 11111111 00000000000000000000000`
* **-Infinity**: `1 11111111 00000000000000000000000`
* **NaN**: `0 11111111 10000000000000000000000` (or any mantissa that is not all zeros)