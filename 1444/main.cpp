#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

namespace {
struct Point {
  int x, y;
  int index;
};

int SquaredLength(const Point& point) {
  return (point.x * point.x) + (point.y * point.y);
}

int DotProduct(const Point& point_a, const Point& point_b) {
  return (point_a.x * point_b.x) + (point_a.y * point_b.y);
}

int CrossProduct(const Point& point_a, const Point& point_b) {
  return (point_a.x * point_b.y) - (point_a.y * point_b.x);
}

bool AreCollinear(const Point& point_a, const Point& point_b) {
  return CrossProduct(point_a, point_b) == 0;
}

}  // namespace

int main() {
  int number_of_points = 0;
  std::cin >> number_of_points;

  std::vector<Point> points(number_of_points);

  for (int i = 0; i < number_of_points; i++) {
    std::cin >> points[i].x;
    std::cin >> points[i].y;
    points[i].index = i;
  }

  for (int i = 1; i <= number_of_points; i++) {
    // Translate everything towards the first point
    points[i].x -= points[0].x;
    points[i].y -= points[0].y;
  }

  // now first point is in 0.0
  points[0].x = 0;
  points[0].y = 0;

  std::sort(points.begin() + 1, points.end(), [](const Point& point_a, const Point& point_b) {
    // Points with the same angle are sorted outwards
    if (AreCollinear(point_a, point_b) && DotProduct(point_a, point_b) >= 0) {
      return SquaredLength(point_a) < SquaredLength(point_b);
    }

    // atan2 is a function of how "left" the vectors are pointing
    // when we sort it like this we scan it from left to right
    return atan2(point_a.y, point_a.x) < atan2(point_b.y, point_b.x);
  });

  int start_index = 0;
  for (int i = 0; i < number_of_points - 1; i++) {
    Point current_point = points[i];
    Point next_point = points[i + 1];

    bool is_clockwise = CrossProduct(current_point, next_point) < 0;
    bool is_pointing_back = DotProduct(current_point, next_point) < 0;
    // Opposite turn, start at that point instead
    if (is_clockwise || AreCollinear(current_point, next_point) && is_pointing_back) {
      start_index = i;
      break;
    }
  }

  std::cout << number_of_points << '\n';

  std::cout << (points[0].index + 1) << '\n';
  for (int i = start_index; i < start_index + number_of_points - 1; i++) {
    std::cout << (points[(i % (number_of_points - 1)) + 1].index + 1) << '\n';
  }

  return 0;
}
