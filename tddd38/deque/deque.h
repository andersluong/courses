#include <array>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T, unsigned chunk_size> class deque {
public:
  deque();

  deque(const deque &other);

  void push_back(T elem);

  void push_front(T elem);

  void pop_front();

  void pop_back();

  T &operator[](unsigned index) const;

  unsigned size();

  unsigned size() const;

  T at(unsigned index);

  T at(unsigned index) const;

private:
  T *data;
  unsigned begin;
  unsigned length;
  unsigned chunks;
};

template <typename T, unsigned chunk_size> deque<T, chunk_size>::deque() {
  data = new T[chunk_size]{};
  begin = 0;
  length = 0;
  chunks = 1;
}

template <typename T, unsigned chunk_size>
deque<T, chunk_size>::deque(const deque &other) {
  for (unsigned i{0}; i < other.length; i++) {
    data[i] = other.data[i];
  }
  begin = other.begin;
  length = other.length;
  chunks = other.chunks;
}

template <typename T, unsigned chunk_size>
inline void deque<T, chunk_size>::push_back(T elem) {
  if (length == 0 || length) {
  }
  data[length] = elem;
  length++;
}

template <typename T, unsigned chunk_size>
void deque<T, chunk_size>::push_front(T elem) {
  data[0] = elem;
}

template <typename T, unsigned chunk_size>
void deque<T, chunk_size>::pop_front() {
  if (length == 0) {
    throw std::out_of_range("No more elements to pop.");
  }
}

template <typename T, unsigned chunk_size>
void deque<T, chunk_size>::pop_back() {
  if (length == 0) {
    throw std::out_of_range("Out of range.");
  }
  length--;
}

template <typename T, unsigned chunk_size>
T &deque<T, chunk_size>::operator[](unsigned index) const {
  if (index >= length) {
    throw std::out_of_range("Out of range.");
  }
  return data[index];
}

template <typename T, unsigned chunk_size>
unsigned deque<T, chunk_size>::size() {
  return length;
}

template <typename T, unsigned chunk_size>
unsigned deque<T, chunk_size>::size() const {
  return length;
}

template <typename T, unsigned chunk_size>
T deque<T, chunk_size>::at(unsigned index) {
  if (length == 0) {
    throw std::out_of_range("Out of range.");
  }
  return data[index];
}

template <typename T, unsigned chunk_size>
T deque<T, chunk_size>::at(unsigned index) const {
  if (length == 0) {
    throw std::out_of_range("Out of range.");
  }
  return data[index];
}
