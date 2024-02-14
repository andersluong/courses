#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <array>

using boardType = std::array<std::array<int, 8>, 8>;

struct Position {
  int x;
  int y;
};

int letterToNumber(char const letter) {
  return letter - 'a';
}

char numberToLetter(int const number) {
  return number + 'a' - 1;
}

std::vector<Position> getValidMoves(Position const &position) {
  std::vector<Position> validMoves;
  std::vector<Position> possibleMoves = {
    { -2, -1 },
    { -2, 1 },
    { -1, -2 },
    { -1, 2 },
    { 1, -2 },
    { 1, 2 },
    { 2, -1 },
    { 2, 1 }
  };

  for (auto move : possibleMoves) {
    int x = position.x + move.x;
    int y = position.y + move.y;

    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
      validMoves.push_back({ x, y });
    }
  }

  return validMoves;
}

struct Comparator {
  bool operator()(std::pair<int, Position> const &a, std::pair<int, Position> const &b) const {
    return a.first < b.first;
  }
};

void solve(boardType &board, Position const &startPosition) {
  std::multiset<std::pair<int, Position>, Comparator> queue;
  queue.insert({ 0, startPosition });
  while (!queue.empty()) {
    Position currentPosition = queue.begin()->second;
    queue.erase(queue.begin());
    for (Position nextMove : getValidMoves(currentPosition)) {
      // if (board[currentPosition.y][currentPosition.x] == 1) {
      //   std::cout << "currentPosition: " << currentPosition.x << " " << currentPosition.y << "\n";
      //   std::cout << "nextMove: " << nextMove.x << " " << nextMove.y << "\n";
      // }
      if (board[nextMove.y][nextMove.x] == -1) {
        board[nextMove.y][nextMove.x] = board[currentPosition.y][currentPosition.x] + 1;
        queue.insert({ board[nextMove.y][nextMove.x], nextMove });
      }
    }
  }
}

struct HidingComparator {
  bool operator()(Position const &a, Position const &b) const {
    if (a.y == b.y) {
      return a.x < b.x;
    }
    return a.y > b.y;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int numberOfTestCases;
  std::cin >> numberOfTestCases;

  for (int i = 0; i < numberOfTestCases; i++) {
    char column;
    int row;
    std::cin >> column >> row;
    Position startPosition = { letterToNumber(column), row - 1 };

    // initialize board
    boardType board;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        board[i][j] = -1;
      }
    }

    board[startPosition.y][startPosition.x] = 0;

    solve(board, startPosition);

    // for (int i = 7; i >= 0; i--) {
    //   for (int j = 0; j < 8; j++) {
    //     std::cout << board[i][j] << " ";
    //   }
    //   std::cout << "\n";
    // }

    int max = 0;
    std::multiset<Position, HidingComparator> hidingPlaces;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (board[i][j] > max) {
          max = board[i][j];
          hidingPlaces.clear();
          hidingPlaces.insert({ j, i });
        } else if (board[i][j] == max) {
          hidingPlaces.insert({ j, i });
        }
      }
    }
    std::cout << max << " ";
    for (auto place : hidingPlaces) {
      std::cout << numberToLetter(place.x + 1) << place.y + 1 << " ";
    }
    std::cout << "\n";
  }
}
