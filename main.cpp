#include "Fraction/Fraction.hpp"
#include "RpnCalculator/RpnCalculator.hpp"

#include <iostream>

int main() {
    std::vector<std::string> formula = {"1", "5", "+", "2", "3", "+", "*"};
    std::cout << RpnCalculator::calculate(formula) << std::endl;
    return 0;
}