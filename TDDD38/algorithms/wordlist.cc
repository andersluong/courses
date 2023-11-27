#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
  vector<string> words{istream_iterator<string>{cin},
                       istream_iterator<string>{}};
  vector<string> items{words};
  sort(begin(words), end(words));
  words.erase(unique(words.begin(), words.end()), words.end());
  transform(words.begin(), words.end(), ostream_iterator<string>{cout, "\n"},
            [&items](string current) {
              int amount = count(items.begin(), items.end(), current);
              return current + ": " + to_string(amount);
            });
  return 0;
}
