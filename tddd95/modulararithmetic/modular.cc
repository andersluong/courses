/**
* Modular Arithmetic
* Addition modulo is using the default % operator. Subtraction modulo needs to handle negative numbers.
* Multiplication modulo is using the default % operator but divided into two steps to avoid overflow.
* Division modulo is using the extended euclidean algorithm to run in O(logn) for finding the gcd == 1 for
* the inverse of y. If the gcd is not 1, then the inverse does not exist.
*
* Sources of inspiration:
* https://www.geeksforgeeks.org/modular-division/
* https://cp-algorithms.com/algebra/extended-euclid-algorithm.html 
*
* Author: Anders Luong (andlu434)
*/
#include <iostream>

long long additionModulo(long long const& x, long long const& y, long long const& mod) {
  return (x + y) % mod;
}

long long subtractionModulo(long long const& x, long long const& y, long long const& mod) {
  // need to handle negative numbers
  long long result = x - y;
  long long resultMod = result % mod;
  return (resultMod + mod) % mod;
}

long long multiplicationModulo(long long const& x, long long const& y, long long const& mod) {
  long long xMod = x % mod;
  long long yMod = y % mod;
  return (xMod * yMod) % mod;
}

/**
* Extended Euclidean Algorithm: ax + by = gcd(a, b)
* This runs in O(logn) time
*/
long long gcd(long long const& a, long long const& b, long long& x, long long& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  long long x1, y1;
  long long d = gcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

// Get the modular inverse of a number
long long modInverse(long long const& a, long long const& mod) {
  // using extended euclidean algorithm
  long long x, y;
  long long gcdResult = gcd(a, mod, x, y);

  // we need to check if the gcd is 1
  if (gcdResult != 1) {
    return -1;
  }

  // x can be negative
  return subtractionModulo(x, 0, mod);
}

long long divisionModulo(long long const& x, long long const& y, long long const& mod) {
  // xy^-1 mod m
  long long yInverse = modInverse(y, mod);
  if (yInverse == -1) {
    return -1;
  }
  return multiplicationModulo(x, yInverse, mod) % mod;
}

int main() {
  while (true) {
    long long mod;
    int numberOfOperations;
    std::cin >> mod >> numberOfOperations;

    if (mod == 0 && numberOfOperations == 0) {
      break;
    }

    for (int i = 0; i < numberOfOperations; i++) {
      long long x, y;
      char op;
      std::cin >> x >> op >> y;
      
      switch (op) {
        case '+':
          std::cout << additionModulo(x, y, mod) << std::endl;
          break;
        case '-':
          std::cout << subtractionModulo(x, y, mod) << std::endl;
          break;
        case '*':
          std::cout << multiplicationModulo(x, y, mod) << std::endl;
          break;
        case '/':
          std::cout << divisionModulo(x, y, mod) << std::endl;
          break;
      }
    }
  }
}
