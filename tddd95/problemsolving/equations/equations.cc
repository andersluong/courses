#include <iostream>
#include <vector>
#include <sstream>

// build up equation as Ax + By = C
struct Equation {
  int coefficientX;
  int coefficientY;
  int constant;
};

Equation parseEquation(std::string const& equation) {
  std::stringstream equationStream(equation);
  bool leftSide = true;
  Equation parsedEquation{0, 0, 0};
  std::string token;
  while (equationStream >> token) {
    if (token == "=") {
      leftSide = false;
      continue;
    }
    if (token == "+") {
      continue;
    }
    if (token[token.size() - 1] == 'x') {
      int neg = 1;
      if (!leftSide) {
        neg = -1;
      }
      if (token.size() == 1) {
        parsedEquation.coefficientX += 1 * neg;
      } else if (token.size() == 2 && token[0] == '-') {
        parsedEquation.coefficientX -= 1 * neg;
      } else {
        parsedEquation.coefficientX += std::stoi(token.substr(0, token.size() - 1)) * neg;
      }
    } else if (token[token.size() - 1] == 'y') {
      int neg = 1;
      if (!leftSide) {
        neg = -1;
      }
      if (token.size() == 1) {
        parsedEquation.coefficientY += 1 * neg;
      } else if (token.size() == 2 && token[0] == '-') {
        parsedEquation.coefficientY -= 1 * neg;
      } else {
        parsedEquation.coefficientY += std::stoi(token.substr(0, token.size() - 1)) * neg;
      }
    } else {
      int neg = 1;
      if (leftSide) {
        neg = -1;
      }
      parsedEquation.constant += std::stoi(token) * neg;
    }
  }
  return parsedEquation;
}

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

void simplestForm(int const a, int const b) {
  int g = gcd(a, b);
  int nom = a / g;
  int denom = b / g;
  if ((denom < 0 && nom < 0) || (denom < 0 && nom > 0)) {
    nom *= -1;
    denom *= -1;
  }
  if (denom == 1) {
    std::cout << nom << "\n";
    return;
  }
  std::cout << nom << "/" << denom << "\n";
}

int main() {
  int numberOfTestcases;
  std::cin >> numberOfTestcases;

  for (int i = 0; i < numberOfTestcases; i++) {
    std::string equation1, equation2;
    std::cin.ignore();
    std::getline(std::cin, equation1);
    std::getline(std::cin, equation2);

    Equation parsedEquation1 = parseEquation(equation1);
    Equation parsedEquation2 = parseEquation(equation2);

    std::cout << "Equation 1: " << parsedEquation1.coefficientX << "x + " << parsedEquation1.coefficientY << "y = " << parsedEquation1.constant << "\n";
    std::cout << "Equation 2: " << parsedEquation2.coefficientX << "x + " << parsedEquation2.coefficientY << "y = " << parsedEquation2.constant << "\n";

    // Equation 1: Ax + By = C; Equation 2: Dx + Ey = F;
    double det = parsedEquation1.coefficientX * parsedEquation2.coefficientY - parsedEquation1.coefficientY * parsedEquation2.coefficientX;
    if (det == 0) {

      if (parsedEquation1.coefficientX != 0 && parsedEquation2.coefficientY == 0 && parsedEquation1.coefficientY == 0) {
        double x = (double)parsedEquation1.constant / parsedEquation1.coefficientX;
        if (x * parsedEquation2.coefficientX == parsedEquation2.constant) {
          simplestForm(parsedEquation1.constant, parsedEquation1.coefficientX);
          std::cout << "don't know\n";
          std::cout << "\n";
          continue;
        }
      } else if (parsedEquation2.coefficientX != 0 && parsedEquation1.coefficientY == 0 && parsedEquation2.coefficientY == 0) {
        double x = (double)parsedEquation2.constant / parsedEquation2.coefficientX;
        if (x * parsedEquation1.coefficientX == parsedEquation1.constant) {
          simplestForm(parsedEquation2.constant, parsedEquation2.coefficientX);
          std::cout << "don't know\n";
          std::cout << "\n";
          continue;
        }
      } else if (parsedEquation1.coefficientY != 0 && parsedEquation2.coefficientX == 0 && parsedEquation1.coefficientX == 0) {
        double y = (double)parsedEquation1.constant / parsedEquation1.coefficientY;
        if (y * parsedEquation2.coefficientY == parsedEquation2.constant) {
          std::cout << "don't know\n";
          simplestForm(parsedEquation1.constant, parsedEquation1.coefficientY);
          std::cout << "\n";
          continue;
        }
      } else if (parsedEquation2.coefficientY != 0 && parsedEquation1.coefficientX == 0 && parsedEquation2.coefficientX == 0) {
        double y = (double)parsedEquation2.constant / parsedEquation2.coefficientY;
        if (y * parsedEquation1.coefficientY == parsedEquation1.constant) {
          std::cout << "don't know\n";
          simplestForm(parsedEquation2.constant, parsedEquation2.coefficientY);
          std::cout << "\n";
          continue;
        }
      }

      std::cout << "don't know\ndon't know\n";
      std::cout << "\n";
      continue;
    }

    int nomX = parsedEquation1.constant * parsedEquation2.coefficientY - parsedEquation1.coefficientY * parsedEquation2.constant;
    int nomY = parsedEquation1.coefficientX * parsedEquation2.constant - parsedEquation1.constant * parsedEquation2.coefficientX;

    simplestForm(nomX, det);
    simplestForm(nomY, det);
    std::cout << "\n";
  }
}
