#include <iostream>
#include <vector>

struct Interval {
  Interval() : lower{0}, upper{0}, coverage{0} {}
  Interval(double lower, double upper) : lower{lower}, upper{upper}, coverage{upper - lower} {}
  Interval(Interval const& other) : lower{other.lower}, upper{other.upper}, coverage{other.coverage} {}
  Interval& operator=(Interval const& other) {
    lower = other.lower;
    upper = other.upper;
    coverage = other.coverage;
    return *this;
  }

  // function called from mainInterval
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

  double lower, upper, coverage;
};

Interval readInterval() {
  std::string input;
  std::cin >> input;
  double lower = std::stoi(input);
  std::cin >> input;
  double upper = std::stoi(input);
  return Interval{ lower, upper };
}

Interval findLargestCoveringInterval(Interval const& mainInterval, std::vector<Interval> const& intervals) {
  Interval largestCoveringInterval;
  double covered = 0;
  for (auto interval : intervals) {
   if (interval.distanceCovered(mainInterval) > covered) {
     covered = interval.distanceCovered(mainInterval);
     largestCoveringInterval = interval;
   }
  }
  return largestCoveringInterval;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  Interval mainInterval{ readInterval() };

  std::vector<Interval> intervals;
  std::string input;
  std::cin >> input;
  double numberOfIntervals = std::stoi(input);
  for (double i = 0; i < numberOfIntervals; i++) {
    intervals.push_back(readInterval());
  }
  

}
