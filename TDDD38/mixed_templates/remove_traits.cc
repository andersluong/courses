#include <type_traits>

template <typename T>
struct remove_reference
{
  using type = T;
};

// implement your specializations here

// implement remove_pointers here

int main()
{
  static_assert(std::is_same<
                remove_reference<int&&>::type, int
                >::value, "remove_reference failed for 'int&&'");
  static_assert(std::is_same<
                remove_reference<int&>::type, int
                >::value, "remove_reference failed for 'int&'");
  static_assert(std::is_same<
                remove_reference<int>::type, int
                >::value, "remove_reference failed for 'int'");
  static_assert(std::is_same<
                remove_reference<int const&>::type, int const
                >::value, "remove_reference failed for 'int const&'");

  static_assert(std::is_same<
                remove_pointers<int>::type, int
                >::value, "remove_pointers failed for 'int'");
  static_assert(std::is_same<
                remove_pointers<int*>::type, int
                >::value, "remove_pointers failed for 'int*'");
  static_assert(std::is_same<
                remove_pointers<int* const>::type, int
                >::value, "remove_pointers failed for 'int* const'");
  static_assert(std::is_same<
                remove_pointers<int* const*>::type, int
                >::value, "remove_pointers failed for 'int* const*'");
  static_assert(std::is_same<
                remove_pointers<int***>::type, int
                >::value, "remove_pointers failed for 'int***'");
}
