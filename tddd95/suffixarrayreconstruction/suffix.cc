#include <iostream>
#include <set>

struct Suffix {
  std::string start;
  std::string end;
  int asterickIndex;
};

bool containsAtIndex(std::vector<std::string> const& container, int const index) {
  return container[index] != "";
}

Suffix splitAsterick(std::string const& input) {
  int asterickIndex = input.find('*');
  if (asterickIndex == std::string::npos) {
    return Suffix{ input, "", -1 };
  }
  return Suffix{ input.substr(0, asterickIndex), input.substr(asterickIndex + 1), asterickIndex };
}

bool isValid(Suffix const& currentSuffix, Suffix const& newSuffix) {
  if (currentSuffix.start.length() < newSuffix.start.length()) {
    if (currentSuffix.start != newSuffix.start.substr(0, currentSuffix.start.length())) {
      return false;
    }
  } else {
    if (currentSuffix.start.substr(0, newSuffix.start.length()) != newSuffix.start) {
      return false;
    }
  }
  if (currentSuffix.end.length() < newSuffix.end.length()) {
    if (currentSuffix.end != newSuffix.end.substr(newSuffix.end.length() - currentSuffix.end.length())) {
      return false;
    }
  } else {
    if (currentSuffix.end.substr(currentSuffix.end.length() - newSuffix.end.length()) != newSuffix.end) {
      return false;
    }
  }
  return true;
}

void solve(std::vector<std::string> const& suffixes, std::string const& initString) {
  std::vector<std::string> possibleStrings{ initString };

  for (int index = 0; index < suffixes.size(); index++) {
    std::string suffix = suffixes[index];
    if (suffix == "") {
      continue;
    }
    Suffix currentSuffix = splitAsterick(suffix);
    std::vector<std::string> newPossibleStrings;
    for (auto it = possibleStrings.begin(); it != possibleStrings.end(); it++) {
      std::string possibleString = *it;
      std::string newString = possibleString;
      bool isValid = true;
      bool hasAsterick = currentSuffix.asterickIndex != -1;
      if (hasAsterick) {
        for (int i = currentSuffix.asterickIndex + currentSuffix.end.length() - 1; i >= currentSuffix.asterickIndex; i--) {
          if (newString[i] == '#' || newString[i] == suffix[i]) {
            // OK to replace
            newString[i] = suffix[i];
          } else {
            // invalid option
            isValid = false;
            break;
          }
        }
        if (!isValid) {
          continue;
        }
        // TODO: add possible strings


      } else {
        for (int i = currentSuffix.start.length() - 1; i >= index; i--) {
          if (newString[i] == '#' || newString[i] == suffix[i]) {
            // OK to replace
            newString[i] = suffix[i];
          } else {
            // invalid option
            possibleStrings.erase(possibleString);
            continue;
          }
        }
      }
      // TODO: update current possible string

    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int numberOfTestCases;
  std::cin >> numberOfTestCases;

  for (int i = 0; i < numberOfTestCases; i++) {
    int outputLength, numberOfSuffixes;
    std::cin >> outputLength >> numberOfSuffixes;

    std::vector<std::string> suffixes(outputLength);
    for (int j = 0; j < numberOfSuffixes; j++) {
      int index;
      std::string suffix;
      std::cin >> index >> suffix;
      if (containsAtIndex(suffixes, index)) {
        // need to check if they are the same
        Suffix currentSuffix = splitAsterick(suffixes[index]);
        Suffix newSuffix = splitAsterick(suffix);
        if (isValid(currentSuffix, newSuffix)) {
          suffixes[index] = currentSuffix.asterickIndex == -1 ? suffix : suffixes[index];
        } else {
          // invalid option, break early
          std::cout << "IMPOSSIBLE\n";
          break;
        }
      }
    }

    std::string initString(outputLength, '#');
    solve(suffixes, initString);
  }
}
