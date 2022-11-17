#include "../line.h"
#include "../point.h"
#include "../segment.h"
#include "../vector.h"

geometry::Line::Line(int64_t a0, int64_t b0, int64_t c0) : a(a0), b(b0), c(c0) {
}
geometry::Line::Line(const geometry::Point &p1, const geometry::Point &p2) {
  if (p1.y - p2.y == 0) {
    a = 0;
    b = 1;
    c = -p1.y;
    return;
  }
  if (p1.x - p2.x == 0) {
    a = 1;
    b = 0;
    c = -p1.x;
    return;
  }
  a = p1.y - p2.y;
  b = p2.x - p1.x;
  c = -(a * p1.x + b * p1.y);
}
geometry::IShape &geometry::Line::Move(const geometry::Vector &vec) {
  c -= a * vec.x + b * vec.y;
  return *this;
}
bool geometry::Line::ContainsPoint(const Point &point) const {
  return a * point.x + b * point.y + c == 0;
}
bool geometry::Line::CrossesSegment(const Segment &seg) const {
  return (a * seg.p.x + b * seg.p.y + c) * (a * seg.q.x + b * seg.q.y + c) <= 0;
}
geometry::IShape *geometry::Line::Clone() const {
  auto *ptr = new Line(a, b, c);
  return ptr;
}
std::string geometry::Line::ToString() const {
  std::string string;
  string += "Line(";
  string += std::to_string(a);
  string += ", ";
  string += std::to_string(b);
  string += ", ";
  string += std::to_string(c);
  string += ")";
  return string;
}
