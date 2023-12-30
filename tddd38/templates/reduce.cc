#include <cstddef> // gives access to size_t
#include <iostream>
#include <string>

using namespace std;

/*
  Your code here
 */


double multiply(double const& lhs, double const& rhs)
{
    return lhs * rhs;
}

template<typename T>
T addition(T const& lhs, T const& rhs) {
    return lhs + rhs;
}

template<typename T, size_t N>
T reduce(T const (&array)[N], T init_value = T{}, T (*op)(T const& lhs, T const& rhs) = addition<T>) {
    T result{ op(init_value, array[0]) };
    for (unsigned i{1}; i < N; ++i) {
        result = op(result, array[i]);
    }
    return result;
}

int main()
{
    double pi[]{0.0505, 0.0505, 0.0405};
    double factorial[]{1.0, 2.0, 3.0, 4.0, 5.0};
    string concat[]{" ", "world"};
    cout << reduce({1,2,3,4,5}) << endl;
    cout << reduce(pi, 3.0) << endl;
    cout << reduce(factorial, 1.0, multiply) << endl;
    cout << reduce(concat, "hello"s) << endl;
}
