// Source of inspiration: https://stackoverflow.com/questions/11891984/count-the-number-of-occurrences-of-0s-in-integers-from-1-to-n

#include <iostream>

int countZeros(unsigned const n) {
  unsigned result = 0;
  unsigned i = 1;

  while (true) {
    // For 1234
    // ???0
    // b = 1234
    // c = 0
    // a = 123
    // b = 4

    // ??0?
    // b = 123
    // c = 4
    // a = 12
    // b = 3

    // ?0??
    // b = 12
    // c = 3
    // a = 1
    // b = 2

    // 0???
    // b = 1
    // c = 2
    // a = 0
    // b = 1
    unsigned b = n / i;
    unsigned c = n % i;
    unsigned a = b / 10;
    b = b % 10;

    if (a == 0) {
      return result;
    }

    // special case for b == 0
    if (b == 0) {
      result += (a - 1) * i + c + 1;
    } else {
      result += a * i;
    }

    i *= 10;
  }
}

int main() {
  long long m;
  long long n;
  while (true) {
    std::cin >> m >> n;
    if (m == -1 && n == -1) {
      break;
    }
    long long zerosInM = m == 0 ? -1 : countZeros(m - 1);
    unsigned zerosInN = n == 0 ? 1 : countZeros(n);
    // std::cout << "zerosInM: " << zerosInM << "\n";
    // std::cout << "zerosInN: " << zerosInN << "\n";
    std::cout << zerosInN - zerosInM << "\n";
  }
}
