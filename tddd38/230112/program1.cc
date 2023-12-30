
/* Example output:

Note: <ENTER> and <ctrl+D> refers to user input.

$ ./a.out
I study at LiU <ENTER>
I study at Linköping University
I take COURSE at LiU <ENTER>
I take TDDD38 at Linköping University
<ctrl+D>

$ ./a.out
The course FULL_COURSE taught me how to fully utilize C++ <ENTER>
The course TDDD38 at Department of Computer and Information Science / Linköping
University taught me how to fully utilize C++ <ctrl+D>

*/

#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>

using macroMap = std::map<std::string, std::string>;

macroMap define_macros(std::ifstream &ifs) {
  macroMap macros{};
  std::string input{};
  while (std::getline(ifs, input)) {
    std::string::size_type delim = input.find(":");
    std::string key = input.substr(0, delim);
    std::string value = input.substr(delim + 1);
    std::string_view v = value;
    v.remove_prefix(std::min(v.find_first_not_of(" "), v.size()));
    macros[key] = v;
  }
  return macros;
}

std::string expand(const std::string &input, const macroMap &macros) {
  std::istringstream ifs{input};
  std::string output{};
  std::for_each(std::istream_iterator<std::string>(ifs),
                std::istream_iterator<std::string>(), [&](std::string word) {
                  if (macros.contains(word)) {
                    output += macros.at(word) + " ";
                  } else {
                    output += word + " ";
                  }
                });
  return output;
}

int main() {
  std::ifstream ifs{"macros.txt"};
  macroMap macros = define_macros(ifs);

  std::string input;
  while (std::getline(std::cin, input)) {
    std::cout << expand(input, macros) << std::endl;
  }
}
