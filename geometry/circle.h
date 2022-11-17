#pragma once
#include "IShape.h"
#include "point.h"

class geometry::Circle : public geometry::IShape {
 public:
  geometry::Point point;
  int64_t radius;
  Circle(const Point &, int64_t);
  IShape &Move(const geometry::Vector &) override;
  bool ContainsPoint(const geometry::Point &) const override;
  bool CrossesSegment(const Segment &) const override;
  IShape *Clone() const override;
  std::string ToString() const override;
};