#include <type_traits>

namespace details
{
    // implement add_pointers function template here
}

template <typename T, typename U>
struct add_pointers
{
  using type = decltype(details::add_pointers_helper<T, U>());
};

int main()
{
  static_assert(std::is_same_v<add_pointers<int, int>::type, int>, "int + int = int");
  static_assert(std::is_same_v<add_pointers<int, int*>::type, int*>, "int + int* = int*");
  static_assert(std::is_same_v<add_pointers<int*, int*>::type, int**>, "int* + int* = int**");
  static_assert(std::is_same_v<add_pointers<int**, int*>::type, int***>, "int** + int* = int**");
  static_assert(std::is_same_v<add_pointers<int**, int***>::type, int*****>, "int** + int*** = int*****");
}
