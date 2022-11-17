#include "../segment.h"
#include "../vector.h"
#include "../line.h"
#include <string>

geometry::Segment::Segment(const Point &point1, const Point &point2) : p(point1), q(point2) {
}
geometry::IShape &geometry::Segment::Move(const Vector &vec) {
  p.Move(vec);
  q.Move(vec);
  return *this;
}
bool geometry::Segment::ContainsPoint(const geometry::Point &point) const {
  return point.CrossesSegment(*this);
}
bool geometry::Segment::CrossesSegment(const geometry::Segment &seg) const {
  Line line1(seg.p, seg.q);
  Line line2(p, q);
  bool crossed_by_line = line1.CrossesSegment(*this) && line2.CrossesSegment(seg);
  return crossed_by_line && Intersect(p.x, q.x, seg.p.x, seg.q.x) && Intersect(p.y, q.y, seg.p.y, seg.q.y);
}
geometry::IShape *geometry::Segment::Clone() const {
  auto *ptr = new Segment(p, q);
  return ptr;
}
std::string geometry::Segment::ToString() const {
  std::string ans = "Segment(";
  std::string str1 = p.ToString();
  std::string str2 = q.ToString();
  ans += str1 + ", " + str2 + ")";
  return ans;
}
geometry::Segment &geometry::Segment::operator=(const geometry::Segment &other) {
  p = other.p;
  q = other.q;
  return *this;
}
bool Intersect(int64_t a, int64_t b, int64_t c, int64_t d) {
  if (a > b) {
    std::swap(a, b);
  }
  if (c > d) {
    std::swap(c, d);
  }
  int64_t max = (a > c ? a : c);
  int64_t min = (b < d ? b : d);
  return max <= min;
}