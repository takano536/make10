#include "Tokenizer.hpp"

#include <algorithm>
#include <stdexcept>

#include <iostream>

std::vector<std::string> Tokenizer::tokenize(const std::string& formula) {
    std::vector<std::string> tokens;
    std::size_t pos = 0;

    while (pos < formula.length()) {
        const char& letter = formula.at(pos);

        if (std::isspace(letter)) {
            pos++;
            continue;
        }
        if (std::isdigit(letter) || letter == '.') {
            tokens.push_back(read_number(formula, pos));
            continue;
        }
        if (is_operator(letter)) {
            tokens.push_back(read_operator(formula, pos));
            continue;
        }
        if (letter == '(' || letter == ')') {
            tokens.push_back(std::string(1, letter));
            pos++;
            continue;
        }

        throw std::runtime_error("Invalid token: " + std::string(1, letter));
    }

    return tokens;
}

bool Tokenizer::is_operator(const char& letter) {
    for (const auto& op : OPERATORS) {
        if (op.front() == letter) return true;
    }
    return false;
}

std::string Tokenizer::read_number(const std::string& formula, std::size_t& pos) {
    std::string number;
    bool has_dot = false;

    while (pos < formula.length()) {
        const char& letter = formula.at(pos);

        if (std::isdigit(letter) || (!has_dot && letter == '.')) {
            number.push_back(letter);
            if (letter == '.') has_dot = true;
            pos++;
            continue;
        }

        break;
    }

    return number;
}

std::string Tokenizer::read_operator(const std::string& formula, std::size_t& pos) {
    std::string op;

    for (const auto& op_str : OPERATORS) {
        if (formula.compare(pos, op_str.length(), op_str) == 0) {
            op = op_str;
            pos += op_str.length();
            break;
        }
    }

    return op;
}