#include <iostream>

int getSum(unsigned long long number, int S) {
  int sum = 0;
  while (number > 0) {
    sum += number % 10;
    number /= 10;

    if (sum > S) {
      return -1;
    }
  }
  return sum;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  unsigned long long A, B;
  int S;
  std::cin >> A >> B >> S;

  int count = 0;
  int leastSum = -1;

  while (A <= B) {
    int sum = getSum(A, S);
    int lastDigit = A % 10;
    std::cout << A << " " << sum << " " << lastDigit << "\n";
    if (sum <= S && S <= sum + lastDigit + 9) {
      count++;

      if (leastSum == -1) {
        leastSum = A + S - lastDigit;
      }
    }
    A += 10 - lastDigit;
  }
  std::cout << count << "\n";
  std::cout << leastSum << "\n";
}
