#include "Fraction/Fraction.hpp"
#include "RpnCalculator/RpnCalculator.hpp"
#include "Tokenizer/Tokenizer.hpp"

#include <iostream>

int main() {
    std::string formula;
    std::cout << "Enter a formula> ";
    std::getline(std::cin, formula);

    std::cout << "Formula: " << formula << std::endl;

    auto tokens = Tokenizer::tokenize(formula);
    std::cout << "Tokens number: " << tokens.size() << std::endl;
    for (const auto& token : tokens) std::cout << token << std::endl;

    return 0;
}