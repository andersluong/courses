#include <iostream>
#include <vector>

int main() {
  std::string lastAnimal;
  std::cin >> lastAnimal;
  int n;
  std::cin >> n;

  std::vector<std::string> animals(n);
  for (int i = 0; i < n; i++) {
    std::cin >> animals[i];
  }

  char lastChar = lastAnimal[lastAnimal.size() - 1];
  std::vector<std::string> possibleAnimals;
  for (int i = 0; i < n; i++) {
    if (animals[i][0] == lastChar) {
      possibleAnimals.push_back(animals[i]);
    }
  }

  // handle case where there are no possible animals
  if (possibleAnimals.size() == 0) {
    std::cout << "?\n";
    return 0;
  }

  for (unsigned i = 0; i < possibleAnimals.size(); i++) {
    char lastChar = possibleAnimals[i][possibleAnimals[i].size() - 1];
    bool found = false;
    for (int j = 0; j < n; j++) {
      if (animals[j][0] == lastChar && animals[j] != possibleAnimals[i]) {
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << possibleAnimals[i] << "!\n";
      return 0;
    }
  }
  std::cout << possibleAnimals[0] << "\n";
}
