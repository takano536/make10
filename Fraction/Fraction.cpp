#include "Fraction.hpp"

#include <limits>
#include <numeric>
#include <stdexcept>
#include <string>
#include <utility>

Fraction::Fraction() : numer(0), denom(1) {}
Fraction::Fraction(int numer) : numer(numer), denom(1) {}

Fraction::Fraction(int numer, int denom) : numer(numer), denom(denom) {
    if (denom == 0) throw std::invalid_argument("Denominator cannot be zero.");
    reduce();
}

Fraction operator+(const Fraction& frac) { return frac; }
Fraction operator-(const Fraction& frac) { return Fraction(-frac.numer, frac.denom); }

Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.numer * rhs.denom + rhs.numer * lhs.denom, lhs.denom * rhs.denom);
}
Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.numer * rhs.denom - rhs.numer * lhs.denom, lhs.denom * rhs.denom);
}
Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    std::pair<int, int> gcd = {std::gcd(lhs.numer, rhs.denom), std::gcd(lhs.denom, rhs.numer)};
    long long numer = static_cast<long long>(lhs.numer / gcd.first) * (rhs.numer / gcd.second);
    long long denom = static_cast<long long>(lhs.denom / gcd.second) * (rhs.denom / gcd.first);

    bool is_overflow = false;
    is_overflow |= numer > std::numeric_limits<int>::max();
    is_overflow |= numer < std::numeric_limits<int>::min();
    is_overflow |= denom > std::numeric_limits<int>::max();
    is_overflow |= denom < std::numeric_limits<int>::min();
    if (is_overflow) throw std::overflow_error("Multiplication overflow.");

    return Fraction(numer, denom);
}
Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    std::pair<int, int> gcd = {std::gcd(lhs.numer, rhs.numer), std::gcd(lhs.denom, rhs.denom)};
    long long numer = static_cast<long long>(lhs.numer / gcd.first) * (rhs.denom / gcd.second);
    long long denom = static_cast<long long>(lhs.denom / gcd.second) * (rhs.numer / gcd.first);

    bool is_overflow = false;
    is_overflow |= numer > std::numeric_limits<int>::max();
    is_overflow |= numer < std::numeric_limits<int>::min();
    is_overflow |= denom > std::numeric_limits<int>::max();
    is_overflow |= denom < std::numeric_limits<int>::min();
    if (is_overflow) throw std::overflow_error("Division overflow.");

    return Fraction(numer, denom);
}

bool Fraction::operator==(const Fraction& rhs) const { return this->numer == rhs.numer && this->denom == rhs.denom; }
bool Fraction::operator!=(const Fraction& rhs) const { return !(*this == rhs); }

bool Fraction::operator<(const Fraction& rhs) const {
    long long lhs_val = static_cast<long long>(this->numer) * rhs.denom;
    long long rhs_val = static_cast<long long>(rhs.numer) * this->denom;
    return lhs_val < rhs_val;
}
bool Fraction::operator<=(const Fraction& rhs) const { return *this < rhs || *this == rhs; }
bool Fraction::operator>(const Fraction& rhs) const { return !(*this <= rhs); }
bool Fraction::operator>=(const Fraction& rhs) const { return !(*this < rhs); }

Fraction& Fraction::operator+=(const Fraction& rhs) {
    *this = *this + rhs;
    return *this;
}
Fraction& Fraction::operator-=(const Fraction& rhs) {
    *this = *this - rhs;
    return *this;
}
Fraction& Fraction::operator*=(const Fraction& rhs) {
    *this = *this * rhs;
    return *this;
}
Fraction& Fraction::operator/=(const Fraction& rhs) {
    *this = *this / rhs;
    return *this;
}

Fraction& Fraction::operator++() {
    *this += Fraction(1);
    return *this;
}
Fraction& Fraction::operator--() {
    *this -= Fraction(1);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
    os << frac.numer;
    if (frac.denom != 1) os << '/' << frac.denom;
    return os;
}

/*!
    @brief 約分する
    @return Fraction& 自身への参照
*/
void Fraction::reduce() {
    // 符号を最適化
    if (this->numer < 0 && this->denom < 0) {
        // 分母も分子も負の場合は正にする
        this->numer = -this->numer;
        this->denom = -this->denom;
    }
    if (this->numer > 0 && this->denom < 0) {
        // 分子が正で分母が負の場合はマイナスを分子に持ってくる
        this->numer = -this->numer;
        this->denom = -this->denom;
    }

    // 約分
    auto gcd = std::gcd(this->numer, this->denom);
    this->numer /= gcd;
    this->denom /= gcd;
}
