#pragma once

#include <iostream>

class Fraction {
  private:
    int numer;
    int denom;

  public:
    Fraction();
    Fraction(int numer);
    Fraction(int numer, int denom);

    friend Fraction operator+(const Fraction& frac);
    friend Fraction operator-(const Fraction& frac);

    friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator*(const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator/(const Fraction& lhs, const Fraction& rhs);

    bool operator==(const int rhs) const;
    bool operator!=(const int rhs) const;
    bool operator<(const int rhs) const;
    bool operator<=(const int rhs) const;
    bool operator>(const int rhs) const;
    bool operator>=(const int rhs) const;

    bool operator==(const Fraction& rhs) const;
    bool operator!=(const Fraction& rhs) const;
    bool operator<(const Fraction& rhs) const;
    bool operator<=(const Fraction& rhs) const;
    bool operator>(const Fraction& rhs) const;
    bool operator>=(const Fraction& rhs) const;

    Fraction& operator+=(const Fraction& rhs);
    Fraction& operator-=(const Fraction& rhs);
    Fraction& operator*=(const Fraction& rhs);
    Fraction& operator/=(const Fraction& rhs);

    Fraction& operator++();
    Fraction& operator--();

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);

  private:
    void reduce();
};