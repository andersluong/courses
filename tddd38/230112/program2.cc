#include <string>
#include <vector>
#include <stdexcept> // exceptions

/* implement your solution here */

int main()
{
    std::string str1 { format("Hello world!") };
    assert(str1 == "Hello world!");
    
    std::string str2 { format("int: {}", 5) };
    assert(str2 == "int: 5");

    std::string my_string { "my string" };
    
    std::string str3 { format("string: {}", my_string) };
    assert(str3 == "string: <my string>");

    std::string str4 { format("{}:{}:{}", 1, 2, 3) };
    assert(str4 == "1:2:3");

    std::vector<std::string> v { "abc", "def", "ghi" };
    
    std::string str5 { format("vector: {}", v) };
    assert(str5 == "vector: { <abc> <def> <ghi> }");
    
    try
    {
        format("{}");
        assert(false);
    }
    catch (...) { }

    try
    {
        format("my string", 5);
        assert(false);
    }
    catch (...) { }
}
