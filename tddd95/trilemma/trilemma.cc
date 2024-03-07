/**
* The problem is to calculate the area of a polygon given its points, and to determine the direction of the polygon.
* This uses the Shoelace formula to calculate the area of the polygon. The formula uses determinants between two points,
* and sum them together and divide by 2. The direction of the polygon is determined by the sign of the area.
* Time complexity is O(n) where n is the number of vertices.
*
* Source of inspiration: https://en.wikipedia.org/wiki/Shoelace_formula
* Author: Anders Luong
*/
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

  // Given a line defined by two points, returns the distance from this point to the line
  double distanceToLine(const Point<T>& point1, Point<T>& point2) {
    // https://stackoverflow.com/questions/52468343/finding-shortest-distance-between-a-point-and-a-line-segment
    // Line
    T x1 = point1.x;
    T y1 = point1.y;
    T x2 = point2.x;
    T y2 = point2.y;
    if ((x1 - x2) * (x - x2) + (y1 - y2) * (y - y2) <= 0) {
      return distanceTo(point2);
    }
    if ((x2 - x1) * (x - x1) + (y2 - y1) * (y - y1) <= 0) {
      return distanceTo(point1);
    }
    double nominator = std::abs((x2 - x1) * (y1 - y) - (x1 - x) * (y2 - y1));
    double denominator = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return nominator / denominator;
  }

  double distanceLength(const Point<T>& other) const {
    return std::abs(x - other.x) + std::abs(y - other.y);
  }


  std::string toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
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

std::vector<double> getTriangleAngles(std::vector<Point<int>> const& points) {
  double a = points[0].distanceTo(points[2]);
  double b = points[1].distanceTo(points[2]);
  double c = points[0].distanceTo(points[1]);

  double angleA = std::acos((a * a + c * c - b * b) / (2 * a * c));
  double angleB = std::acos((a * a + b * b - c * c) / (2 * a * b));
  double angleC = std::acos((b * b + c * c - a * a) / (2 * b * c));

  angleA = angleA * 180 / M_PI;
  angleB = angleB * 180 / M_PI;
  angleC = angleC * 180 / M_PI;

  return {angleA, angleB, angleC};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int numberOfTestCases;
  std::cin >> numberOfTestCases;

  for (int i = 1; i <= numberOfTestCases; i++) {
    std::cout << "Case #" << i << ": ";
    std::vector<Point<int>> triangle;

    for (int j = 0; j < 3; j++) {
      int x, y;
      std::cin >> x >> y;
      triangle.push_back(Point<int>{x, y});
    }
    triangle.push_back(triangle[0]);
    double area = polygonArea(triangle);

    if (area == 0) {
      std::cout << "not a triangle\n";
      continue;
    }
    auto angles = getTriangleAngles(triangle);
    std::string type = "scalene";
    if (angles[0] == angles[1] || angles[1] == angles[2] || angles[0] == angles[2]) {
      type = "isosceles";
    }
    std::string form = "acute";
    for (auto angle : angles) {
      // std::cout << "angle: " << angle << "\n";
      if (angle <= 90 + 1e-9 && angle >= 90 - 1e-9) {
        form =  "right";
        break;
      } else if (angle > 90) {
        form = "obtuse";
        break;
      }
    }
    std::cout << type << " " << form << " triangle\n";
  }
}
