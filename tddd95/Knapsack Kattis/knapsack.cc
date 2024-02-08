/**
* This is the classical knapsack problem. This is solved using dynamic programming with a 2D array where the columns are 
* the weight and the rows are the items. The valueMap[i][j] represents the maximum value that can be obtained with the
* first i items. 
* Source of inspiration: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
*
* Author: Anders Luong
*/
#include <iostream>
#include <string>
#include <vector>

struct Object {
  int value;
  int weight;
  int index;
};

// Represents a knapsack.
// The rows represent the items used and the columns represent the weight.
using worldMapType = std::vector<std::vector<Object>>;

static const int UNDEFINED = -1;

void solve(worldMapType &valueMap, std::vector<Object> const& objects, int const totalCapacity) {
  // if weight is 0, then no items can be picked
  for (unsigned i = 0; i < objects.size(); i++) {
    valueMap[i][0].value = 0;
  }
  // 0 items picked have 0 weight 
  for (int i = 0; i < totalCapacity; i++) {
    valueMap[0][i].value = 0;
  }
 
  for (unsigned i = 1; i <= objects.size(); i++) {
    for (int j = 1; j <= totalCapacity; j++) {
      Object prevObject = objects[i - 1];
      if (prevObject.weight <= j) {
        int excludeValue = valueMap[i-1][j].value;
        int includeValue = prevObject.value + valueMap[i - 1][j - prevObject.weight].value;
        if (excludeValue > includeValue) {
          // exclude item
          valueMap[i][j] = { excludeValue, valueMap[i - 1][j].weight, valueMap[i - 1][j].index };
        } else {
          // include item
          valueMap[i][j] = { includeValue, prevObject.weight, prevObject.index };
        }
      } else {
        // exclude item
        valueMap[i][j] = valueMap[i - 1][j];
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int capacity;
  while (std::cin >> capacity) {
    int numberOfObjects;
    std::cin >> numberOfObjects;
    std::vector<Object> objects;
    for (int i = 0; i < numberOfObjects; i++) {
      int value, weight;
      std::cin >> value >> weight;
      objects.push_back(Object{value, weight, i});
    }

    // init
    std::vector<Object> initValues(capacity + 1, {UNDEFINED, UNDEFINED, UNDEFINED});
    worldMapType valueMap(numberOfObjects + 1, initValues);

    // solve
    solve(valueMap, objects, capacity);
    int count = 0;
    std::string indexes = "";
    for (int i = numberOfObjects; i > 0; i--) {
      if (capacity == 0) {
        break;
      }
      Object object = valueMap[i][capacity];
      Object prevObject = valueMap[i - 1][capacity];
      if (object.value != prevObject.value) {
        count++;
        if (count == 1) {
          indexes = std::to_string(object.index);
        } else {
          indexes = std::to_string(object.index) + " " + indexes;
        }
        capacity -= object.weight;
      }
    }
    std::cout << count << "\n";
    std::cout << indexes << "\n";
  }

}
