#pragma once

#include <limits>
#include <map>
#include <string>
#include <vector>

class FormulaConverter {
public:
    FormulaConverter() = delete;
    ~FormulaConverter() = delete;
    FormulaConverter& operator=(const FormulaConverter&) = delete;

private:
    static const std::map<std::string, int> OP_PRIO_FOR_INFIX;
    static constexpr int INF = std::numeric_limits<int>::max();

public:
    static std::vector<std::string> infix2rpn(const std::vector<std::string>& tokens);
    static std::vector<std::string> rpn2infix(const std::vector<std::string>& tokens);
};