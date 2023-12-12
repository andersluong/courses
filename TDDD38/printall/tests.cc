#include <array>
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

template <typename T> void print(std::ostream &os, T const &value);

namespace details {

void print(std::ostream &os, std::string const &value, int) { os << value; }
void print(std::ostream &os, char const *value, int) { os << value; }

template <size_t N>
void print(std::ostream &os, std::string const (&value)[N], int) {
  os << "{";
  for (auto it = std::begin(value); it != std::end(value) - 1; ++it) {
    ::print(os, *it);
    os << ", ";
  }
  ::print(os, *(std::end(value) - 1));
  os << "}";
}

template <typename T>
auto print(std::ostream &os, T const &value, int)
    -> decltype(std::begin(value), std::declval<void>()) {
  os << "{";
  for (auto it = std::begin(value); it != std::end(value); ++it) {
    ::print(os, *it);
    os << ", ";
  }
  os << "}";
}

template <typename T> void print_with_space(std::ostream &os, T const &value) {
  ::print(os, value);
  os << " ";
}

template <typename T, std::size_t... Is>
void print_tuple(std::ostream &os, T const &tuple, std::index_sequence<Is...>) {
  (print_with_space(os, std::get<Is>(tuple)), ...);
}

template <typename T>
auto print(std::ostream &os, T const value, int)
    -> decltype(std::get<0>(value), std::tuple_size_v<T>,
                std::declval<void>()) {
  constexpr size_t tuple_size = std::tuple_size_v<decltype(value)>;
  os << "(";
  print_tuple(os, value, std::make_index_sequence<tuple_size>{});
  os << ")";
}

template <typename T, size_t N>
void print(std::ostream &os, std::array<T, N> const &value, int) {
  os << "{";
  for (auto it = std::begin(value); it != std::end(value) - 1; ++it) {
    ::print(os, *it);
    os << ", ";
  }
  ::print(os, *(std::end(value) - 1));
  os << "}";
}

template <typename T> void print(std::ostream &os, T const &value, double) {
  os << value;
}

} // namespace details

template <typename T> void print(std::ostream &os, T const &value) {
  details::print(os, value, 0);
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
