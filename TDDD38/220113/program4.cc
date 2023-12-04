#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

// Possible implementation for Grid::print
// Will support printing of a grid even if the number of items is not
// a multiple of the grid width.
void print(std::ostream& os)
{
    // Print header for the grid
    os << name << ":\n";
    for (int i{0}; i < items.size(); ++i)
    {
        // print each item
        print_item(os, items[i]);

        // If we have filled one row (or if this is the last item),
        // print a newline character
        if ((i + 1) % width == 0 || i + 1 == items.size())
        {
            os << '\n';
        }
        else
        {
            os << ' ';
        }
    }
}

/* Expected output:

My Text: "This is a text"

My Grid (3):
  1  12 123
456   4  45
 78 789   7

My List:
 - [  1]
 - [ 12]
 - [123]
 - [456]
 - [  4]
 - [ 45]
 - [ 78]
 - [789]
 - [  7]

My Grid (2):
  1  12
123 456
  4  45
 78 789
  7

*/

int main()
{
    std::vector</* Element */> elements = {
        Label{"My Label", "This is a text"},
        Grid<3>{"My Grid (3)"},
        List{"My List"},
        Grid<2>{"My Grid (2)"}
    };
    std::vector<int> data {1, 12, 123, 456, 4, 45, 78, 789, 7};

    // Populate each collection with 'data'
    for (int n : data)
    {
        for (auto e : elements)
        {
            // If e is of type 'Collection':
            // call insert(n) on it
        }
    }

    // Print each element
    for (auto e : elements)
    {
        // call print(std::cout) on e
        std::cout << std::endl;
    }
    
}
