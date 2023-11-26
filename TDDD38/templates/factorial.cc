#include <iostream>

using namespace std;

/*
  Your code here
 */
template<unsigned int N>
unsigned long long factorial() {
  return N * factorial<N-1>();
}

template<>
unsigned long long factorial<1>() {
  return 1;
}

template<>
unsigned long long factorial<0>() {
  return 1;
}

int main()
{
    cout << factorial<0>() << endl;
    cout << factorial<1>() << endl;
    cout << factorial<5>() << endl;
    cout << factorial<20>() << endl;
}
