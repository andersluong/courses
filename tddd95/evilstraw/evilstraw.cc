#include <iostream>

int solve(std::string &input) {
  int swaps = 0;
  int left = 0;
  int right = input.size() - 1;

  while (left <= right) {
    if (input[left] == input[right]) {
      // they match, so no swap needed
      left++;
      right--;
      continue;
    }

    // they don't match, so we need to find a match
    bool didSwap = false;
    int nextLeft = left + 1;
    int nextRight = right - 1;

    while (nextLeft <= right - 1) {
      // checking with the original
      if (input[nextLeft] == input[right]) {
        // we want to swap nextLeft position to the left until we reach left == right
        while (input[nextLeft] != input[left]) {
          swaps++;
          std::swap(input[nextLeft], input[nextLeft - 1]);
          nextLeft--;
        }
        didSwap = true;
        break;
      }
      if (input[left] == input[nextRight]) {
        // we want to swap nextRight position to the right until we reach left == right
        while (input[nextRight] != input[right]) {
          swaps++;
          std::swap(input[nextRight], input[nextRight + 1]);
          nextRight++;
        }
        didSwap = true;
        break;
      }
      nextLeft++;
      nextRight--;
    }
    if (!didSwap) {
      return -1;
    }
  }
  return swaps;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int numberOfTestCases;
  std::cin >> numberOfTestCases;

  for (int i = 0; i < numberOfTestCases; i++) {
    std::string input;
    std::cin >> input;

    int swaps = solve(input);
    if (swaps == -1) {
      std::cout << "Impossible" << "\n";
    } else {
      std::cout << swaps << "\n";
    }
  }
}
