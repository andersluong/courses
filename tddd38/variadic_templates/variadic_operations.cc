#include <iostream>
#include <type_traits>
#include <cstdint>

using namespace std;

template<typename... Ts>
class Pack {
    [&] (int n) mutable {
        n = n+1;
        return n + 1
    }
};

namespace v1 {
struct Pack {
    operator()
};
}

v1::Pack()

template<typename T>
bool contains_helper(Pack<>) {
    return false;
}

template<typename T, typename F, typename... R>
bool contains_helper(Pack<F, R...>) {
    if (is_same_v<T, F>) {
        return true;
    }
    Pack<R...> rest;
    return contains_helper<T>(rest);
}

template<typename T, typename... Ts>
bool contains(Pack<Ts...> pack) {
    return contains_helper<T>(pack);    
}

template<typename T>
int index_of_helper(Pack<>, int) {
    return -1;
}

template<typename T, typename F, typename... R>
int index_of_helper(Pack<F, R...>, int index) {
    if (is_same_v<T, F>) {
        return index;
    }
    Pack<R...> rest;
    return index_of_helper<T>(rest, ++index);
}

template<typename T, typename... Ts>
int index_of(Pack<Ts...> pack) {
    return index_of_helper<T>(pack, 0);
}

int main() {
    Pack<int, float, char> p;
    cout << contains<int>(p) << endl;
    cout << contains<bool>(p) << endl;
    cout << index_of<int>(p) << endl;
    cout << index_of<char>(p) << endl;
    cout << index_of<bool>(p) << endl;
}