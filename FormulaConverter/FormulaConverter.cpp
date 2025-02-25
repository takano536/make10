#include "FormulaConverter.hpp"
#include "../Tokenizer/Tokenizer.hpp"

#include <algorithm>
#include <stack>
#include <stdexcept>
#include <utility>

const std::map<std::string, int> FormulaConverter::OP_PRIO_FOR_INFIX = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
};

std::vector<std::string> FormulaConverter::infix2rpn(const std::vector<std::string>& tokens) {
    std::vector<std::string> rpn;
    std::stack<std::string> op_stack;
    std::stack<std::string> num_stack;
    auto is_digit = [](const char& c) { return std::isdigit(c) || c == '.'; };

    for (const auto& token : tokens) {

        const bool is_number = std::all_of(token.begin(), token.end(), is_digit);
        if (is_number) {
            rpn.push_back(token);
            continue;
        }

        const bool is_operator = OP_PRIO_FOR_INFIX.find(token) != OP_PRIO_FOR_INFIX.end();
        if (is_operator) {
            while (!op_stack.empty()) {
                const auto top = op_stack.top();
                if (OP_PRIO_FOR_INFIX.find(top) == OP_PRIO_FOR_INFIX.end()) break;
                if (OP_PRIO_FOR_INFIX.at(token) > OP_PRIO_FOR_INFIX.at(top)) break;
                rpn.push_back(top);
                op_stack.pop();
            }
            op_stack.push(token);
            continue;
        }

        if (token == "(") {
            op_stack.push(token);
            continue;
        }

        if (token == ")") {
            while (op_stack.top() != "(") {
                rpn.push_back(op_stack.top());
                op_stack.pop();
            }
            op_stack.pop();
            continue;
        }

        rpn.push_back(token);
    }

    while (!op_stack.empty()) {
        rpn.push_back(op_stack.top());
        op_stack.pop();
    }

    return rpn;
}

std::vector<std::string> FormulaConverter::rpn2infix(const std::vector<std::string>& tokens) {
    std::vector<std::string> infix;
    std::stack<std::pair<std::string, int>> stack;
    auto is_digit = [](const char& c) { return std::isdigit(c) || c == '.'; };

    for (const auto& token : tokens) {

        const bool is_number = std::all_of(token.begin(), token.end(), is_digit);
        if (is_number) {
            stack.push({token, INF});
            continue;
        }

        const bool is_operator = OP_PRIO_FOR_INFIX.find(token) != OP_PRIO_FOR_INFIX.end();
        if (is_operator) {

            if (stack.size() < 2) throw std::runtime_error("Invalid formula.");

            const auto [rhs, rhs_prio] = stack.top();
            stack.pop();
            const auto [lhs, lhs_prio] = stack.top();
            stack.pop();
            const int prio = OP_PRIO_FOR_INFIX.at(token);

            std::string lhs_expr = (lhs_prio < prio) ? "(" + lhs + ")" : lhs;
            std::string rhs_expr = (rhs_prio <= prio) ? "(" + rhs + ")" : rhs;

            stack.push({lhs_expr + " " + token + " " + rhs_expr, prio});
            continue;
        }

        throw std::runtime_error("Invalid formula.");
    }

    if (stack.size() != 1) throw std::runtime_error("Invalid formula.");

    const auto [expr, _] = stack.top();
    return Tokenizer::tokenize(expr);
}