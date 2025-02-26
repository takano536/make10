#include "FormulaConverter/FormulaConverter.hpp"
#include "Fraction/Fraction.hpp"
#include "RpnCalculator/RpnCalculator.hpp"
#include "Tokenizer/Tokenizer.hpp"

#include <algorithm>
#include <array>
#include <iostream>
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

    std::vector<std::string> nums;
    myfuncs::generate_nums({0, 9}, SIZE, "", nums);

    std::vector<std::string> ops;
    myfuncs::generate_nums({0, 3}, SIZE - 1, "", ops);

    std::array<std::vector<std::string>, static_cast<std::size_t>(myfuncs::powi(10, SIZE))> results;

    for (const auto& num : nums) {
        for (const auto& op : ops) {

            std::vector<std::string> rpn_tokens;
            for (const auto& c : op) rpn_tokens.push_back(OPS[c - '0']);
            for (const auto& c : num) rpn_tokens.push_back(std::string(1, c));

            do {

                std::vector<std::string> infix_tokens;
                try {
                    infix_tokens = FormulaConverter::rpn2infix(rpn_tokens);
                } catch (const std::exception& e) {
                    continue;
                }

                Fraction result = 0;
                try {
                    result = RpnCalculator::calculate(rpn_tokens);
                } catch (const std::exception& e) {
                    continue;
                }

                if (result != TARGET) continue;

                const auto infix_formula = Tokenizer::join(infix_tokens);

                std::string curr_num;
                std::copy_if(infix_formula.begin(), infix_formula.end(), std::back_inserter(curr_num), [](const char& c) { return std::isdigit(c); });

                results[std::stoi(curr_num)].push_back(infix_formula);

            } while (std::next_permutation(rpn_tokens.begin(), rpn_tokens.end()));
        }
    }

    for (int i = 0; i < myfuncs::powi(10, SIZE); i++) {
        if (results[i].empty()) continue;

        std::cout << i << ": " << results[i].size() << '\n';
        for (const auto& res : results[i]) std::cout << res << '\n';
        std::cout << std::endl;
    }

    return 0;
}