#include <cmath> // for std::sqrt
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
    return 1;
  }

  // filename is stored in argv[1]

  // implement the steps here
  std::ifstream file;
  file.open(argv[1], std::ios::binary | std::ios::in);
  if (!file.is_open()) {
    std::cerr << "Couldn't open file: " << argv[1] << std::endl;
    return 1;
  }
  double dx;
  file >> dx;
  // std::cout << dx << std::endl;

  std::vector<double> values { std::istream_iterator<double>(file), std::istream_iterator<double>() };

  std::vector<double> lengths;
  std::transform(values.begin(), values.end(), std::back_inserter(lengths), [oldValue = 0.0](const double value) mutable {
    double prevValue = oldValue;
    oldValue = value;
    return value - prevValue; 
  });
  for (auto value: lengths) std::cout << value << std::endl;
  std::reverse(lengths.begin(), lengths.end());
  // std::transform(lengths.begin() + 1, lengths.end(), lengths.begin(), [](double value) { return value; });
  std::transform(lengths.begin(), lengths.end(), lengths.begin(), [&](const double dy) { return std::sqrt(dx*dx + dy*dy); });
  std::cout << std::accumulate(lengths.begin(), lengths.end(), -*values.begin()) << std::endl;
}
