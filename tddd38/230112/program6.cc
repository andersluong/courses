#include <cassert>
#include <deque>
#include <list>
#include <vector>

template <typename T, typename Container>
std::vector<T> flatten(const Container &container);

namespace details {

template <typename T, typename Container>
auto flatten(const Container &container, int) -> decltype(container == std::declval<T>(), std::vector<T>{}) {
  return std::vector<T>{container};
}

template <typename T, typename Container>
auto flatten(const Container &container, double) -> decltype(*container, std::vector<T>{}) {
  return ::flatten<T>(*container);
}

template <typename T, typename Container>
auto flatten(const Container &container, int) -> decltype(std::begin(container), std::vector<T>{}) {
  std::vector<T> result{};
  for (auto it = std::begin(container); it != std::end(container); ++it) {
    auto elemResult = ::flatten<T>(*it);
    result.insert(result.end(), elemResult.cbegin(), elemResult.cend());
  }
  return result;
}

} // namespace details

template <typename T, typename Container>
std::vector<T> flatten(const Container &container) {
  return details::flatten<T>(container, 0);
}

int main() {
  { assert(flatten<int>(5) == std::vector<int>{5}); }
  {
    std::vector<std::list<int>> v{{1, 2, 3}, {4, 5, 6, 7}, {8, 9}};

    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto res = flatten<int>(v);
    assert(flatten<int>(v) == expected);
  }

  {
    std::vector<char> data{'a', 'b', 'c'};

    using iterator = std::vector<char>::iterator;

    std::vector<std::vector<iterator>> v{
        {std::begin(data), std::begin(data), std::begin(data)},
        {std::begin(data) + 1},
        {std::begin(data) + 2, std::begin(data) + 2}};

    std::vector<char> expected{'a', 'a', 'a', 'b', 'c', 'c'};
    assert(flatten<char>(v) == expected);
  }

  {
    std::vector<std::list<std::deque<std::vector<float>>>> v{
        {
            {
                {1.2, 3.45, 6.0},
                {7.8, 9.10},

            },
            {{11.1213, 14.0}, {15.16, 17.18, 19.20}, {21.22}},
        },

        {{}, {{}, {23.2425}, {}}, {}},
    };

    std::vector<float> expected{1.2,  3.45,  6.0,   7.8,   9.10,  11.1213,
                                14.0, 15.16, 17.18, 19.20, 21.22, 23.2425};
    assert(flatten<float>(v) == expected);
  }

  {

    int x{5};
    std::vector<int *> v{&x};

    assert((flatten<int>(v) == std::vector<int>{5}));
    assert((flatten<int *>(v) == std::vector<int *>{&x}));
  }
}
