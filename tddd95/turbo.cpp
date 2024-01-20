#include <array>
#include <iostream>
#include <array>

int main() {
  std::array<int, 100001> indexes;
  std::string input;
  std::cin >> input;
  int elements = std::stoi(input);
  // elements will have same index as the assignment description, that is,
  // starting from 1
  for (int i = 1; i <= elements; i++) {
    std::cin >> input;
    int index = std::stoi(input);
    indexes[index] = i;
  }
  // for (int i = 0; i <= elements; i++) std::cout << indexes.at(i) << " ";
  int elementsToCheck = elements / 2;
  if (elements % 2 != 0) elementsToCheck++;
  for (int i = 1; i <= elementsToCheck; i++) {
    int elementFromLeft = indexes[i];
    int elementFromRight = indexes[elements - i + 1];
    int swapsFromLeft = elementFromLeft - i;
    int swapsFromRight = elements - i + 1 - elementFromRight;
    std::cout << "swaps left: " << swapsFromLeft << ". checking: " << i << std::endl;
    std::cout << "swaps right: " << swapsFromRight << ". checking: " << elements - i + 1 << std::endl;
  }
}
