/**
  Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

/**

Test case:
5
how now brown <animal>
<foo> now <color> cow
who are you
<a> <b> <a>
<a> b
c <a>
a b c <tag>
a b c
how now brown <animal>
<foo> now <color> <animal>

*/

bool addPlaceholder(std::unordered_map<std::string, std::string> &placeholders, std::istringstream &iss1, std::istringstream &iss2) {
  std::string word1, word2;
  while (iss1 >> word1) {
    if (!(iss2 >> word2)) {
      return false;
    }
    if (word1[0] == '<') {
      if (placeholders.find(word1) != placeholders.end()) {
        if (placeholders[word1] != word2) {
          return false;
        }
      }
      placeholders[word1] = word2;
    }
  }
  if (iss2 >> word2) {
    return false;
  }
  return true;
}

std::string solve(std::string const& pattern1, std::string const& pattern2) {
  std::unordered_map<std::string, std::string> placeholders1, placeholders2;
  std::istringstream iss1{pattern1};
  std::istringstream iss2{pattern2};
  if (!addPlaceholder(placeholders1, iss1, iss2)) {
    return "-";
  }
  iss1.clear();
  iss1.seekg(0, std::ios::beg);
  iss2.clear();
  iss2.seekg(0, std::ios::beg);
  if (!addPlaceholder(placeholders2, iss2, iss1)) {
    return "-";
  }
  std::string result, word;
  iss1.clear();
  iss1.seekg(0, std::ios::beg);
  while (iss1 >> word) {
    if (word[0] == '<') {
      if (placeholders1[word][0] == '<') {
        result += word.substr(1, word.length() - 2) + " ";
      } else {
        result += placeholders1[word] + " ";
      }
    } else {
      result += word + " ";
    }
  }
  result.pop_back();
  return result;
}

int main() {
  std::string input;
  std::getline(std::cin, input); // number of test cases
  int test_cases = std::stoi(input);
  std::vector<std::string> results;
  for (int i = 0; i < test_cases; i++) {
    std::getline(std::cin, input); // pattern 1
    std::string pattern1 = input;
    std::getline(std::cin, input); // pattern 2
    std::string pattern2 = input;
    results.push_back(solve(pattern1, pattern2));
  }
  std::copy(results.begin(), results.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
  return 0;
}
