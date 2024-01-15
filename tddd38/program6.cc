#include <cassert>
#include <list>
#include <string>
#include <vector>

template <typename Container>
using container_type = typename Container::value_type;

namespace details {

template <typename Container>
auto prepend(Container &container, container_type<Container> &&value, int, int)
    -> decltype(container.push_front(value), std::declval<void>()) {
  container.push_front(std::forward<container_type<Container>>(value));
}

template <typename Container>
auto prepend(Container &container, container_type<Container> &&value, int,
             double) -> decltype(value + container, std::declval<void>()) {
  container = std::forward<container_type<Container>>(value) + container;
}

template <typename Container>
auto prepend(Container &container, container_type<Container> &&value, double,
             double)
    -> decltype(container.insert(std::begin(container), 1, value),
                std::declval<void>()) {
  container.insert(std::begin(container), 1,
                   std::forward<container_type<Container>>(value));
}

} // namespace details

template <typename Container>
void prepend(Container &container, container_type<Container> &&value) {
  details::prepend(container, std::forward<container_type<Container>>(value), 0,
                   0);
}

int main() {
  std::vector<int> v{1, 2, 3};

  assert(v.front() == 1);
  prepend(v, 0);
  assert(v.front() == 0);

  std::list<float> d{1.2f, 3.45f, 67.8f, 9.0f};

  assert(d.front() == 1.2f);
  prepend(d, 0);
  assert(d.front() == 0.0f);

  std::string s{"ello world!"};

  assert(s.front() == 'e');
  prepend(s, 'H');
  assert(s.front() == 'H');
}
