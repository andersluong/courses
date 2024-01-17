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
3
how now brown <animal>
<foo> now <color> cow
who are you
<a> <b> <a>
<a> b
c <a>

Test case:
6
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
test test1
test1 test

Test case:
1
how now brown <animal>
<foo> now <color> <foo>

Output:
how now brown how

*/

using placeholder_map = std::unordered_map<std::string, std::string>;

bool addPlaceholder(placeholder_map &placeholders1, placeholder_map & placeholders2, std::istringstream &iss1, std::istringstream &iss2) {
  std::vector<std::string> words1{ std::istream_iterator<std::string>{iss1}, std::istream_iterator<std::string>{} };
  std::vector<std::string> words2{ std::istream_iterator<std::string>{iss2}, std::istream_iterator<std::string>{} };
  if (words1.size() != words2.size()) {
    return false;
  }
  for (unsigned i = 0; i < words1.size(); i++) {
    std::string word1 = words1[i];
    std::string word2 = words2[i];
    if (word1[0] == '<') {
      if (placeholders1.find(word1) != placeholders1.end()) {
        if (placeholders1[word1] != word2) {
          return false;
        }
      }
      placeholders1[word1] = word2;
    } else if (word2[0] == '<') {
      if (placeholders2.find(word2) != placeholders2.end()) {
        if (placeholders2[word2] != word1) {
          return false;
        }
      }
      placeholders2[word2] = word1;
    } else if (word1 != word2) {
      return false;
    }
  }
  return true;
}

std::string getTextFromPlaceholder(std::string placeholder, placeholder_map &placeholders1, placeholder_map &placeholders2) {
  std::string result;
  if (placeholders1[placeholder][0] == '<') {
    return getTextFromPlaceholder(placeholders1[placeholder], placeholders1, placeholders2);
  } else {
    result = placeholders1[placeholder];
  }
  if (placeholders2[placeholder][0] == '<') {
    return getTextFromPlaceholder(placeholders2[placeholder], placeholders1, placeholders2);
  } else {
    result = placeholders2[placeholder];
  }
  return result;
}

std::string solve(std::string const& pattern1, std::string const& pattern2) {
  placeholder_map placeholders1, placeholders2;
  std::istringstream iss1{pattern1};
  std::istringstream iss2{pattern2};
  if (!addPlaceholder(placeholders1, placeholders2, iss1, iss2)) {
    return "-";
  }
  std::string result, word;
  iss1.clear();
  iss1.seekg(0, std::ios::beg);
  while (iss1 >> word) {
    if (word[0] == '<') {
      result += getTextFromPlaceholder(word, placeholders1, placeholders2) + " ";
    } else {
      result += word + " ";
    }
  }
  result.pop_back();
  return result;
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
  std::cout << std::flush;
  return 0;
}
