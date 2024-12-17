#include "Fraction/Fraction.hpp"

#include <iostream>

int main() {
    Fraction a(3, 2);
    Fraction b(8, 6);

    std::cout << a << " + " << b << " = " << a + b << std::endl;
    std::cout << a << " - " << b << " = " << a - b << std::endl;
    std::cout << a << " * " << b << " = " << a * b << std::endl;
    std::cout << a << " / " << b << " = " << a / b << std::endl;

    std::cout << a << " + " << 3 << " = " << a + 3 << std::endl;
    return 0;
}