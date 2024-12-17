#include "Fraction.hpp"

#include <numeric>
#include <stdexcept>

Fraction::Fraction() : numer(0), denom(1) {}
Fraction::Fraction(int numer) : numer(numer), denom(1) {}

Fraction::Fraction(int numer, int denom) : numer(numer), denom(denom) {
    if (denom == 0) throw std::invalid_argument("Denominator cannot be zero.");
    reduce();
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

    auto gcd = std::gcd(this->numer, this->denom);
}