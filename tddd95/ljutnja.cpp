#include <iostream>
#include <set>
#include <algorithm>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::string input1, input2;
  std::cin >> input1 >> input2;
  unsigned long long candies = std::stoi(input1);
  unsigned long long kids = std::stoi(input2);
  unsigned long long wanted = 0;
  std::set<unsigned long long> kids_wanted;
  for (unsigned long long i = 0; i < kids; i++) {
    std::cin >> input1;
    unsigned long long kid = std::stoi(input1);
    wanted += kid;
    kids_wanted.insert(kid);
  }
  
  unsigned long long difference = wanted - candies;
  unsigned long long index = 0;
  unsigned long long angryPoints = 0;
  std::for_each(kids_wanted.begin(), kids_wanted.end(), [&](unsigned long long const kid) mutable {
    unsigned long long a = difference / (kids - index);
    unsigned long long used = kid < a ? kid : a;
    // std::cout << "used: " << used << "\n";
    std::cout << "index: " << index << "\n";
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
