#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

// Represents a knapsack.
// The rows represent the items used and the columns represent the weight.
template <typename T>
using worldMapType = std::array<std::array<T, 2001>, 2001>;

static const int UNDEFINED = -1;

struct Object {
  int value;
  int weight;
};

void solve(worldMapType<int> &valueMap, std::vector<Object> const& objects, int const totalCapacity) {
  // 0 items picked have 0 weight 
  for (int i = 0; i < totalCapacity; i++) {
    valueMap[0][i] = 0;
  }
  // if weight is 0, then no items can be picked
  for (int i = 0; i < objects.size(); i++) {
    valueMap[i][0] = 0;
  }
 
  for (int i = 1; i <= objects.size(); i++) {
    for (int j = 1; j <= objects[i].weight; j++) {
      Object prevObject = objects[i - 1];
      if (prevObject.weight <= j) {
        valueMap[i][j] = std::max(valueMap[i-1][j], prevObject.value + valueMap[i-1][j - prevObject.weight]);
      } else {
        valueMap[i][j] = valueMap[i - 1][j];
      }
    }
  }

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int numberOfTests;
  std::cin >> numberOfTests;
  for (int tc = 0; tc < numberOfTests; tc++) {
    int capacity, numberOfObjects;
    std::cin >> capacity >> numberOfObjects;
    std::vector<Object> objects;
    for (int i = 0; i < numberOfObjects; i++) {
      int value, weight;
      std::cin >> value >> weight;
      objects.push_back({value, weight});
    }

    // init
    worldMapType<int> valueMap;
    std::array<int, 2001> initValues;
    std::fill(initValues.begin(), initValues.end(), UNDEFINED);
    std::fill_n(valueMap.begin(), numberOfObjects, initValues);

    // solve
    solve(valueMap, objects, capacity);
    std::cout << valueMap[numberOfObjects][capacity] << "\n";
    // for (int row = 0; row < numberOfInstructions; row++) {
    //   std::cout << row << ": [ ";
    //   for (int col = 0; col <= 20; col++) {
    //     std::cout << "(" << col << ": " << worldMap[row][col] << ") ";
    //   }
    //   std::cout << "]\n";
    // }
    // for (int row = 0; row < numberOfInstructions; row++) {
    //   std::cout << row << ": [ ";
    //   for (int col = 0; col <= 20; col++) {
    //     std::cout << "(" << col << ": " << directionMap[row][col] << ") ";
    //   }
    //   std::cout << "]\n";
    // }
  }

}
