#pragma once
#include <vector>
#include <string>

namespace geometry {

class Vector;
class Circle;
class Line;
class Point;
class Polygon;
class Ray;
class Segment;

class IShape {
 public:
  virtual IShape &Move(const Vector &) = 0;
  virtual bool ContainsPoint(const Point &) const = 0;
  virtual bool CrossesSegment(const Segment &) const = 0;
  virtual IShape *Clone() const = 0;
  virtual std::string ToString() const = 0;
  virtual ~IShape() = default;
};

}  // namespace geometry