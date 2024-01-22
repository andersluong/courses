/**
* Using greedy algorithm to solve the interval cover problem.
* The algorithm is as follow:
* Sort the intervals on their starting point, then iterate through them until start isn't covered. Out of those
* that are iterated, find the biggest covering area. Pick this one, and repeat until the end is covered.
*
* Source of inspiration: https://www.geeksforgeeks.org/minimum-number-of-intervals-to-cover-the-target-interval/
* 
* Author: Anders Luong (andlu434)
*/
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// constants
const static int INF = std::numeric_limits<int>::max();
const static int END_OF_INPUT = -999;

// Interval containing [lower, upper] and the index of the interval
struct Interval {
  double lower, upper;
  int index;
};

// read an interval from the terminal
Interval readInterval(int const index) {
  double lower, upper;
  if (!(std::cin >> lower >> upper)) {
    return Interval{ 0, 0, END_OF_INPUT  };
  }
  return Interval{ lower, upper, index };
}

// solving a test case. Here is where the algorithm is implemented
bool solveTestcase() {
  Interval mainInterval{ readInterval(-1) };
  if (mainInterval.index == END_OF_INPUT) {
    return false;
  }

  std::vector<Interval> intervals;
  int numberOfIntervals;
  std::cin >> numberOfIntervals;
  for (int i = 0; i < numberOfIntervals; i++) {
    intervals.push_back(readInterval(i));
  }
  intervals.push_back(Interval{ INF, INF, numberOfIntervals });

  // sort on starting point
  auto comparator = [](Interval const& interval1, Interval const& interval2){ return interval1.lower < interval2.lower; };
  std::sort(intervals.begin(), intervals.end(), comparator);

  // init
  std::vector<int> chosenIndexes;
  unsigned index = 0;

  // algorithm
  while (true) {
    // check if interval covers start
    if (intervals[index].lower > mainInterval.lower) {
      std::cout << "impossible\n";
      return true;
    } 
    // find biggest covering of start, since they are ordered of start, just iterate until the 
    // last one covering start
    Interval biggestCovering{ mainInterval.lower, mainInterval.lower - 1, -1 };
    for (unsigned i = index; i < intervals.size(); i++) {
      if (intervals[index].lower <= mainInterval.lower) {
        if (intervals[index].upper > biggestCovering.upper) {
          // found a better option
          biggestCovering = intervals[index];
        }
        index++;
      } else {
        break;
      }
    }

    // update state
    mainInterval.lower = biggestCovering.upper;
    chosenIndexes.push_back(biggestCovering.index);

    // check if we are done
    if (biggestCovering.upper >= mainInterval.upper) {
      break;
    }
  }
  // found optimal solution, print it out
  std::cout << chosenIndexes.size() << "\n";
  for (auto index : chosenIndexes) {
    std::cout << index << " ";
  }
  std::cout << "\n";

  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  while (solveTestcase()) {}
}
