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

bool mapContains(placeholder_map const& placeholders, std::string const& word) {
  return placeholders.find(word) != placeholders.end();
}

bool checkPlaceholder(placeholder_map &placeholders, std::string const& word1, std::string const& word2) {
  if (mapContains(placeholders, word1)) {
    std::string oldValue = placeholders[word1];
    if (isPlaceholder(oldValue) && !isPlaceholder(word2)) {
      placeholders[word1] = word2;
    } else if (!isPlaceholder(oldValue) && !isPlaceholder(word2) && oldValue != word2) {
      return false;
    } else if (isPlaceholder(oldValue) && isPlaceholder(word2)) {
      placeholders[word1] += " " + word2;
    }
  } else if (isPlaceholder(word1)) {
    placeholders[word1] = word2;
  }
  return true;
}

std::vector<std::string> extractString(std::string const& raw) {
  std::istringstream iss{raw};
  return std::vector<std::string>{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };
}

bool notSame(placeholder_map &placeholders, std::string const& word1, std::string const& word2) {
  std::vector<std::string> p = extractString(placeholders[word1]);
  for (auto elem: p) {
    if (elem != word2) {
      return true;
    }
  }
  return false;
}

std::string solve(std::string const& pattern1, std::string const& pattern2) {
  placeholder_map placeholders1, placeholders2;
  std::vector<std::string> words1 = extractString(pattern1);
  std::vector<std::string> words2 = extractString(pattern2);
  if (words1.size() != words2.size()) {
    return "-";
  }
  for (unsigned i = 0; i < words1.size(); i++) {
    std::string word1 = words1[i];
    std::string word2 = words2[i];
    if (!checkPlaceholder(placeholders1, word1, word2)) {
      return "-";
    }
    if (!checkPlaceholder(placeholders2, word2, word1)) {
      return "-";
    }
  }
  // std::cout << "placeholder 1:" << std::endl;
  // for (auto p: placeholders1) std::cout << p.first << ": " << p.second << std::endl;
  // std::cout << "placeholder 2:" << std::endl;
  // for (auto p: placeholders2) std::cout << p.first << ": " << p.second << std::endl;
  std::string result1, result2;
  for (unsigned i = 0; i < words1.size(); i++) {
    std::string word1 = words1[i];
    std::string word2 = words2[i];
    if (isPlaceholder(word1) && isPlaceholder(word2) && isPlaceholder(placeholders1[word1]) && isPlaceholder(placeholders2[word2])
      && !notSame(placeholders1, word1, word2) && !notSame(placeholders2, word2, word1))
    {
      result1 += "arbitrary ";
      result2 += "arbitrary ";
      continue;
    }
    if (isPlaceholder(word1)) {
      result1 += extractString(placeholders1[word1])[0] + " ";
    } else {
      result1 += word1 + " ";
    }
    if (isPlaceholder(word2)) {
      result2 += extractString(placeholders2[word2])[0] + " ";
    } else {
      result2 += word2 + " ";
    }
  }
  // std::cout << "content 1: " << result1 << std::endl;
  // std::cout << "content 2: " << result2 << std::endl;
  if (result1 != result2) {
    if (result1.find('<') == std::string::npos && result2.find('<') == std::string::npos) {
      // done, but they don't match
      return "-";
    }
    // std::cout << "call again." << std::endl;
    result1 = solve(result1, result2) + " ";
  }
  result1.pop_back();
  return result1;
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
