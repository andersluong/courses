#include <cassert>
#include <string>
#include <iostream>

template <typename T>
struct New_Allocator
{
  template <typename... Args>
  static T *create(Args &&...args)
  {
    T *object = new T{std::forward<Args>(args)...};
    return object;
  }
  static void destroy(T *object)
  {
    delete object;
  }
};

template <typename T>
struct Tracker_Allocator
{
  
  template <typename... Args>
  static T *create(Args &&...args)
  {
    T *object = new T{std::forward<Args>(args)...};
    std::cout << "new item created" << std::endl;
    return object;
  }
  static void destroy(T *object)
  {
    delete object;
    std::cout << "item deleted" << std::endl;
  }
};

template <typename T, template <typename> typename Allocator = New_Allocator>
class Stack
{

  struct Node;

public:
  Stack()
      : head{nullptr} {}

  Stack(Stack const &) = delete;
  Stack(Stack &&) = delete;

  Stack &operator=(Stack const &) = delete;
  Stack &operator=(Stack &&) = delete;

  ~Stack()
  {
    while (!empty())
    {
      pop();
    }
  }

  void push(int const &value)
  {
    head = Allocator<Node>::create(value, head);
  }

  int pop()
  {
    int result{top()};
    Node *old{head};
    head = head->next;
    Allocator<Node>::destroy(old);
    return result;
  }

  int &top()
  {
    return head->value;
  }

  int const &top() const
  {
    return head->value;
  }

  bool empty() const
  {
    return head == nullptr;
  }

private:
  struct Node
  {
    int value;
    Node *next;
  };

  Node *head;
};

int main()
{
  Stack<std::string, Tracker_Allocator> st{};
  assert(st.empty());

  st.push(1);
  assert(!st.empty());
  assert(st.top() == 1);

  st.push(2);
  assert(st.top() == 2);
  assert(st.pop() == 2);

  assert(st.pop() == 1);

  assert(st.empty());

  st.push(3);
  assert(st.pop() == 3);

  st.push(4);

  st.push(5);
  assert(st.pop() == 5);
}
