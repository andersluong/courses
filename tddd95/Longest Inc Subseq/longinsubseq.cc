#include <iostream>
#include <vector>

void solve(int const lengthOfSequence, std::vector<int> const &sequence) {
  std::vector<int> bucket;
  std::vector<int> indexes;
  for (int i = 0; i < lengthOfSequence; i++) {
    // std::cout << "back: " << bucket.back() << " sequence[i]: " << sequence[i] << "\n";
    if (bucket.empty() || bucket.back() < sequence[i]) {
      bucket.push_back(sequence[i]);
      indexes.push_back(i);
    } else {
      auto it = std::lower_bound(bucket.begin(), bucket.end(), sequence[i]);
      int newIndex = std::distance(bucket.begin(), it);
      *it = sequence[i];
      // std::copy(bucket.begin(), bucket.end(), std::ostream_iterator<int>(std::cout, " "));
      // std::cout << "\n";
    }
  }
  std::cout << bucket.size() << "\n";
  std::copy(indexes.begin(), indexes.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}

int main() {
  int lengthOfSequence;
  while (std::cin >> lengthOfSequence) {
    std::vector<int> sequence(lengthOfSequence);
    for (int i = 0; i < lengthOfSequence; ++i) {
      int value;
      std::cin >> value;
      sequence[i] = value;
    }
    solve(lengthOfSequence, sequence);
  }
}
