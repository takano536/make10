#include "FormulaConverter/FormulaConverter.hpp"
#include "Fraction/Fraction.hpp"
#include "RpnCalculator/RpnCalculator.hpp"
#include "Tokenizer/Tokenizer.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

namespace myfuncs {

void generate_nums(const std::pair<int, int>& range, const int& length, const std::string& curr, std::vector<std::string>& nums) {
    if (curr.length() == length) {
        nums.push_back(curr);
        return;
    }

    const auto& [start, end] = range;
    for (int i = start; i <= end; i++) generate_nums({i, end}, length, curr + std::to_string(i), nums);
    return;
}

static constexpr int powi(const int& x, const int& y) {
    int result = 1;
    for (int i = 0; i < y; i++) result *= x;
    return result;
}

}  // namespace myfuncs

int main() {
    const std::array<std::string, 4> OPS = {"+", "-", "*", "/"};
    static constexpr int TARGET = 10;
    static constexpr int SIZE = 4;

    std::vector<std::string> ops;
    myfuncs::generate_nums({0, 3}, SIZE - 1, "", ops);

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, myfuncs::powi(10, SIZE) - 1);

    std::vector<std::string> ans;

    std::string num;
    while (true) {

        num = std::to_string(dist(gen));
        while (num.length() < SIZE) num = "0" + num;

        for (const auto& op : ops) {

            std::vector<std::string> tokens;
            for (const auto& c : op) tokens.push_back(OPS[c - '0']);
            for (const auto& c : num) tokens.push_back(std::string(1, c));
            std::sort(tokens.begin(), tokens.end());

            do {
                std::string curr_num;
                for (const auto& t : tokens) {
                    if (std::isdigit(t[0])) curr_num += t;
                }
                if (curr_num != num) continue;

                std::vector<std::string> infix_tokens;
                try {
                    infix_tokens = FormulaConverter::rpn2infix(tokens);
                } catch (const std::exception& e) {
                    continue;
                }

                Fraction result = 0;
                try {
                    result = RpnCalculator::calculate(tokens);
                } catch (const std::exception& e) {
                    continue;
                }

                if (result != TARGET) continue;

                const auto infix_formula = Tokenizer::join(infix_tokens);
                ans.push_back(infix_formula);

            } while (std::next_permutation(tokens.begin(), tokens.end()));
        }
        if (!ans.empty()) break;
    }

    while (true) {
        std::cout << num << " = " << TARGET << "? [a: print ans] > ";
        std::string input;
        std::getline(std::cin, input);

        if (input[0] == 'a') break;

        std::vector<std::string> rpn_tokens;
        try {
            rpn_tokens = FormulaConverter::infix2rpn(Tokenizer::tokenize(input));
        } catch (const std::exception& e) {
            std::cout << "Invalid input!: FormulaConverter::infix2rpn" << std::endl;
            continue;
        }

        Fraction result = 0;
        try {
            result = RpnCalculator::calculate(rpn_tokens);
        } catch (const std::exception& e) {
            std::cout << "Invalid input!: RpnCalculator::calculate" << std::endl;
            continue;
        }

        std::string input_nums;
        for (const auto& c : input) {
            if (std::isdigit(c)) input_nums += c;
        }
        if (input_nums != num) {
            std::cout << "Invalid input!" << std::endl;
            continue;
        }

        if (result == TARGET) {
            std::cout << "Correct!" << std::endl;
            break;
        } else {
            std::cout << "Incorrect!" << std::endl;
        }
    }

    for (const auto& a : ans) std::cout << a << std::endl;
    return 0;
}