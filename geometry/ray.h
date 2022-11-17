#pragma once
#include "IShape.h"
#include "point.h"
#include "vector.h"

class geometry::Ray : public geometry::IShape {
 public:
  Point point;
  Vector vector;
  Ray(const Point &, const Vector &);
  Ray(const Point &, const Point &);
  IShape &Move(const geometry::Vector &) override;
  bool ContainsPoint(const geometry::Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  IShape *Clone() const override;
  std::string ToString() const override;
};