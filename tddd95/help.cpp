/**
  Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using placeholder_map = std::unordered_map<std::string, std::string>;

bool isPlaceholder(std::string const& word) {
  return word[0] == '<';
}

std::vector<std::string> extractString(std::string const& raw) {
  std::istringstream iss{raw};
  return std::vector<std::string>{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
}

bool replacedPlaceholder(std::vector<std::string> &words1, std::vector<std::string> &words2) {
  for (unsigned i = 0; i < words1.size(); i++) {
    std::string word1 = words1[i];
    std::string word2 = words2[i];

    if (isPlaceholder(word1) && !isPlaceholder(word2)) {
      std::replace(words1.begin(), words1.end(), word1, word2);
      return true;
    }
    if (isPlaceholder(word2) && !isPlaceholder(word1)) {
      std::replace(words2.begin(), words2.end(), word2, word1);
      return true;
    }
  }
  return false;
}

bool arbitraryPlaceholder(std::vector<std::string> &words1, std::vector<std::string> &words2) {
  for (unsigned i = 0; i < words1.size(); i++) {
    std::string word1 = words1[i];
    std::string word2 = words2[i];

    if (isPlaceholder(word1) && isPlaceholder(word2)) {
      std::replace(words1.begin(), words1.end(), word1, std::string{"arbitrary"});
      std::replace(words2.begin(), words2.end(), word2, std::string{"arbitrary"});
      return true;
    }
  }
  return false;
} 

std::string solve(std::string const& pattern1, std::string const& pattern2) {
  std::vector<std::string> words1 = extractString(pattern1);
  std::vector<std::string> words2 = extractString(pattern2);
  if (words1.size() != words2.size()) {
    return "-";
  }
  while (true) {
    if (!replacedPlaceholder(words1, words2) && !arbitraryPlaceholder(words1, words2)) {
      if (words1 == words2) {
        std::string result;
        for (auto word: words1) {
          result += word + " ";
        }
        return result;
      }
      return "-";
    }
  }
  return "-";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
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
