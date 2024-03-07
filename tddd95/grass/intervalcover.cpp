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
  double radius;
};

// read an interval from the terminal
Interval readInterval(int const index, double const grassWidth) {
  double position, radius;
  if (!(std::cin >> position >> radius)) {
    return Interval{ 0, 0, END_OF_INPUT, 0  };
  }
  double compensate = grassWidth / (2*radius);
  return Interval{ position - radius + compensate, position + radius - compensate, index, radius };
}

// solving a test case. Here is where the algorithm is implemented
bool solveTestcase() {
  std::vector<Interval> intervals;
  int numberOfIntervals;
  if (!(std::cin >> numberOfIntervals)) {
    return false;
  }
  double grassLength, grassWidth;
  std::cin >> grassLength >> grassWidth;

  for (int i = 0; i < numberOfIntervals; i++) {
    intervals.push_back(readInterval(i, grassWidth));
  }
  intervals.push_back(Interval{ INF, INF, numberOfIntervals, 0 });

  // sort on starting point
  auto comparator = [](Interval const& interval1, Interval const& interval2){
    if (interval1.lower == interval2.lower) {
      return interval1.upper > interval2.upper;
    }
    return interval1.lower < interval2.lower;
  };
  std::sort(intervals.begin(), intervals.end(), comparator);

  // init
  unsigned index = 0;
  int counter = 0;

  // main interval
  Interval mainInterval{ 0, grassLength, -1, 0 };
  // algorithm
  while (true) {
    // check if interval covers start
    if (intervals[index].lower > mainInterval.lower) {
      std::cout << "-1\n";
      return true;
    } 
    // find biggest covering of start, since they are ordered of start, just iterate until the 
    // last one covering start
    Interval biggestCovering{ mainInterval.lower, mainInterval.lower - 1, -1, 0 };
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
    counter++;

    // std::cout << "chosen: " << biggestCovering.lower << " " << biggestCovering.upper << "\n";

    // check if we are done
    if (biggestCovering.upper >= mainInterval.upper) {
      break;
    }
  }
  // found optimal solution, print it out
  std::cout << counter << "\n";
  // for (auto index : chosenIndexes) {
  //   std::cout << index << " ";
  // }
  // std::cout << "\n";

  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  while (solveTestcase()) {}
}
