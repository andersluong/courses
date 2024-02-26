#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

struct Literal {
  int variable;
  bool isNegated;
};

using clausesType = std::vector<std::vector<Literal>>;

bool isClauseSatisfiable(std::vector<Literal> const& clause, int const assignment) {
  for (Literal literal : clause) {
    int value = (assignment >> (literal.variable - 1)) & 1;
    if (literal.isNegated) {
      // negation
      if (!value) {
        // this clause is satisfied
        return true;
      }
    } else {
      if (value) {
        // this clause is satisfied
        return true;
      }
    }
  }
  return false;
}

bool isSatisfiable(clausesType const& clauses, int const assignment) {
  for (auto clause : clauses) {
    if (!isClauseSatisfiable(clause, assignment)) {
      return false;
    }
  }
  return true;
}

void solve(clausesType const& clauses, int const numberOfVariables) {
  // for (auto clause : clauses) {
  //   for (auto literal : clause) {
  //     std::cout << literal << " ";
  //   }
  //   std::cout << "\n";
  // }
  for (int assignment = 0; assignment < std::exp2(numberOfVariables); assignment++) {
    if (isSatisfiable(clauses, assignment)) {
      std::cout << "satisfiable\n";
      return;
    }
  }
  std::cout << "unsatisfiable\n";
}

int main() {
  int numberOfTestCases;
  std::cin >> numberOfTestCases;

  for (int i = 0; i < numberOfTestCases; i++) {
    int numberOfVariables, numberOfClauses;
    std::cin >> numberOfVariables >> numberOfClauses;
    std::cin.ignore();

    clausesType clauses;

    for (int j = 0; j < numberOfClauses; j++) {
      std::vector<Literal> clause;
      std::string input;
      std::getline(std::cin, input);
      std::istringstream iss(input);
      std::string input2;
      while (iss >> input2) {
        if (input2 == "v") {
          // no need to store the OR token
          continue;
        }

        Literal literal;
        if (input2[0] == '~') {
          literal.isNegated = true;
          literal.variable = std::stoi(input2.substr(2));
        } else {
          literal.isNegated = false;
          literal.variable = std::stoi(input2.substr(1));
        }

        clause.push_back(literal);
      }
      clauses.push_back(clause);
    }

    solve(clauses, numberOfVariables);
  }
}
