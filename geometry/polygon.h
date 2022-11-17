#pragma once
#include "IShape.h"
#include "point.h"
#include "ray.h"
#include "segment.h"

class geometry::Polygon : public geometry::IShape {
 public:
  std::vector<geometry::Point> polygon;

  Polygon() = default;
  explicit Polygon(const std::vector<Point> &);
  Polygon(const Polygon &);
  Polygon(const Polygon &&);
  IShape &Move(const Vector &) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  IShape *Clone() const override;
  std::string ToString() const override;
  Polygon &operator=(const Polygon &);
};