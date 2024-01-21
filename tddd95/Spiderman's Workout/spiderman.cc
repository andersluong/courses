#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

template <typename T>
using worldMapType = std::array<std::array<T, 40>, 1000>;

enum {
  UNDEFINED = -1,
  IMPOSSIBLE = -2
};

void solve(worldMapType<int> &worldMap, worldMapType<std::string> &directionMap, std::vector<int> const& instructions) {
  // first move, spiderman can only go up
  worldMap[0][instructions[0]] = instructions[0];
  directionMap[0][instructions[0]] = "U";

  for (int index = 1; index < instructions.size(); index++) {
    auto instruction = instructions[index];
    auto prevInstructions = worldMap[index - 1];
    for (int prevIndex = 0; prevIndex < prevInstructions.size(); prevIndex++) {
      int prevInstruction = prevInstructions[prevIndex];
      if (prevInstruction == UNDEFINED) {
        continue;
      }
      int moveDown = prevInstruction - instruction;
      int moveUp = prevInstruction + instruction;
      if (moveDown > 0) {
        worldMap[index][moveDown] = std::max(moveDown, prevInstruction);
        directionMap[index][moveDown] = "D";
      }
      worldMap[index][moveUp] = std::max(moveUp, prevInstruction);
      directionMap[index][moveUp] = "U";
    }
    
  }
  // if (currentHeight < 0) {
  //   return IMPOSSIBLE;
  // }
  // if (currentHeight == heights.size() - 1) {
  //   return 0;
  // }
  // if (worldMap[index][currentHeight] != UNDEFINED) {
  //   return worldMap[index][currentHeight];
  // }
  // int instructionHeight = heights[index];
  // int moveDown = solve(worldMap, directionMap, heights, currentHeight - instructionHeight, index + 1);
  // int moveUp = solve(worldMap, directionMap, heights, currentHeight + instructionHeight, index + 1);
  // std::cout << "index: " << index << " currentHeight: " << currentHeight << " moveDown: " << moveDown << " moveUp: " << moveUp << std::endl;
  // if (moveDown < moveUp) {
  //   int choice = std::max(currentHeight, moveDown);
  //   worldMap[index][currentHeight] = choice;
  //   directionMap[index][currentHeight] = "D";
  //   return choice;
  // } else {
  //   int choice = std::max(currentHeight, moveUp);
  //   worldMap[index][currentHeight] = choice;
  //   directionMap[index][currentHeight] = "U";
  //   return choice;
  // }

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int numberOfTests;
  std::cin >> numberOfTests;
  for (int tc = 0; tc < numberOfTests; tc++) {
    int numberOfInstructions;
    std::cin >> numberOfInstructions;
    std::vector<int> heights;
    for (int i = 0; i < numberOfInstructions; i++) {
      int height;
      std::cin >> height;
      heights.push_back(height);
    }

    // init
    worldMapType<int> worldMap;
    std::array<int, 40> instructions;
    std::fill(instructions.begin(), instructions.end(), UNDEFINED);
    std::fill_n(worldMap.begin(), numberOfInstructions, instructions);
    // used for knowing if we should go up or down
    worldMapType<std::string> directionMap;

    // solve
    solve(worldMap, directionMap, heights);
    for (int row = 0; row < numberOfInstructions; row++) {
      std::cout << "[ ";
      for (int col = 0; col < 20; col++) {
        std::cout << worldMap[row][col] << " ";
      }
      std::cout << "]\n";
    }

    // find smallest result
    int inf = std::numeric_limits<int>::max();
    int smallestIndex = inf;
    int shortestDistance = inf;
    auto lastInstruction = worldMap[numberOfInstructions - 1];
    for (int index = 0; index < lastInstruction.size(); index++) {
      if (lastInstruction[index] != UNDEFINED) {
        if (lastInstruction[index] < shortestDistance) {
          std::cout << "lastInstruction[" << index << "]: " << lastInstruction[index] << std::endl;
          shortestDistance = lastInstruction[index];
          smallestIndex = index;
        }
      }
    }
    std::cout << "smallestIndex: " << smallestIndex << std::endl;
    std::string result;

    // backtrack
    for (int index = numberOfInstructions - 1; index >= 0; index--) {
      result += directionMap[index][smallestIndex];
      if (directionMap[index][smallestIndex] == "D") {
        smallestIndex -= heights[index];
      } else {
        smallestIndex += heights[index];
      }
    }
    std::reverse(result.begin(), result.end());
    std::cout << result << "\n";
    // for (int instruction = 0; instruction < numberOfInstructions; instruction++) {
    //   result += directionMap[instruction][moved];
    //   if (directionMap[instruction][moved] == "D") {
    //     height -= heights[instruction];
    //   } else {
    //     height += heights[instruction];
    //   }
    // }
    // std::cout << result << "\n";
  }

}
