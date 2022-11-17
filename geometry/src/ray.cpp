#include "../ray.h"
#include "../line.h"
#include "../segment.h"

geometry::Ray::Ray(const Point &other_point, const Vector &other_vector) : point(other_point), vector(other_vector) {
}
geometry::Ray::Ray(const geometry::Point &point1, const geometry::Point &point2) : Ray(point1, point2 - point1) {
}
geometry::IShape &geometry::Ray::Move(const geometry::Vector &vec) {
  point.Move(vec);
  return *this;
}
bool geometry::Ray::ContainsPoint(const geometry::Point &other_point) const {
  Vector other_vector = other_point - point;
  return vector.x * other_vector.y - vector.y * other_vector.x == 0 &&
         vector.x * other_vector.x + vector.y * other_vector.y >= 0;
}
bool geometry::Ray::CrossesSegment(const geometry::Segment &other_segment) const {
  Point other_point(point.x + vector.x, point.y + vector.y);
  Line other_line(point, other_point);
  Vector segment_vector = other_segment.q - other_segment.p;
  Vector seg_ray_vector = point - other_segment.p;
  return (point.CrossesSegment(other_segment)) ||
         ((other_line.CrossesSegment(other_segment)) &&
          (VectorProduct(segment_vector, seg_ray_vector) * VectorProduct(vector, segment_vector) >= 0));
}
geometry::IShape *geometry::Ray::Clone() const {
  auto *ptr = new Ray(point, vector);
  return ptr;
}
std::string geometry::Ray::ToString() const {
  std::string string;
  string += "Ray(";
  string += point.ToString();
  string += ", ";
  string += "Vector(";
  string += std::to_string(vector.x);
  string += ", ";
  string += std::to_string(vector.y);
  string += "))";
  return string;
}