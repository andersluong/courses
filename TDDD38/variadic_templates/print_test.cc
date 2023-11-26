#include "print.h"

using namespace std;

struct X { };

ostream& operator<<(ostream& os, X const&)
{
  return os << "X";
}

int main()
{
  // should produce an empty line
  print();

  // should produce:
  // a 3.5 100 hello
  print('a', 3.5, 100, "hello");

  // should produce:
  // a b
  print('a', 'b');

  // should produce:
  // X Y Z
  print(X{}, "Y", "Z");
}
