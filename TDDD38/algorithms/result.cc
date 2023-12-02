#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/* Expected output:

Highscore      | Fastest
Team D  : 37   | Team C
Team C  : 12   | Team B
Team B  : 5    | Team A

*/

string team_to_string(pair<string, int> const &team) {
  ostringstream oss{};
  oss << left << setw(8) << team.first << ": " << setw(4) << team.second;
  return oss.str();
}

int main() {
  vector<pair<string, int>> const results{
      {"Team C", 12},
      {"Team B", 5},
      {"Team A", 0},
      {"Team D", 37},
  };
  vector<pair<string, int>> highscore(3);

  // write your code here
  partial_sort_copy(
      results.begin(), results.end(), highscore.begin(), highscore.end(),
      [](pair<string, int> const &team1, pair<string, int> const &team2) {
        return team1.second > team2.second;
      });

  transform(highscore.begin(), highscore.end(), results.begin(),
            ostream_iterator<string>{cout, "\n"},
            [](pair<string, int> const &team1, pair<string, int> const &team2) {
              return team_to_string(team1);
            });
}
