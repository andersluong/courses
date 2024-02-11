#include <iostream>
#include <vector>

struct Position {
  int x, y;
};

enum Symbol {
  PLAYER = 'P',
  GOLD = 'G',
  TRAP = 'T',
  WALL = '#',
  NORMAL = '.'
};

void movePlayer(std::vector<std::vector<char>> &worldMap, Position const position) {
  char currentTile = worldMap[position.y][position.x];
  if (currentTile == Symbol::GOLD) {
    worldMap[position.y][position.x] = Symbol::NORMAL;
  } else if (currentTile == Symbol::WALL) {
    // go back
    return;
  }

  // make the position just visited not possible to visit again
  worldMap[position.y][position.x] = Symbol::WALL;

  // check surroundings
  char up = worldMap[position.y - 1][position.x];
  char down = worldMap[position.y + 1][position.x];
  char left = worldMap[position.y][position.x - 1];
  char right = worldMap[position.y][position.x + 1];

  if (up == Symbol::TRAP || down == Symbol::TRAP || left == Symbol::TRAP || right == Symbol::TRAP) {
    return;
  }

  // collect gold
  movePlayer(worldMap, {position.x, position.y - 1});
  movePlayer(worldMap, {position.x, position.y + 1});
  movePlayer(worldMap, {position.x - 1, position.y});
  movePlayer(worldMap, {position.x + 1, position.y});
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  
  int width, height;
  std::cin >> width >> height;
  std::vector<std::vector<char>> worldMap(height, std::vector<char>(width));

  Position position;
  int possibleGold = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cin >> worldMap[i][j];

      if (worldMap[i][j] == Symbol::PLAYER) {
        position.x = j;
        position.y = i;
        worldMap[i][j] = Symbol::NORMAL;
      } else if (worldMap[i][j] == Symbol::GOLD) {
        possibleGold++;
      }
    }
  }

  movePlayer(worldMap, position);
  int leftGold = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (worldMap[i][j] == Symbol::GOLD) {
        leftGold++;
      }
    }
  }
  // print map
  // for (int i = 0; i < height; i++) {
  //   for (int j = 0; j < width; j++) {
  //     std::cout << worldMap[i][j];
  //   }
  //   std::cout << "\n";
  // }
  std::cout << possibleGold - leftGold << "\n";
}
