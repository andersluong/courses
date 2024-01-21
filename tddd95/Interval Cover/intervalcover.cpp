#include <iostream>
#include <vector>
#include <array>
#include <limits>

const int infinity = std::numeric_limits<int>::max();

struct Interval {
  Interval() : lower{infinity}, upper{-infinity}, coverage{} {}
  Interval(double lower, double upper) : lower{lower}, upper{upper}, coverage{upper - lower} {}
  Interval(Interval const& other) : lower{other.lower}, upper{other.upper}, coverage{other.coverage} {}
  Interval& operator=(Interval const& other) {
    lower = other.lower;
    upper = other.upper;
    coverage = other.coverage;
    return *this;
  }

  double lower, upper, coverage;
};

struct MainInterval : public Interval {

  double distanceCovered(Interval const& other) const {
    if (other.lower <= lower && other.upper >= upper) {
      // full coverage
      return coverage;
    } else if (other.lower <= lower && other.upper <= lower) {
      // overlapping from left
      return other.upper - lower;
    } else if (other.lower >= lower && other.upper >= upper) {
      // overlapping from right
      return upper - other.lower;
    } else if (other.lower >= lower && other.upper <= upper) {
      // inside of the interval
      return other.coverage;
    } else {
      // no coverage
      return 0;
    }
  }

  bool isFullyCovered(std::vector<Interval> const& intervals) const {
    // std::cout << "checking if fully covered\n";
    // for (auto interval : intervals) {
    //   std::cout << "interval: " << interval.lower << " " << interval.upper << "\n";
    // }
    // std::cout << "main interval: " << lower << " " << upper << "\n";
    double lowerBound = infinity;
    double upperBound = -infinity;
    for (auto interval : intervals) {
      if (interval.lower < lowerBound) {
        lowerBound = interval.lower;
      } 
      if (interval.upper > upperBound) {
        upperBound = interval.upper;
      }
    }
    // std::cout << "lower bound: " << lowerBound << ". upper bound: " << upperBound << "\n";
    if (lowerBound <= lower && upperBound >= upper) {
      return true;
    }
    return false;
  }
};

int findLargestCoveringInterval(MainInterval const& mainInterval, std::array<Interval, 20000> const& intervals, int numberOfIntervals) {
  int largestCoveringIntervalIndex{-1};
  double covered{};
  for (int i = 0; i < numberOfIntervals; i++) {
    if (intervals[i].lower == infinity) {
      // interval has been removed
      continue;
    }
    double currentCovered = mainInterval.distanceCovered(intervals[i]);
    if (currentCovered > covered) {
        covered = currentCovered;
        largestCoveringIntervalIndex = i;
    }
  }
  return largestCoveringIntervalIndex;
}

Interval readInterval() {
  std::string input;
  if (!(std::cin >> input)) {
    return Interval{};
  }
  double lower = std::stod(input);
  if (!(std::cin >> input)) {
    return Interval{};
  }
  double upper = std::stod(input);
  return Interval{ lower, upper };
}

bool solveTestcase() {
  MainInterval mainInterval{ readInterval() };
  if (mainInterval.lower == INT_MAX) {
    return false;
  }

  std::array<Interval, 20000> intervals;
  std::string input;
  std::cin >> input;
  int numberOfIntervals = std::stoi(input);
  for (int i = 0; i < numberOfIntervals; i++) {
    intervals[i] = readInterval();
  }

  // special case when lower and upper are the same
  if (mainInterval.lower == mainInterval.upper) {
    for (int i = 0; i < numberOfIntervals; i++) {
      Interval interval = intervals[i];
      if (interval.lower <= mainInterval.lower && interval.upper >= mainInterval.upper) {
        std::cout << "1\n" << i << "\n";
        return true;
      }
    }
    std::cout << "impossible\n";
    return true;
  }

  std::string chosenIndexes;
  std::vector<Interval> chosenIntervals;
  while (!mainInterval.isFullyCovered(chosenIntervals)) {
    int largestCoveringIntervalIndex = findLargestCoveringInterval(mainInterval, intervals, numberOfIntervals);
    if (largestCoveringIntervalIndex == -1) {
      std::cout << "impossible\n";
      return true;
    }
    Interval largestCoveringInterval = intervals[largestCoveringIntervalIndex];
    intervals[largestCoveringIntervalIndex] = Interval{}; // remove interval from list
    // std::cout << "current largest interval: " << largestCoveringInterval.lower << " " << largestCoveringInterval.upper << "\n";
    chosenIntervals.push_back(largestCoveringInterval);
    chosenIndexes += std::to_string(largestCoveringIntervalIndex) + " ";
  }
  std::cout << chosenIntervals.size() << "\n";
  std::cout << chosenIndexes << "\n";
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  while (solveTestcase()) {}
}
