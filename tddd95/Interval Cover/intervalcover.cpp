#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>

const static int INF = std::numeric_limits<int>::max();
const static int END_OF_INPUT = -999;

struct Interval {
  double lower, upper;
  int index;
};

Interval readInterval(int i) {
  std::string input;
  if (!(std::cin >> input)) {
    return Interval{ 0, 0, END_OF_INPUT  };
  }
  double lower = std::stod(input);
  if (!(std::cin >> input)) {
    return Interval{ 0, 0, END_OF_INPUT };
  }
  double upper = std::stod(input);
  return Interval{ lower, upper, i };
}

bool solveTestcase() {
  Interval mainInterval{ readInterval(-1) };
  if (mainInterval.index == END_OF_INPUT) {
    return false;
  }

  // https://www.geeksforgeeks.org/minimum-number-of-intervals-to-cover-the-target-interval/
  std::vector<Interval> intervals;
  std::string input;
  std::cin >> input;
  int numberOfIntervals = std::stoi(input);
  for (int i = 0; i < numberOfIntervals; i++) {
    intervals.push_back(readInterval(i));
  }
  intervals.push_back(Interval{ INF, INF, numberOfIntervals });

  // sort on starting point
  auto comparator = [](Interval const& interval1, Interval const& interval2){ return interval1.lower < interval2.lower; };
  std::sort(intervals.begin(), intervals.end(), comparator);

  std::string chosenIndexes;
  double start = mainInterval.lower;
  double end = mainInterval.lower - 1;
  int count = 0;
  unsigned i = 0;
  // special case when no intervals cover start
  if (intervals[0].lower > start) {
    std::cout << "impossible\n";
    return true;
  }
  while (i < intervals.size()) {
    Interval interval = intervals[i];
    // std::cout << "interval: " << interval.lower << " " << interval.upper << std::endl;
    if (interval.lower <= start) {
      end = std::max(end, interval.upper);
      i++;
    } else {
      start = end;
      count++;
      chosenIndexes += std::to_string(intervals[i-1].index) + " ";
      // std::cout << chosenIndexes << std::endl;
      // std::cout << "interval: " << intervals[i-1].lower << " " << intervals[i-1].upper << std::endl;
      if (interval.lower > end || end >= mainInterval.upper) {
        break;
      }
    }
  }
  if (end < mainInterval.upper) {
    std::cout << "impossible\n";
    return true;
  }
  chosenIndexes.pop_back();
  std::cout << count << "\n";
  std::cout << chosenIndexes << "\n";

  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  while (solveTestcase()) {}
}
