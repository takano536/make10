#pragma once

#include <array>
#include <string>
#include <vector>

class Tokenizer {
public:
    Tokenizer() = delete;
    ~Tokenizer() = delete;
    Tokenizer& operator=(const Tokenizer&) = delete;

private:
    static constexpr std::array OPERATORS = {
        static_cast<std::string_view>("+"),
        static_cast<std::string_view>("-"),
        static_cast<std::string_view>("*"),
        static_cast<std::string_view>("/"),
    };

public:
    static std::vector<std::string> tokenize(const std::string& formula);
    static std::string join(const std::vector<std::string>& tokens);

private:
    static bool is_operator(const char& letter);
    static std::string read_number(const std::string& formula, std::size_t& pos);
    static std::string read_operator(const std::string& formula, std::size_t& pos);
};