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

  T getX() const {
    return x;
  }

  T getY() const {
    return y;
  }
private:
  T x, y;
};

int insidePolygon(std::vector<Point<int>> const& vertices, Point<int> const& point) {
  bool inside = false;
  for (unsigned i = 0; i < vertices.size() - 1; i++) {
    Point point1 = vertices[i];
    Point point2 = vertices[i + 1];

    int minX = std::min(point1.getX(), point2.getX());
    int maxX = std::max(point1.getX(), point2.getX());
    int minY = std::min(point1.getY(), point2.getY());
    int maxY = std::max(point1.getY(), point2.getY());

    if (point.getX() < minX || point.getY() < minY || point.getY() > maxY) {
      // outside of this line
      continue;
    }

    if (point1.getY() != point2.getY()) {
      if ()
    } else {
      // edge case: if y is the same
      if (point.getX() == minX) {
        return 0;
      }
      if (point.getX() > minX && point.getX() <= maxX) {
        inside = !inside;
      }
      continue;
    }

    double xIntercept = (double)(point.getY() - point1.getY()) * (point2.getX() - point1.getX()) / (point2.getY() - point1.getY()) + point1.getX();
    if (point1.getX() == point2.getX() || point.getX() <= xIntercept) {
      inside = !inside;
    }
  }
  if (inside) {
    return 1;
  }
  return -1;
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

    int numberOfTestPoints;
    std::cin >> numberOfTestPoints;

    for (int i = 0; i < numberOfTestPoints; i++) {
      int x, y;
      std::cin >> x >> y;
      Point<int> testPoint{x, y};
      int result = insidePolygon(vertices, testPoint);
      switch (result) {
        case 1:
          std::cout << "in\n";
          break;
        case -1:
          std::cout << "out\n";
          break;
        case 0:
          std::cout << "on\n";
          break;
      }
    }

  }
}
