#pragma once

#include <algorithm>
#include <cmath>
#include <compare>
#include <iostream>
#include <numeric>
#include <optional>
#include <ranges>
#include <variant>
#include <vector>

struct Vector3d {
  double x = 0, y = 0, z = 0;

  Vector3d &operator*=(double factor) {
    x *= factor;
    y *= factor;
    z *= factor;
    return *this;
  }

  Vector3d operator*(double factor) const {
    Vector3d copy = *this;
    copy *= factor;
    return copy;
  }

  Vector3d &operator/=(double factor) {
    x /= factor;
    y /= factor;
    z /= factor;
    return *this;
  }

  Vector3d operator/(double factor) const {
    Vector3d copy = *this;
    copy /= factor;
    return copy;
  }

  Vector3d &operator+=(const Vector3d &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  Vector3d operator+(Vector3d other) const {
    Vector3d copy = *this;
    copy += other;
    return copy;
  }

  Vector3d &operator-=(const Vector3d &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  Vector3d operator-(const Vector3d &other) const {
    Vector3d copy = *this;
    copy -= other;
    return copy;
  }

  Vector3d operator-() const { return {-x, -y, -z}; }

  bool operator==(const Vector3d &other) const = default;

  auto operator<=>(const Vector3d &other) const = default;

  [[nodiscard]] double length() const {
    return std::sqrt(x * x + y * y + z * z);
  }

  friend std::istream &operator>>(std::istream &in, Vector3d &vector) {
    return in >> vector.x >> vector.y >> vector.z;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector3d &vector) {
    return out << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
  }
};

Vector3d cross(const Vector3d &left, const Vector3d &right) {
  // https://en.wikipedia.org/wiki/Cross_product
  return {
    .x = left.y * right.z - left.z * right.y,
    .y = left.z * right.x - left.x * right.z,
    .z = left.x * right.y - left.y * right.x,
  };
}

auto dot(const Vector3d &left, const Vector3d &right) {
  // https://en.wikipedia.org/wiki/Dot_product
  return left.x * right.x + left.y * right.y + left.z * right.z;
}

bool almost_equal(double left, double right) {
  return std::abs(right - left) < 0.00000000001;
}

auto sin(const Vector3d &left, const Vector3d &right) {
  return cross(left, right) / (left.length() * right.length());
}

auto cos(const Vector3d &left, const Vector3d &right) {
  return dot(left, right) / (left.length() * right.length());
}

auto distance(const Vector3d &p1, const Vector3d p2) {
  return (p1 - p2).length();
}

struct Line {
  Vector3d direction;
  Vector3d point;

  bool operator==(const Line &other) const = default;
};

struct Plane {
  Vector3d normal;
  Vector3d point;

  bool operator==(const Plane &other) const = default;
};

struct Segment {
  Vector3d begin, end;

  [[nodiscard]] Line line() const {
    return {.direction = end - begin, .point = end};
  }

  [[nodiscard]] auto length() const { return (end - begin).length(); }

  bool operator==(const Segment &other) const = default;
};

struct Parallelogram {
  Vector3d a, b, c, d;

  Parallelogram(Vector3d a, Vector3d b, Vector3d c)
      : a(a), b(b), c(c), d(c + (a - b)) {}

  [[nodiscard]] Plane plane() const {
    return {.normal = cross(b - a, c - a), .point = a};
  }

  [[nodiscard]] std::vector<Segment> sides() const {
    return {{a, b}, {b, c}, {c, d}, {d, a}};
  }

  bool operator==(const Parallelogram &other) const = default;
};

struct Parallelepiped {
  Parallelogram top;
  Parallelogram bottom;

  Parallelepiped(Vector3d a1, Vector3d b1, Vector3d c1, Vector3d a2)
      : top(a1, b1, c1),
        bottom(a1 + (a2 - a1), b1 + (a2 - a1), c1 + (a2 - a1)) {}

  [[nodiscard]] std::vector<Parallelogram> sides() const {
    return {
      top,
      bottom,
      {top.a, top.b, bottom.b},
      {top.b, top.c, bottom.c},
      {top.c, top.d, bottom.d},
      {top.d, top.a, bottom.a}};
  }

  bool operator==(const Parallelepiped &other) const = default;
};

std::optional<Vector3d>
planeLineIntersection(const Plane &plane, const Line &line) {
  // https://cyclowiki.org/wiki/Точка_пересечения_прямой_и_плоскости
  if (dot(line.direction, plane.normal) == 0) return std::nullopt;
  auto D = dot(plane.normal, plane.point);
  return line.point - line.direction * ((dot(line.point, plane.normal) + D) /
                                        dot(line.direction, plane.normal));
}

bool lineBelongsToPlane(const Plane &plane, const Line &line) {
  auto point = line.point;
  if (point == plane.point) point += line.direction;
  return almost_equal(0, cos(plane.normal, line.direction)) and
         almost_equal(0, cos(plane.normal, plane.point - point));
}

bool pointBelongsToParallelogram(
  const Parallelogram &par, const Vector3d &point
) {
  // relative = n * e1 + m * e2
  // n, m should be in [0; 1]
  auto relative = point - par.a;
  auto e1 = par.d - par.a;
  auto e2 = par.b - par.a;
  auto n = dot(e1, relative) / e1.length();
  auto m = dot(e2, relative) / e2.length();
  return (0 <= n and n <= 1) and (0 <= m and m <= 1);
}

bool pointBelongsToSegment(const Segment &segment, const Vector3d &point) {
  return almost_equal(
    segment.length(),
    distance(segment.begin, point) + distance(segment.end, point)
  );
}

bool segmentIntersectParallelogram(
  const Parallelogram &par, const Segment &segment
) {
  if (lineBelongsToPlane(par.plane(), segment.line()))
    return pointBelongsToParallelogram(par, segment.begin) or
           pointBelongsToParallelogram(par, segment.end);
  auto crossPoint = planeLineIntersection(par.plane(), segment.line());
  return crossPoint.has_value() and
         pointBelongsToSegment(segment, crossPoint.value()) and
         pointBelongsToParallelogram(par, crossPoint.value());
}

bool parallelogramIntersectParallelogram(
  const Parallelogram &p1, const Parallelogram &p2
) {
  return std::ranges::any_of(p2.sides(), [&](auto &x) {
    return segmentIntersectParallelogram(p1, x);
  });
}

bool parallelepipedIntersectParallelepiped(
  const Parallelepiped &p1, const Parallelepiped &p2
) {
  for (const auto &side1 : p1.sides())
    for (const auto &side2 : p2.sides())
      if (parallelogramIntersectParallelogram(side1, side2)) return true;
  return false;
}
