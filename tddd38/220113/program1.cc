#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <tuple>
#include <vector>

using Event = std::tuple<int, int, std::string>;

namespace std {
// operator >>
std::istream &operator>>(std::istream &is, Event &event) {
  is >> std::get<0>(event) >> std::get<1>(event);
  std::getline(is, std::get<2>(event));
  return is;
}

// operator <<
ostream &operator<<(ostream &os, const Event &event) {
  os << std::setfill('0') << std::setw(2) << std::get<0>(event) << " to "
     << std::setw(2) << std::get<1>(event) << ": " << std::get<2>(event);
  return os;
}
} // namespace std

/*
  Expected output:

07 to 08:  Eat breakfast
08 to 10:  Go to morning lecture
10 to 12:  Study
12 to 13:  Eat lunch
13 to 15:  Afternoon lecture
15 to 17:  Lab work
17 to 18:  Go Home
18 to 19:  Eat dinner
18 to 22:  Relax
22 to 07:  Sleep

 */

int main() {
  // Events are sorted with respect to start hour. If two start
  // hours are equal then they are sorted by end hour in second
  // hand. If both start and end hour are equal then they are sorted
  // by description.

  auto scheduleComparator = [](const Event &event1, const Event &event2) {
    if (std::get<0>(event1) == std::get<0>(event2)) {
      if (std::get<1>(event1) == std::get<1>(event2)) {
        return std::get<2>(event1) < std::get<2>(event2);
      }
      return std::get<1>(event1) < std::get<1>(event2);
    }
    return std::get<0>(event1) < std::get<0>(event2);
  };

  // 1. Read all events from "first.txt" into a vector of Event
  //    called first_schedule.
  std::ifstream firstFile{"first.txt"};
  std::vector<Event> firstData{std::istream_iterator<Event>{firstFile},
                               std::istream_iterator<Event>{}};

  // 2. Sort first_schedule.
  std::sort(firstData.begin(), firstData.end(), scheduleComparator);

  // 3. Read all events from "second.txt" into a vector of Event
  //    called second_schedule.
  std::ifstream secondFile{"second.txt"};
  std::vector<Event> secondData{std::istream_iterator<Event>{secondFile},
                                std::istream_iterator<Event>{}};

  // 4. Sort second_schedule.
  std::sort(secondData.begin(), secondData.end(), scheduleComparator);

  // 5. Create a new vector of Event called combined_schedule.
  std::vector<Event> combined_schedule{};

  // 6. Copy first_schedule and second_schedule into
  //    combined_schedule in such a way that the events are sorted.
  std::copy(firstData.begin(), firstData.end(),
            std::back_inserter(combined_schedule));
  std::copy(secondData.begin(), secondData.end(),
            std::back_inserter(combined_schedule));

  std::sort(combined_schedule.begin(), combined_schedule.end(),
            scheduleComparator);

  // 7. Remove any duplicates from combined_schedule.
  auto removeDuplicates =
      std::unique(combined_schedule.begin(), combined_schedule.end());
  combined_schedule.erase(removeDuplicates, combined_schedule.end());

  // 8. Print each event in combined_schedule, one line per event.
  std::copy(combined_schedule.begin(), combined_schedule.end(),
            std::ostream_iterator<Event>{std::cout, "\n"});
}
