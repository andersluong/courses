#include <iostream>
#include <cmath>

int negativeLargestPower(int const x) {
  for (int b = -2; std::abs(b) <= (int)std::sqrt(std::abs(x)); b--) {
    for (int p = 3; p <= 32; p+=2) {
      double value = std::pow(b, p);
      if (value < x) {
        break;
      }
      if (value == (double)x) {
        return p;
      }
    }
  }
  return 1;
}

int postiveLargestPower(int const x) {
  for (int b = 2; std::abs(b) <= std::sqrt(x); b++) {
    for (int p = 2; p <= 32; p++) {
      double value = std::pow(b, p);
      if (value > x) {
        break;
      }
      if (value == (double)x) {
        return p;
      }
    }
  }
  return 1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int x;
  while (true) {
    std::cin >> x;
    if (x == 0) {
      break;
    }
    if (x > 0) {
      std::cout << postiveLargestPower(x) << "\n";
    } else {
      std::cout << negativeLargestPower(x) << "\n";
    }
  }
}
