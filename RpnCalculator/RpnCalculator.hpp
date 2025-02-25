#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "../Fraction/Fraction.hpp"

class RpnCalculator final {
public:
    RpnCalculator() = delete;
    ~RpnCalculator() = delete;
    RpnCalculator& operator=(const RpnCalculator&) = delete;

private:
    static const std::map<std::string, std::function<Fraction(const Fraction&, const Fraction&)>> OPERATORS;

public:
    static Fraction calculate(const std::vector<std::string>& formula);

private:
    static Fraction operate(const Fraction& lhs, const Fraction& rhs, const std::string op);
    static bool is_operater(const std::string& str);
};
