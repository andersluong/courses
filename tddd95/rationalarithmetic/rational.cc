/**
* This program does simple arithmetic operations on rational numbers. The time complexity
* of the arithmetic operations is O(log(n)) where n is the maximum of the nominator and
* denominator. The compare operations are in O(1). The space complexity is O(1) since 
* we only store the nominator and denominator.
* 
* Author: Anders Luong (andlu434)
*/
#include <iostream>

class RationalNumber {
public:
  RationalNumber(long long const x, long long const y) : nominator{x}, denominator{y} {
    // reduce the fraction
    reduce();
  }
  
  // arithmetic operations
  RationalNumber operator+(RationalNumber const &other) const {
    long long newNominator = nominator * other.denominator + other.nominator * denominator;
    long long newDenominator = denominator * other.denominator;
    return RationalNumber(newNominator, newDenominator);
  }

  RationalNumber operator-(RationalNumber const &other) const {
    long long newNominator = nominator * other.denominator - other.nominator * denominator;
    long long newDenominator = denominator * other.denominator;
    return RationalNumber(newNominator, newDenominator);
  }

  RationalNumber operator*(RationalNumber const &other) const {
    long long newNominator = nominator * other.nominator;
    long long newDenominator = denominator * other.denominator;
    return RationalNumber(newNominator, newDenominator);
  }

  RationalNumber operator/(RationalNumber const &other) const {
    long long newNominator = nominator * other.denominator;
    long long newDenominator = denominator * other.nominator;
    return RationalNumber(newNominator, newDenominator);
  }

  // compare operations
  bool operator<(RationalNumber const &other) const {
    return nominator * other.denominator < other.nominator * denominator;
  }

  bool operator>(RationalNumber const &other) const {
    return nominator * other.denominator > other.nominator * denominator;
  }

  bool operator<=(RationalNumber const &other) const {
    return nominator * other.denominator <= other.nominator * denominator;
  }

  bool operator>=(RationalNumber const &other) const {
    return nominator * other.denominator >= other.nominator * denominator;
  }

  bool operator==(RationalNumber const &other) const {
    return nominator == other.nominator && denominator == other.denominator;
  }

  bool operator!=(RationalNumber const &other) const {
    return nominator != other.nominator || denominator != other.denominator;
  }

private:
  long long nominator;
  long long denominator;

  long long gcd(long long const x, long long const y) {
    if (y == 0) {
      return x;
    }
    return gcd(y, x % y);
  }

  void reduce() {
    long long gcd = this->gcd(nominator, denominator);
    nominator /= gcd;
    denominator /= gcd;
  }

  friend std::ostream &operator<<(std::ostream &os, RationalNumber const &rationalNumber) {
    if ((rationalNumber.denominator < 0 && rationalNumber.nominator > 0) || (rationalNumber.denominator < 0 && rationalNumber.nominator < 0)) {
      // 1. if the denominator is negative, we want to make the nominator negative instead
      // 2. if both nominator and denominator are negative, we want to make both positive instead
      os << -rationalNumber.nominator << " / " << -rationalNumber.denominator;
      return os;
    }
    os << rationalNumber.nominator << " / " << rationalNumber.denominator;
    return os;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  long long numberOfOperations;
  std::cin >> numberOfOperations;

  for (int i = 0; i < numberOfOperations; i++) {
    int x1, y1, x2, y2;
    char op;
    std::cin >> x1 >> y1 >> op >> x2 >> y2;
    RationalNumber r1{x1, y1};
    RationalNumber r2{x2, y2};

    switch (op) {
      case '+':
        std::cout << r1 + r2 << "\n";
        break;
      case '-':
        std::cout << r1 - r2 << "\n";
        break;
      case '*':
        std::cout << r1 * r2 << "\n";
        break;
      case '/':
        std::cout << r1 / r2 << "\n";
        break;
    }
  }
}
