#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

template <typename T>
using worldMapType = std::array<std::array<T, 1001>, 40>;

static const int UNDEFINED = -1;

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
      int moveDownIndex = prevIndex - instruction;
      int moveUpIndex = prevIndex + instruction;

      // check down branch
      if (moveDownIndex >= 0) {
        if (worldMap[index][moveDownIndex] != UNDEFINED) {
          if (prevInstruction < worldMap[index][moveDownIndex]) {
            // found a smaller path, update it
            worldMap[index][moveDownIndex] = prevInstruction;
            directionMap[index][moveDownIndex] = "D";
          }
        } else {
          // new path
          worldMap[index][moveDownIndex] = std::max(moveDownIndex, prevInstruction);
          directionMap[index][moveDownIndex] = "D";
        }
      }

      // check up branch
      if (worldMap[index][moveUpIndex] != UNDEFINED) {
        if (prevInstruction < worldMap[index][moveUpIndex]) {
          // found a smaller path, update it
          worldMap[index][moveUpIndex] = prevInstruction;
          directionMap[index][moveUpIndex] = "U";
        }
      } else {
        // new path
        worldMap[index][moveUpIndex] = std::max(moveUpIndex, prevInstruction);
        directionMap[index][moveUpIndex] = "U";
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
    std::array<int, 1001> distances;
    std::fill(distances.begin(), distances.end(), UNDEFINED);
    std::fill_n(worldMap.begin(), numberOfInstructions, distances);
    // used for knowing if we should go up or down
    worldMapType<std::string> directionMap;

    // solve
    solve(worldMap, directionMap, heights);
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
