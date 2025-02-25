#include "FormulaConverter/FormulaConverter.hpp"
#include "Fraction/Fraction.hpp"
#include "RpnCalculator/RpnCalculator.hpp"
#include "Tokenizer/Tokenizer.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main() {
    const std::array<std::string, 4> OPS = {"+", "-", "*", "/"};
    constexpr int TARGET = 10;
    constexpr int SIZE = 4;

    std::set<std::string> has_visited;

    for (int i = 0; i < std::pow(10, SIZE); i++) {

        std::string input = std::to_string(i);
        while (input.size() < 4) input = "0" + input;

        std::sort(input.begin(), input.end());
        if (has_visited.find(input) != has_visited.end()) continue;

        has_visited.insert(input);

        std::cout << input << std::endl;

        std::vector<std::string> nums;
        for (const auto& c : input) nums.push_back(std::string(1, c));

        const std::size_t token_size = nums.size() * 2 - 1;

        auto is_creatable = [](const std::vector<std::string>& tokens, const int& target) {
            std::vector<std::string> infix;
            try {
                infix = FormulaConverter::rpn2infix(tokens);
            } catch (const std::runtime_error& e) {
                return false;
            }

            Fraction result;
            try {
                result = RpnCalculator::calculate(tokens);
            } catch (const std::runtime_error& e) {
                return false;
            }
            if (result != target) return false;

            const auto infix_formula = Tokenizer::join(infix);
            std::cout << infix_formula << " = " << result << std::endl;
            return true;
        };

        auto dfs = [is_creatable, OPS, TARGET, token_size, nums](auto&& f, const int& idx, const std::vector<std::string>& tokens) -> void {
            if (tokens.size() < token_size) {
                for (std::size_t i = idx; i < OPS.size(); i++) {
                    auto next = tokens;
                    next.push_back(OPS[i]);
                    f(f, i, next);
                }
                return;
            }

            auto current = tokens;
            std::sort(current.begin(), current.end());
            do {
                std::vector<std::string> curr_nums;
                for (const auto& s : current) {
                    if (std::all_of(s.begin(), s.end(), [](const char& c) { return std::isdigit(c) || c == '.'; })) {
                        curr_nums.push_back(s);
                    }
                }
                if (curr_nums == nums) is_creatable(current, TARGET);
            } while (std::next_permutation(current.begin(), current.end()));

            return;
        };

        dfs(dfs, 0, nums);

        std::cout << std::endl;
    }

    return 0;
}