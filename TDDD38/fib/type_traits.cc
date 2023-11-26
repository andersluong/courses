// Implement is_const, is_pointer, is_array and is_const_pointer here

template<bool B>
struct base {
  static bool const value{B};
};

template<typename T>
struct is_const : public base<false> {};

template<typename T>
struct is_const <T const> : public base<true> {};

template<typename T>
struct is_pointer : public base<false> {};

template<typename T>
struct is_pointer <T*> : public base<true> {};

template<typename T>
struct is_pointer <T* const> : public base<true> {};

template<typename T>
struct is_array : public base<false> {};

template<typename T, unsigned int N>
struct is_array<T[N]> : public base<true> {};

template <typename T>
struct is_const_pointer : public base<false> {};

template<typename T>
struct is_const_pointer<T* const> : public base<true> {};

int main()
{ 
  static_assert(is_const<int const>::value, "is_const failed for 'int const'");
  static_assert(is_const<int* const>::value, "is_const failed for 'int* const'");
  static_assert(!is_const<int>::value, "is_const failed for 'int'");
  static_assert(!is_const<int const*>::value, "is_const failed for 'int const*'");

  static_assert(is_pointer<int*>::value, "is_pointer failed for 'int*'");
  static_assert(is_pointer<int const*>::value, "is_pointer failed for 'int const*'");
  static_assert(is_pointer<int* const>::value, "is_pointer failed for 'int* const'");
  static_assert(!is_pointer<int>::value, "is_pointer failed for 'int'");

  static_assert(is_array<int[5]>::value, "is_array failed for 'int[5]'");
  static_assert(is_array<int const[7]>::value, "is_array failed for 'int const[7]'");
  static_assert(!is_array<int>::value, "is_array failed for 'int'");

  static_assert(is_const_pointer<int* const>::value, "is_const_pointer failed for 'int* const'");
  static_assert(!is_const_pointer<int*>::value, "is_const_pointer failed for 'int*'");
  static_assert(!is_const_pointer<int>::value, "is_const_pointer failed for 'int'");
  static_assert(!is_const_pointer<int const>::value, "is_const_pointer failed for 'int const'");
}
