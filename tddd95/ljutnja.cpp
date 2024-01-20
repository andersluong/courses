#include <iostream>
#include <set>
#include <algorithm>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::string input1, input2;
  std::cin >> input1 >> input2;
  unsigned candies = std::stoi(input1);
  unsigned kids = std::stoi(input2);
  unsigned wanted = 0;
  std::set<unsigned> kids_wanted;
  for (unsigned i = 0; i < kids; i++) {
    std::cin >> input1;
    unsigned kid = std::stoi(input1);
    wanted += kid;
    kids_wanted.insert(kid);
  }
  
  unsigned difference = wanted - candies;
  unsigned index = 0;
  unsigned angryPoints = 0;
  std::for_each(kids_wanted.begin(), kids_wanted.end(), [&](unsigned const kid) {
    unsigned a = difference / (kids - index);
    unsigned used = kid < a ? kid : a;
    // std::cout << "used: " << used << "\n";
    angryPoints += (used * used);
    difference -= used;
    index++;
  });
  std::cout << angryPoints << "\n";
  
  /*
    difference = wanted - m

    5 3
    5
    3
    2

  */
}
