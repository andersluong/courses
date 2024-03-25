#include <vector>
#include <ostream>

template<typename T>
class Stack {
public:
    template<typename... Ts>
    Stack(Ts&&... list) : stack{std::forward<Ts>(list)...}, x{a} {}

    bool operator==(T element) {
        return element == stack.back();
    }

    Stack& operator<<(T element) {
        stack.push_back(element);
        return *this;
    }

    Stack& operator>>(T& element) {
        element = stack.back();
        stack.pop_back();
        return *this;
    }

    bool is_empty() {
        return stack.size() == 0;
    }
private:
    std::vector<T> stack;

    friend std::ostream& operator<<(std::ostream& os, Stack<T>& s) {
        for (int i = s.stack.size() -1; i >= 0; --i) {
            os << s.stack[i] << " ";
        }
        return os;
    }
    int const& x;

    int* test = new int{5};
    int* test2 = &test;
    int test = int{5};
};