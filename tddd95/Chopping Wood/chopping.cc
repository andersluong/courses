#include <iostream>
#include <vector>
#include <set>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int length;
  std::cin >> length;

  std::vector<int> degrees(length+1);
  std::vector<int> sequence(length);

  for (int i = 0; i < length; i++) {
    int index;
    std::cin >> index;
    degrees[index - 1] += 1;
    sequence[i] = index;
  }
  if (sequence[sequence.size()-1] != length + 1) {
    std::cout << "Error" << "\n";
    return 0;
  }

  std::set<int> cuts;
  for (unsigned i = 0; i < degrees.size(); i++) {
    if (degrees[i] == 0) {
      cuts.insert(i + 1);
    }
  }

  for (int i = 0; i < length; i++) {
    int checkIndex = sequence[i];
    std::cout << std::to_string(*cuts.begin()) << "\n";

    cuts.erase(*cuts.begin());
    degrees[checkIndex - 1] -= 1;
    if (degrees[checkIndex - 1] == 0) {
      cuts.insert(checkIndex);
    };
  }
}
