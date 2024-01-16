#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

bool addPlaceholder(std::unordered_map<std::string, std::string> &placeholders, std::istringstream &iss1, std::istringstream &iss2) {
  std::string word1, word2;
  while (iss1 >> word1) {
    iss2 >> word2;
    if (word1[0] == '<') {
      if (placeholders.contains(word1)) {
        if (placeholders[word1] != word2) {
          return false;
        }
      }
      placeholders[word1] = word2;
    }
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
      result += placeholders1[word] + " ";
    } else {
      result += word + " ";
    }
  }
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
