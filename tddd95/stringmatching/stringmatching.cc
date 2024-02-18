/**
* Knuth-Moris-Pratt algorithm for string matching. 
* The algorithm is used to find the occurrences of a pattern in a text. By precomputing the longest prefix suffix (lps) array,
* we can save time by not rechecking the characters that we have already checked and know that they are a match.
* The time complexity of the algorithm is O(n + m) where n is the length of the text and m is the length of the pattern.
* The source of the implementation: https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
* Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <vector>

class KnuthMorisPratt {
public:
  // Instanstiate the class with the pattern and the text, and construct the lps array
  KnuthMorisPratt(std::string const p, std::string const t) : pattern{p}, text{t} {
    // preprocess the lps
    lps = std::vector<unsigned>(pattern.size(), 0);
    unsigned i = 0;
    unsigned len = 0;

    // first step
    lps[0] = 0;
    i++;

    // build the lps
    while (i < pattern.size()) {
      if (pattern[i] == pattern[len]) {
        len++;
        lps[i] = len;
        i++;
      } else if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }

  // Find the occurrences of the pattern in the text and return the indices of the occurrences
  std::vector<unsigned> find() {
    std::vector<unsigned> result;
    unsigned i = 0;
    unsigned j = 0;
    while (text.size() - i >= pattern.size() - j) {
      if (j == pattern.size()) {
        // found a pattern match at index i - j
        result.push_back(i - j);
        j = lps[j - 1];
        continue;
      } 
      if (text[i] == pattern[j]) {
        // we have a match
        i++;
        j++;
      } else if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
    return result;
  }

private:
  std::string pattern;
  std::string text;
  std::vector<unsigned> lps;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  std::string text, pattern;
  while (std::getline(std::cin, pattern) && std::getline(std::cin, text)) {
    // std::cout << "Pattern: " << pattern << " Text: " << text << "\n";
    KnuthMorisPratt kmp{pattern, text};
    std::vector<unsigned> result = kmp.find();
    for (unsigned i : result) {
      std::cout << i << " ";
    }
    std::cout << "\n";
  }
}

