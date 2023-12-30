#include <istream>
#include <iostream>
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

struct Product
{
    string name;
    double price;
    int inventory;
};

ostream& operator<<(ostream& os, Product const& product)
{
    return os << product.name << ": "
              << product.price << " kr ("
              << product.inventory << " available)";
}

template <typename T>
T read(istream& is)
{
    T data;
    is >> data;
    return data;
}

template<>
string read<string>(istream& is) {
    string result;
    is.ignore(numeric_limits<streamsize>::max(), '#');
    getline(is, result, '#');
    return result;
}

template <>
Product read<Product>(istream& is) {
    Product data;
    data.name = read<string>(is);
    data.price = read<double>(is);
    data.inventory = read<int>(is);
    return data;
}

template <typename T>
void write(ostream& os, T const& t)
{
    os << t << ' ';
}

void write(ostream& os, string const& text) {
    os << '#' << text << '#';
}

void write(ostream& os, Product const& product) {
    //os << "#" << product.name << product.price << product.inventory;
    write(os, product.name);
    write(os, product.price);
    write(os, product.inventory);
}

int main()
{
    stringstream ss;
    { // send data to ss
        Product apple {"Red Apple", 1.5, 100};
        Product laptop{"Laptop", 5995.0, 10};
        Product monitor{"4K Monitor", 8790.0, 1};
        write(ss, apple);
        write(ss, laptop);
        write(ss, monitor);
    }

    //cout << ss.str() << endl;

    { // recieve data from ss
        Product apple  {read<Product>(ss)};
        Product laptop {read<Product>(ss)};
        Product monitor{read<Product>(ss)};
        cout << apple << endl
             << laptop << endl
             << monitor << endl;
    }
}
