#include <iostream>
#include <ranges>
#include <iterator>

int main() {
  std::ranges::copy(std::views::iota(0) | std::views::filter([](unsigned num) -> unsigned { return num % 2 == 0; }) | std::views::take(10), std::ostream_iterator<unsigned>(std::cout, " "));
}

