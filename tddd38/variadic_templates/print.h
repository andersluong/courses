#include <iostream>

//template<>
void print_helper() {
    std::cout << std::endl;
}

template<typename First, typename... Rest>
void print_helper(First first, Rest... rest) {
    std::cout << first << " ";
    print_helper(rest...);
}

template<typename... Ts>
void print(Ts... list) {
    //print_helper(list...);
    ((std::cout << list << " "), ...);
    std::cout << std::endl;
}