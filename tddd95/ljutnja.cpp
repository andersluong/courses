#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  unsigned candiesAvailable; // M from kattis
  unsigned kids; // N from kattis
  std::cin >> candiesAvailable >> kids;

  std::vector<unsigned> candiesWishlist;
  unsigned long long totalCandies = 0;
  for (unsigned i = 0; i < kids; i++) {
    unsigned kidWants;
    std::cin >> kidWants;
    totalCandies += kidWants;
    candiesWishlist.push_back(kidWants);
  }

  std::sort(candiesWishlist.begin(), candiesWishlist.end());
  
  unsigned long long candiesLeft = totalCandies - candiesAvailable;
  unsigned long long angryPoints = 0;

  // candies left to give out. We want to distribute them evenly so less kids are angry
  for (unsigned i = 0; i < candiesWishlist.size(); i++) {
    double check = (double)candiesLeft / (kids - i);
    unsigned long long candiesToGive = std::min((unsigned)std::floor(check), candiesWishlist[i]);
    angryPoints += candiesToGive * candiesToGive;
    candiesLeft -= candiesToGive;
  }
  std::cout << angryPoints << "\n";
  
  /*
    difference = wanted - m

    5 3
    5
    3
    2

  */
}
