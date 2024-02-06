#include <iostream>
#include <array>
#include <bitset> 

using stonesType = std::array<int, 8>;
using worldMapType = std::array<stonesType, 101>;

static const int UNDEFINED = -1;

int flip(int const stone, int const index) {
  return stone ^ (1 << index);
}

// void checkStone(worldMapType &worldMap, worldMapType &preferences, int const priest, int const choice, int const stone) {
//   int nextStone = worldMap[priest + 1][choice];
//   if (nextStone == UNDEFINED) {
//     // this stone is not yet defined, so update it
//     worldMap[priest + 1][choice] = stone;
//   } else if (preferences[priest][stone] < preferences[priest][nextStone]) {
//     // this new priest prefers this stone more, so update it
//     worldMap[priest + 1][choice] = stone;
//   }
// }
//
// void solve(worldMapType &worldMap, worldMapType &preferences, int const numberOfPriests) {
//   // when there are 0 priests, we start with NNN
//   worldMap[0][0] = 0b000;
//
//   for (int priest = 0; priest < numberOfPriests; priest++) {
//     stonesType stones = worldMap[priest];
//     for (unsigned stone = 0b000; stone < stones.size(); stone++) {
//       if (stones[stone] == UNDEFINED) {
//         continue;
//       }
//       int choice1 = flip(stone, 0);
//       int choice2 = flip(stone, 1);
//       int choice3 = flip(stone, 2);
//
//       checkStone(worldMap, preferences, priest, choice2, stone);
//       checkStone(worldMap, preferences, priest, choice1, stone);
//       checkStone(worldMap, preferences, priest, choice3, stone);
//     }
//   }
// }

int solve(worldMapType &worldMap, worldMapType &preferences, int const numberOfPriests, int const priest, int const stone) {
  if (priest == numberOfPriests) {
    return stone;
  }
  if (worldMap[priest][stone] != UNDEFINED) {
    return worldMap[priest][stone];
  }
  int choice1 = flip(stone, 0);
  int choice2 = flip(stone, 1);
  int choice3 = flip(stone, 2);
  int nextStone1 = solve(worldMap, preferences, numberOfPriests, priest + 1, choice1);
  int nextStone2 = solve(worldMap, preferences, numberOfPriests, priest + 1, choice2);
  int nextStone3 = solve(worldMap, preferences, numberOfPriests, priest + 1, choice3);

  int bestNextStone = nextStone1;
  if (preferences[priest][nextStone2] < preferences[priest][bestNextStone]) {
    bestNextStone = nextStone2;
  }
  if (preferences[priest][nextStone3] < preferences[priest][bestNextStone]) {
    bestNextStone = nextStone3;
  }
  worldMap[priest][stone] = bestNextStone;
  return bestNextStone;
}

int main() {
  int rounds;
  std::cin >> rounds;
  
  for (int round = 0; round < rounds; round++) {
    int numberOfPriests;
    std::cin >> numberOfPriests;
    worldMapType worldMap;
    stonesType votes;
    std::fill(votes.begin(), votes.end(), UNDEFINED);
    std::fill_n(worldMap.begin(), numberOfPriests + 1, votes);

    worldMapType preferences;
    for (int i = 0; i < numberOfPriests; i++) {
      for (int j = 0; j < 8; j++) {
        std::cin >> preferences[i][j];
      }
    }

    // Do dynamic programming
    int stone = solve(worldMap, preferences, numberOfPriests, 0, 0b000);
    // std::cout << std::bitset<3>(stone) << "\n";
    // solve(worldMap, preferences, numberOfPriests);

    // std::cout << "world map:\n";
    // for (int row = 0; row <= numberOfPriests; row++) {
    //   std::cout << row << ": [ ";
    //   for (int col = 0; col < 8; col++) {
    //     if (worldMap[row][col] == UNDEFINED) {
    //       std::cout << "(" << std::bitset<3>(col) << ": " << UNDEFINED << ") ";
    //     } else {
    //       std::cout << "(" << std::bitset<3>(col) << ": " << std::bitset<3>(worldMap[row][col]) << ") ";
    //     }
    //   }
    //   std::cout << "]\n";
    // }
    // std::cout << "preferences:\n";
    // for (int row = 0; row < numberOfPriests; row++) {
    //   std::cout << row << ": [ ";
    //   for (int col = 0; col < 8; col++) {
    //     std::cout << "(" << std::bitset<3>(col) << ": " << preferences[row][col] << ") ";
    //   }
    //   std::cout << "]\n";
    // }

    // break; // only one round for debugging
    // print out the result
    for (auto bit : std::bitset<3>(stone).to_string()) {
      if (bit == '1') {
        std::cout << "Y";
      } else {
        std::cout << "N";
      }
    }
    std::cout << "\n";
  }
}
