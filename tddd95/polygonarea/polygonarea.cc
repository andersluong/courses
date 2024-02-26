/**
* The problem is to calculate the area of a polygon given its points, and to determine the direction of the polygon.
* This uses the Shoelace formula to calculate the area of the polygon. The formula uses determinants between two points,
* and sum them together and divide by 2. The direction of the polygon is determined by the sign of the area.
* Time complexity is O(n) where n is the number of vertices.
*
* Source of inspiration: https://en.wikipedia.org/wiki/Shoelace_formula
* Author: Anders Luong
*/
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
class Point {
public:
  Point(T x, T y) : x(x), y(y) {};

  double distanceTo(const Point<T>& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
  }

  double determinant(const Point<T>& other) const {
    return x * other.y - y * other.x;
  }
private:
  T x, y;
};

double polygonArea(std::vector<Point<int>> const& vertices) {
  double area = 0; 
  for (unsigned i = 0; i < vertices.size() - 1; i++) {
    area += vertices[i].determinant(vertices[i + 1]);
  }

  area /= 2;
  return area;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  while (true) {
    int numberOfVertices;
    std::cin >> numberOfVertices;

    if (numberOfVertices == 0) {
      break;
    }

    std::vector<Point<int>> vertices;
    for (int i = 0; i < numberOfVertices; ++i) {
      int x, y;
      std::cin >> x >> y;
      vertices.push_back(Point<int>{x, y});
    }
    // Add the first vertex to the end of the vector to close the polygon
    vertices.push_back(vertices[0]);
    double area = polygonArea(vertices);

    if (area < 0) {
      std::cout << "CW " << std::fixed << std::setprecision(1) << -area << "\n";
    } else {
      std::cout << "CCW " << std::fixed << std::setprecision(1) << area << "\n";
    }
  }
}
