#include <cassert>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
class Stack {
public:
  Stack(std::initializer_list<T> list): storage{list} {};

  explicit operator bool() {
    return !storage.empty();
  }

  operator T() {
    return storage.back();
  }

  Stack& operator<<(const T &value) {
    storage.push_back(value); 
    return *this;
  }

  Stack& operator>>(T &value) {
    value = storage.back();
    storage.pop_back();
    return *this;
  }

private:
  std::vector<T> storage;

  friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    std::copy(stack.storage.rbegin(), stack.storage.rend(), std::ostream_iterator<T>(os, " "));
    return os;
  }
};


int main() {
  {
    Stack<int> st{6, 5, 4};

    // 4 should be at the top of the stack
    assert(st == 4);

    // pushing 3, 2 and 1 to the stack
    st << 3 << 2 << 1;

    // now 1 should be at the top
    assert(st == 1);

    // stack must be convertible to bool
    assert(st);

    std::ostringstream oss{};
    oss << st;
    assert(oss.str() == "1 2 3 4 5 6 ");

    // popping into a, b and c as a chained operator call.
    int a, b, c;
    st >> a >> b >> c;

    assert(a == 1);
    assert(b == 2);
    assert(c == 3);

    // pop the values one by one
    int i{4};
    while (st) {
      int x;
      st >> x;

      assert(x == i);
      ++i;
    }

    // now the list should be empty
    assert(!st);
  }
}
