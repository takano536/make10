#include "RpnCalculator.hpp"

#include <stack>
#include <stdexcept>

const std::map<std::string, std::function<Fraction(const Fraction&, const Fraction&)>> RpnCalculator::OPERATORS = {
    {"+", [](const Fraction& lhs, const Fraction& rhs) { return lhs + rhs; }},
    {"-", [](const Fraction& lhs, const Fraction& rhs) { return lhs - rhs; }},
    {"*", [](const Fraction& lhs, const Fraction& rhs) { return lhs * rhs; }},
    {"/", [](const Fraction& lhs, const Fraction& rhs) { return lhs / rhs; }},
};

Fraction RpnCalculator::calculate(const std::vector<std::string>& formula) {
    std::stack<Fraction> stack;
    for (const auto& str : formula) {
        if (!is_operater(str)) {
            stack.push(Fraction(std::stoi(str)));
            continue;
        }

        const auto rhs = stack.top();
        stack.pop();
        const auto lhs = stack.top();
        stack.pop();
        stack.push(operate(lhs, rhs, str));
    }

    if (stack.size() != 1) throw std::invalid_argument("Invalid formula.");
    return stack.top();
}

Fraction RpnCalculator::operate(const Fraction& lhs, const Fraction& rhs, const std::string op) {
    if (!is_operater(op)) throw std::invalid_argument("Invalid operator.");
    return OPERATORS.at(op)(lhs, rhs);
}

bool RpnCalculator::is_operater(const std::string& str) {
    return OPERATORS.find(str) != OPERATORS.end();
}