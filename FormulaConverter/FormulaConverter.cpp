#include "FormulaConverter.hpp"

#include <algorithm>
#include <stack>

const std::map<std::string, int> FormulaConverter::OP_PRECEDENCES_FOR_INFIX = {
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

        const bool is_operator = OP_PRECEDENCES_FOR_INFIX.find(token) != OP_PRECEDENCES_FOR_INFIX.end();
        if (is_operator) {
            while (!op_stack.empty()) {
                const auto top = op_stack.top();
                if (OP_PRECEDENCES_FOR_INFIX.find(top) == OP_PRECEDENCES_FOR_INFIX.end()) break;
                if (OP_PRECEDENCES_FOR_INFIX.at(token) > OP_PRECEDENCES_FOR_INFIX.at(top)) break;
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