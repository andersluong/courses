#include <type_traits>

template<typename T>
struct count_pointers{
    using value = count_pointers<std::remove_pointer_t<T>>::value + 1;
  };

  template<typename T> 
  struct count_pointers<N=0>{
   using value = typename 0;
  };

int main() {
 static_assert(count_pointers<int>::value == 1);
}
