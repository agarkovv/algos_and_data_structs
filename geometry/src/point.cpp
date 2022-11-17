#include "../point.h"
#include "../segment.h"
#include "../vector.h"
#include <string>
#include <iostream>

geometry::Point::Point(int64_t x0, int64_t y0) : x(x0), y(y0) {
}
geometry::Point::Point(const geometry::Point &other) : x(other.x), y(other.y) {
}
geometry::IShape &geometry::Point::Move(const Vector &vec) {
  x += vec.x;
  y += vec.y;
  return *this;
}
bool geometry::Point::ContainsPoint(const geometry::Point &point) const {
  return x == point.x && y == point.y;
}
bool geometry::Point::CrossesSegment(const geometry::Segment &seg) const {
  Vector vector1 = *this - seg.p;
  Vector vector2 = seg.q - *this;
  return VectorProduct(vector1, vector2) == 0 && ScalarProduct(vector1, vector2) >= 0;
}
geometry::IShape *geometry::Point::Clone() const {
  auto *ptr = new Point(x, y);
  return ptr;
}
std::string geometry::Point::ToString() const {
  std::string string;
  string += "Point(";
  string += std::to_string(x);
  string += ", ";
  string += std::to_string(y);
  string += ")";
  return string;
}

geometry::Point &geometry::Point::operator=(const geometry::Point &other) {
  x = other.x;
  y = other.y;
  return *this;
}

geometry::Vector operator-(const geometry::Point &p1, const geometry::Point &p2) {
  geometry::Vector vec;
  vec.x = p1.x - p2.x;
  vec.y = p1.y - p2.y;
  return vec;
}