#include "FormulaConverter/FormulaConverter.hpp"
#include "Fraction/Fraction.hpp"
#include "RpnCalculator/RpnCalculator.hpp"
#include "Tokenizer/Tokenizer.hpp"

#include <iostream>

int main() {
    std::string formula;
    std::cout << "Enter a formula> ";
    std::getline(std::cin, formula);

    std::cout << "Formula: " << formula << std::endl;

    const auto tokens = Tokenizer::tokenize(formula);

    const auto rpn = FormulaConverter::infix2rpn(tokens);

    const auto rpn_formula = Tokenizer::join(rpn);
    std::cout << "RPN formula: " << rpn_formula << std::endl;

    const auto result = RpnCalculator::calculate(rpn);
    std::cout << "Result: " << result << std::endl;

    return 0;
}