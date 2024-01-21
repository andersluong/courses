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

  for (unsigned index = 1; index < instructions.size(); index++) {
    auto instruction = instructions[index];
    auto prevInstructions = worldMap[index - 1];
    for (unsigned prevIndex = 0; prevIndex < prevInstructions.size(); prevIndex++) {
      int prevInstruction = prevInstructions[prevIndex];
      if (prevInstruction == UNDEFINED) {
        continue;
      }
      int moveDown = prevIndex - instruction;
      int moveUp = prevIndex + instruction;
      if (moveDown >= 0) {
        if (worldMap[index][moveDown] > moveDown) {
          worldMap[index][moveDown] = std::min((int)prevIndex, worldMap[index][moveDown]);
        } else {
          worldMap[index][moveDown] = std::max(moveDown, prevInstruction);
          directionMap[index][moveDown] = "D";
        }
      }
      if (worldMap[index][moveUp] > moveUp) {
        worldMap[index][moveUp] = std::min((int)prevIndex, worldMap[index][moveUp]);
      } else {
        worldMap[index][moveUp] = std::max(moveUp, prevInstruction);
        directionMap[index][moveUp] = "U";
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
    // for (int row = 0; row < numberOfInstructions; row++) {
    //   std::cout << row << ": [ ";
    //   for (int col = 0; col <= 20; col++) {
    //     std::cout << col << ": " << worldMap[row][col] << " ";
    //   }
    //   std::cout << "]\n";
    // }
    // for (int row = 0; row < numberOfInstructions; row++) {
    //   std::cout << row << ": [ ";
    //   for (int col = 0; col <= 20; col++) {
    //     std::cout << col << ": " << directionMap[row][col] << " ";
    //   }
    //   std::cout << "]\n";
    // }

    auto lastInstruction = worldMap[numberOfInstructions - 1];
    if (lastInstruction[0] == UNDEFINED) {
      std::cout << "IMPOSSIBLE\n";
      continue;
    }

    std::string path;
    int backTrackIndex = 0;

    // backtrack
    for (int index = numberOfInstructions - 1; index >= 0; index--) {
      path = directionMap[index][backTrackIndex] + path;
      if (directionMap[index][backTrackIndex] == "D") {
        backTrackIndex += heights[index];
      } else {
        backTrackIndex -= heights[index];
      }
    }

    std::cout << path << "\n";
  }

}
