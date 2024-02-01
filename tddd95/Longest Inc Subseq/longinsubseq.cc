#include <iostream>
#include <vector>

bool solveTestCase() {
  int lengthOfSequence;
  if (!(std::cin >> lengthOfSequence)) {
    return false;
  }
  std::vector<int> sequence(lengthOfSequence);
  for (int i = 0; i < lengthOfSequence; ++i) {
    int value;
    std::cin >> value;
    sequence[i] = value;
  }
  // std::vector<int> sortedSequence(sequence);
  // std::sort(sortedSequence.begin(), sortedSequence.end());
  std::vector<int> indexes;
  std::vector<int> bucket{sequence[0]};
  for (int i = 1; i < lengthOfSequence; i++) {
    std::cout << "back: " << bucket.back() << " sequence[i]: " << sequence[i] << "\n";
    if (bucket.back() < sequence[i]) {
      bucket.push_back(sequence[i]);
      indexes.push_back(i);
    } else {
      auto it = std::lower_bound(bucket.begin(), bucket.end(), sequence[i]);
      *it = sequence[i];
      std::copy(bucket.begin(), bucket.end(), std::ostream_iterator<int>(std::cout, " "));
      std::cout << "\n";
    }
  }
  std::cout << indexes.size() << "\n";
  std::copy(indexes.begin(), indexes.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  std::copy(bucket.begin(), bucket.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  return true;
}

int main() {
  while (solveTestCase()) {}
}
