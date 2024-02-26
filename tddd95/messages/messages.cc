#include <iostream>
#include <algorithm>
#include <vector>

struct Interval {
  int start;
  int end;

  bool operator<(Interval const& other) const {
    return end < other.end;
  }
};

int solve(std::vector<std::string> const& dictionary, std::string &message) {
  std::vector<Interval> intervals;
  for (std::string word : dictionary) {
    std::string::size_type start = message.find(word);
    while (start != std::string::npos) {
      Interval interval{ (int)start, (int)start + (int)word.size() - 1 };
      intervals.push_back(interval);
      start = message.find(word, start + 1);
    }
  }
  std::sort(intervals.begin(), intervals.end());

  int count = 0;
  int coveredEnd = -1;
  for (Interval interval : intervals) {
    if (interval.start > coveredEnd) {
      count++;
      coveredEnd = interval.end;
    }
  }

  return count;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  std::vector<std::string> dictionary;

  while (true) {
    std::string word;
    std::cin >> word;
    if (word == "#") {
      break;
    }
    dictionary.push_back(word);
  }

  std::string message;
  while (true) {
    std::string messagePart;
    std::cin >> messagePart;
    if (messagePart == "#") {
      break;
    }
    message += messagePart;
    if (message.back() == '|') {
      message.pop_back();
      int count = solve(dictionary, message);
      std::cout << count << "\n";
      message.clear();
    }
  }
}
