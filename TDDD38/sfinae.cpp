
#include <vector>
#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T>
enable_if_t<(sizeof(T) < 4), int> foo(T &&)
{
    cout << "test: " << typeid(enable_if_t<(sizeof(T) < 4), bool>).name();
    return 1;
}

template <typename T, T = nullptr>
int foo(T &&)
{
    return 2;
}

template <typename T>
auto foo(T &&t) -> decltype(t.size(), 3)
{
    return 3;
}

int main()
{
    vector<int> v{};
    short int s{};
    cout << foo(s)
         << foo(nullptr)
         << foo(v);
}