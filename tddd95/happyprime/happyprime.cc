#include <iostream>
#include <set>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  std::vector<bool> isPrime(10001, true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i * i <= 10000; i++) {
    if (isPrime[i]) {
      for (int j = i * i; j <= 10000; j += i) {
        isPrime[j] = false;
      }
    }
  }

  int numberOfDataSets;
  std::cin >> numberOfDataSets;

  for (int i = 0; i < numberOfDataSets; i++) {
    int dataSetNumber, number;
    std::cin >> dataSetNumber >> number;

    std::cout << dataSetNumber << " " << number << " ";

    if (!isPrime[number]) {
      std::cout << "NO\n";
      continue;
    }

    bool isHappyPrime = false;
    // check visited for a number so we don't potentially get stuck in a loop
    std::set<int> visited;
    while (visited.find(number) == visited.end()) {
      visited.insert(number);
      int newNumber = 0;
      // get one digit at a time
      while (number != 0) {
        int lastDigit = number % 10;
        newNumber += lastDigit * lastDigit;
        number /= 10;
      } 
      if (newNumber == 1) {
        isHappyPrime = true;
        break;
      }
      number = newNumber;
    }
    if (isHappyPrime) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
  
}
