#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

static const int INF = 1e9;

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

  std::string toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }
private:
  T x, y;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int numberOfTestCases;
  std::cin >> numberOfTestCases;

  for (int i = 0; i < numberOfTestCases; i++) {
    std::vector<Point<int>> innerPoints;
    std::vector<Point<int>> outerPoints;

    int numberOfInnerPoints;
    std::cin >> numberOfInnerPoints;
    for (int j = 0; j < numberOfInnerPoints; j++) {
      int x, y;
      std::cin >> x >> y;
      innerPoints.push_back(Point<int>(x, y));
    }

    int numberOfOuterPoints;
    std::cin >> numberOfOuterPoints;
    for (int j = 0; j < numberOfOuterPoints; j++) {
      int x, y;
      std::cin >> x >> y;
      outerPoints.push_back(Point<int>(x, y));
    }
    outerPoints.push_back(outerPoints[0]);

    double shortestDistance = INF;
    for (Point point : innerPoints) {
      for (unsigned lineIndex = 0; lineIndex < outerPoints.size() - 1; lineIndex++) {
        Point linePoint1 = outerPoints[lineIndex];
        Point linePoint2 = outerPoints[lineIndex + 1];
        // std::cout << "point: " << point.toString() << "\n";
        // std::cout << "line point 1: " << linePoint1.toString() << "\n";
        // std::cout << "line point 2: " << linePoint2.toString() << "\n";
        double distance = point.distanceToLine(linePoint1, linePoint2);
        // std::cout << "distance: " << distance << "\n";
        if (distance < shortestDistance) {
          shortestDistance = distance;
          // std::cout << "new shortest distance: " << shortestDistance << "\n";
        }
      }
    }
    // radius = diameter / 2
    std::cout << std::setprecision(8) << shortestDistance / 2.0 << "\n";
  }

}
