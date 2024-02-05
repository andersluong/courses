#include <iostream>
#include <bitset> 
#include <vector>

std::string orderToVoting(int const n) {
  switch (n) {
    case 1:
      return "NNN";
    case 2:
      return "NNY";
    case 3:
      return "NYN";
    case 4:
      return "NYY";
    case 5:
      return "YNN";
    case 6:
      return "YNY";
    case 7:
      return "YYN";
    case 8:
      return "YYY";
    default:
      return "---";
  }
}

std::string orderToBinary(int const n) {
  switch (n) {
    case 1:
      return "000";
    case 2:
      return "001";
    case 3:
      return "010";
    case 4:
      return "011";
    case 5:
      return "100";
    case 6:
      return "101";
    case 7:
      return "110";
    case 8:
      return "111";
    default:
      return "---";
  }
}

int main() {
  int rounds;
  std::cin >> rounds;
  
  for (int round = 0; round < rounds; round++) {
    int numberOfPriests;
    std::cin >> numberOfPriests;
    std::string currentOrder = "000";
    for (int priest = 0; priest < numberOfPriests; priest++) {
      for (int i = 0; i < 8; i++) {
        int order;
        std::cin >> order;
        for (auto selection : orderToBinary(order)) {
          
        }
      }
    }
  }
}
