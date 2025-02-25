#pragma once

#include <map>
#include <string>
#include <vector>

class FormulaConverter {
public:
    FormulaConverter() = delete;
    ~FormulaConverter() = delete;
    FormulaConverter& operator=(const FormulaConverter&) = delete;

private:
    static const std::map<std::string, int> OP_PRECEDENCES_FOR_INFIX;

public:
    static std::vector<std::string> infix2rpn(const std::vector<std::string>& tokens);
};