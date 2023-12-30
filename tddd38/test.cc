#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v{1, 3};
    std::back_inserter(v)++ = 7;
    int start = *v.begin();
    int value{++(*v.begin())};
    *std::inserter(v, v.begin() + 1) = value;
    for (int i : v)
    {
        std::cout << i << " ";
    }
}