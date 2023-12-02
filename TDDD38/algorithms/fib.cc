#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

int main() {
  unsigned num = 0;
  cin >> num;
  
  vector<unsigned long long int> fib(num, 1);
  adjacent_difference(begin(fib), next(begin(fib), num - 1), next(begin(fib)), plus<unsigned long long int>{});
  copy(begin(fib), end(fib), ostream_iterator<unsigned long long int>{cout, "\n"});
}
