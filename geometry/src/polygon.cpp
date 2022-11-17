#include "../polygon.h"
#include "../point.h"
#include "../segment.h"
#include "../ray.h"
#include "../line.h"

geometry::Polygon::Polygon(const std::vector<Point> &vector) : polygon(vector) {
}
geometry::Polygon::Polygon(const Polygon &other) : polygon(other.polygon) {
}
geometry::Polygon::Polygon(const Polygon &&other) : polygon(std::move(other.polygon)) {
}
geometry::IShape &geometry::Polygon::Move(const Vector &vector) {
  for (size_t i = 0; i < polygon.size(); ++i) {
    polygon[i].Move(vector);
  }
  return *this;
}
bool geometry::Polygon::ContainsPoint(const geometry::Point &point) const {
  int64_t counter = 0;
  Point infinite(100001, point.y + 1);
  geometry::Ray ray(point, infinite);
  for (size_t i = 0; i < polygon.size() - 1; ++i) {
    if (Segment(polygon[i], polygon[i + 1]).ContainsPoint(ray.point)) {
      return true;
    }
    if (ray.CrossesSegment(Segment(polygon[i], polygon[i + 1]))) {
      ++counter;
    }
  }
  if (ray.CrossesSegment(Segment(polygon[0], polygon[polygon.size() - 1]))) {
    ++counter;
  }
  return counter % 2 == 1;
}
bool geometry::Polygon::CrossesSegment(const geometry::Segment &segment) const {
  bool inside = true;
  for (size_t i = 0; i < polygon.size() - 1; ++i) {
    if (segment.CrossesSegment({polygon[i], polygon[i + 1]})) {
      return inside;
    }
    if (segment.CrossesSegment({polygon[polygon.size() - 1], polygon[0]})) {
      return inside;
    }
  }
  return !inside;
}
geometry::IShape *geometry::Polygon::Clone() const {
  IShape *new_polygon = new Polygon(polygon);
  return new_polygon;
}
std::string geometry::Polygon::ToString() const {
  std::string str = "Polygon(";
  for (size_t i = 0; i < polygon.size(); ++i) {
    str += polygon[i].ToString();
    if (i != polygon.size() - 1) {
      str += ", ";
    }
  }
  str += ")";
  return str;
}
geometry::Polygon &geometry::Polygon::operator=(const Polygon &other) {
  polygon = other.polygon;
  return *this;
}
