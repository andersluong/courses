#ifndef STACK_H_
#define STACK_H_

#include <vector>
#include <iostream>

template <typename T>
class Stack
{
public:
    template <typename... Ts>
    Stack(Ts &&...elements)
    {
        constructor_helper(std::forward<Ts>(elements)...);
    };

    template <typename... R>
    void constructor_helper(T &&first, R &&...rest)
    {
        stack.push_back(first);
        constructor_helper(std::forward<R>(rest)...);
    }

    void constructor_helper() {}

    template <typename F, typename... R>
    void constructor_helper(F first, R... rest)
    {
        std::cout << "A parameter is in wrong format" << std::endl;
        return;
    }

    Stack &operator<<(T elem)
    {
        stack.push_back(elem);
        return *this;
    }

    Stack &operator>>(T &elem)
    {
        elem = stack.back();
        stack.pop_back();
        return *this;
    }

    bool operator==(T elem)
    {
        return stack.back() == elem;
    }

    bool is_empty() {
        return stack.size() == 0;
    }

private:
    friend std::ostream &operator<<(std::ostream &os, Stack<T> &s)
    {
        for (unsigned i = 0; i < s.stack.size(); i++) {
            os << s.stack[s.stack.size() - 1 - i] << " ";
        }
        return os;
    }

    std::vector<T> stack;
};

#endif