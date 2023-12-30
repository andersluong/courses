#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Element {
public:
  Element(std::string n) : name{n} {}

  virtual ~Element() = default;

  virtual void print(std::ostream &os) const = 0;

protected:
  std::string name;
};

class Label : public Element {
public:
  Label(std::string n, std::string t) : Element(n), text{t} {}

  virtual void print(std::ostream &os) const {
    os << name << ": " << '"' << text << "\"\n";
  }

protected:
  std::string text;
};

class Collection : public Element {
public:
  Collection(std::string n) : Element{n} {}

  void insert(int value) {
    items.push_back(value);
    int value_size = std::to_string(value).size();
    if (value_size > column_width) {
      column_width = value_size;
    }
  }

protected:
  virtual void print_item(std::ostream &os, int value) const {
    os << std::setw(column_width) << value;
  }

  std::vector<int> items{};
  int column_width = 0;

private:
};

template <int width> class Grid : public Collection {
public:
  Grid(std::string n) : Collection(n) {}
  // Possible implementation for Grid::print
  // Will support printing of a grid even if the number of items is not
  // a multiple of the grid width.
  void print(std::ostream &os) const override {
    // Print header for the grid
    os << name << ":\n";
    for (size_t i{0}; i < items.size(); ++i) {
      // print each item
      print_item(os, items[i]);

      // If we have filled one row (or if this is the last item),
      // print a newline character
      if ((i + 1) % width == 0 || i + 1 == items.size()) {
        os << '\n';
      } else {
        os << ' ';
      }
    }
  }

private:
};

class List : public Grid<1> {
public:
  List(std::string n) : Grid<1>{n} {}
  void print_item(std::ostream &os, int value) const override {
    os << std::setw(column_width) << "- [" << value << "]";
  }

private:
};

/* Expected output:

My Text: "This is a text"

My Grid (3):
  1  12 123
456   4  45
 78 789   7

My List:
 - [  1]
 - [ 12]
 - [123]
 - [456]
 - [  4]
 - [ 45]
 - [ 78]
 - [789]
 - [  7]

My Grid (2):
  1  12
123 456
  4  45
 78 789
  7

*/

int main() {
  std::vector<Element *> elements = {
      new Label{"My Label", "This is a text"}, new Grid<3>{"My Grid (3)"},
      new List{"My List"}, new Grid<2>{"My Grid (2)"}};
  std::vector<int> data{1, 12, 123, 456, 4, 45, 78, 789, 7};

  // Populate each collection with 'data'
  for (int n : data) {
    for (auto e : elements) {
      // If e is of type 'Collection':
      // call insert(n) on it
      if (auto elem = dynamic_cast<Collection *>(e)) {
        elem->insert(n);
      }
    }
  }

  // Print each element
  for (auto e : elements) {
    // call print(std::cout) on e
    e->print(std::cout);
    std::cout << std::endl;
  }
}
