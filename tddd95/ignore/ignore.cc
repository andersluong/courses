#include <iostream>

void solve(int const K) {
  /*
   all valid entries:
    - 0 -> 0
    - 1 -> 1
    - 2 -> 2
    - 3 -> 5
    - 4 -> 9
    - 5 -> 8
    - 6 -> 6

    for every 7 numbers, the pattern repeats
  */
  // create the number represented in valid
  std::string valid = "";
  int left = K;
  while (left > 0) {
    int digit = left % 7;
    switch (digit) {
      case 3:
        valid += "5";
        break;
      case 4:
        valid += "9";
        break;
      case 5:
        valid += "8";
        break;
      default:
        valid += std::to_string(digit);
        break;
    }
    left -= digit;
    left /= 7;
  }
  std::cout << valid << "\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int K;
  while (std::cin >> K) {
    solve(K);
  }
} 
