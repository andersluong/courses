#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

/* This should give the following output (or something similar at least):
5
{1, 2, 3}
{(1 1), (2 2), (3 3)}
(5 3.14)
{hello, world}
{{ab, c}, {def, g, hi}}
SFINAE
string literal
 */
void print(std::ostream &os, char *const &n, int) { os << n; }

void print(std::ostream &os, std::string const &n, long) { os << n; }

template <typename T, std::size_t N>
void print(std::ostream &os, std::array<T, N> const &container, int) {
  os << '{';
  for (auto it = std::begin(container); it != std::end(container); it++) {
    // os << *it;
  }
  os << '}';
}

template <typename T>
auto print(std::ostream &os, T const &container, int)
    -> decltype(std::begin(container), std::declval<void>()) {
  os << '{';
  for (auto it = std::begin(container); it != std::end(container); it++) {
    // os << *it;
  }
  os << '}';
}

template <typename T>
auto print(std::ostream &os, T const &container, int)
    -> decltype(std::get<0>(container), std::tuple_size_v<decltype(container)>,
                std::declval<void>()) {
  os << '(';
  os << ')';
}

template <typename T> void print(std::ostream &os, T container, long) {
  os << container;
}

template <typename T> void print(std::ostream &os, T const &value) {
  print(os, value, 0);
}

int main() {
  print(std::cout, 5);
  std::cout << std::endl;

  std::vector<int> v{1, 2, 3};
  print(std::cout, v);
  std::cout << std::endl;

  std::map<int, int> m{{1, 1}, {2, 2}, {3, 3}};
  print(std::cout, m);
  std::cout << std::endl;

  std::tuple<int, double> t{5, 3.14};
  print(std::cout, t);
  std::cout << std::endl;

  std::string s[]{"hello", "world"};
  print(std::cout, s);
  std::cout << std::endl;

  std::array<std::vector<std::string>, 2> a{
      std::vector<std::string>{"ab", "c"},
      std::vector<std::string>{"def", "g", "hi"}};

  print(std::cout, a);
  std::cout << std::endl;

  char const *str{"SFINAE"};
  print(std::cout, str);
  std::cout << std::endl;

  print(std::cout, "string literal");
  std::cout << std::endl;
}
