#include <iostream>
#include <vector>

std::string solve(std::vector<int> const& distances, int longestDistance, int remainingDistance) {
  std::string result;
  int currentDistance = 0;
  std::cout << "longestDistance: " << longestDistance << std::endl;
  for (auto distance : distances) {
    /*
       
      */
    std::cout << "remainingDistance: " << remainingDistance << ". currentDistance: " << currentDistance << ". distance: " << distance << std::endl;
    remainingDistance -= distance;
    if (currentDistance - distance < 0) {
      std::cout << "case #1" << std::endl;
      result += "U";
      currentDistance += distance;
    } else if (remainingDistance == currentDistance) {
      std::cout << "case #2" << std::endl;
      result += "D";
      currentDistance -= distance;
    } else if (distance <= currentDistance) {
      std::cout << "case #5" << std::endl;
      result += "D";
      currentDistance -= distance;
    } else if (distance + currentDistance >= longestDistance) {
      std::cout << "case #3" << std::endl;
      result += "D";
      currentDistance -= distance;
    } else {
      std::cout << "case #4" << std::endl;
      result += "U";
      currentDistance += distance;
    } 

  }
  return result;
}

int main() {
  std::string input;
  std::getline(std::cin, input);
  int test_cases = std::stoi(input);
  for (int i = 0; i < test_cases; ++i) {
    int numberOfDistances;
    std::getline(std::cin, input);
    numberOfDistances = std::stoi(input);
    std::vector<int> distances;
    int longestDistance = -1;
    int remainingDistance = 0;
    for (int j = 0; j < numberOfDistances; ++j) {
      std::cin >> input;
      int distance = std::stoi(input);
      distances.push_back(distance);

      // extra logic
      if (longestDistance == -1 && distance > longestDistance) {
        longestDistance = distance;
      }
      remainingDistance += distance;
    }
    std::cout << solve(distances, longestDistance, remainingDistance) << std::endl;
    // for (auto distance : distances) std::cout << distance << " ";
  }
}
