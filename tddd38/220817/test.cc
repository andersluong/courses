#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>

int main() {
  std::string words = "Hello World is full of surprises!";
  for (auto wordIt : std::ranges::split_view(words, ' ')) {
    std::string_view word{wordIt.begin(), wordIt.end()};
    std::cout << std::quoted(word) << '\n';
  }
  return 0;
}
