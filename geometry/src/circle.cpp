#include "../circle.h"
#include "../line.h"
#include "../segment.h"
#include "../vector.h"

geometry::Circle::Circle(const geometry::Point &other_point, int64_t other_radius)
    : point(other_point), radius(other_radius) {
}
geometry::IShape &geometry::Circle::Move(const geometry::Vector &other_vector) {
  point.Move(other_vector);
  return *this;
}
bool geometry::Circle::ContainsPoint(const geometry::Point &other_point) const {
  return (other_point - point).Length() <= radius * radius;
}
bool geometry::Circle::CrossesSegment(const geometry::Segment &other_segment) const {
  int64_t dist_segment = 0;
  int64_t tmp_rad = radius * radius;
  geometry::Vector vector_p = other_segment.p - point;
  geometry::Vector vector_q = other_segment.q - point;
  geometry::Vector vector = other_segment.q - other_segment.p;
  if (ScalarProduct(vector_p, vector) * ScalarProduct(vector_q, vector) >= 0) {
    if (ScalarProduct(vector_p, vector) > 0) {
      dist_segment = vector_p.Length();
    } else {
      dist_segment = vector_q.Length();
    }
  } else {
    dist_segment = VectorProduct(vector, vector_p);
    tmp_rad *= vector.Length();
  }
  if (dist_segment < 0) {
    dist_segment = -dist_segment;
  }
  bool first_point = ContainsPoint(other_segment.p);
  bool second_point = ContainsPoint(other_segment.q);
  bool first_point_inside = (other_segment.p - point).Length() < radius * radius;
  bool second_point_inside = (other_segment.q - point).Length() < radius * radius;
  bool near_point = dist_segment <= tmp_rad;
  if (first_point_inside && second_point_inside) {
    return false;
  }
  if ((first_point && !second_point) || (second_point && !first_point)) {
    return true;
  }
  return near_point;
}
geometry::IShape *geometry::Circle::Clone() const {
  auto *ptr = new geometry::Circle(point, radius);
  return ptr;
}
std::string geometry::Circle::ToString() const {
  std::string str = "Circle(";
  str += point.ToString();
  str += ", ";
  str += std::to_string(radius);
  str += ")";
  return str;
}