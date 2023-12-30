#include <algorithm>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <vector>

// Implement Heap here
template <typename T, typename C = std::less<T>> class Heap {
public:
  Heap(std::initializer_list<T> values, C comp = {})
      : data{values.begin(), values.end()}, compare{comp} {
    std::make_heap(data.begin(), data.end(), compare);
  };

  typename std::vector<T>::const_iterator begin() const {
    return std::begin(data);
  }

  typename std::vector<T>::const_iterator end() const { return std::end(data); }

  T front() const {
    return data.at(0);
  }

  void pop() {
    if (data.size() > 0) {
      std::pop_heap(data.begin(), data.end(), compare);
      data.pop_back();
    }
  }

  void push(T elem) {
    data.push_back(elem);
    std::push_heap(data.begin(), data.end(), compare);
  }

private:
  std::vector<T> data;
  C compare;
};

int main() {

  {
    Heap<int> heap{1, 3, 4, 7, 9, 10};

    std::cout << "int heap with std::less:" << std::endl;

    std::cout << "\tCreation   : ";
    for (int v : heap) {
      std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "\tMax element: " << heap.front() << std::endl;

    heap.pop();

    std::cout << "\tAfter pop  : ";
    for (int v : heap) {
      std::cout << v << " ";
    }
    std::cout << std::endl;

    heap.push(11);

    std::cout << "\tPush 11    : ";
    for (int v : heap) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }

  {
    Heap<std::string, std::greater<std::string>> heap{"A", "AB", "C", "DE",
                                                      "EFG"};

    std::cout << "string heap with std::greater: " << std::endl;

    std::cout << "\tCreation   : ";
    for (std::string const &v : heap) {
      std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "\tMax element: " << heap.front() << std::endl;

    heap.pop();

    std::cout << "\tAfter pop  : ";
    for (std::string const &v : heap) {
      std::cout << v << " ";
    }
    std::cout << std::endl;

    heap.push("CD");

    std::cout << "\tPush \"CD\"  : ";
    for (std::string const &v : heap) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
  }
}
