#pragma once
#include "IShape.h"

class geometry::Point : public geometry::IShape {
 public:
  int64_t x, y;
  Point() = default;
  Point(int64_t, int64_t);
  Point(const Point &);
  IShape &Move(const Vector &) override;
  bool ContainsPoint(const Point &) const override;
  bool CrossesSegment(const Segment &seg) const override;
  IShape *Clone() const override;
  std::string ToString() const override;
  Point &operator=(const Point &);
};

geometry::Vector operator-(const geometry::Point &, const geometry::Point &);