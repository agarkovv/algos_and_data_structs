#pragma once
#include "IShape.h"
#include "point.h"

class geometry::Segment : public geometry::IShape {
 public:
  geometry::Point p, q;
  Segment(const geometry::Point &, const geometry::Point &);
  IShape &Move(const geometry::Vector &) override;
  bool ContainsPoint(const geometry::Point &) const override;
  bool CrossesSegment(const geometry::Segment &) const override;
  IShape *Clone() const override;
  std::string ToString() const override;
  Segment &operator=(const geometry::Segment &);
};

bool Intersect(int64_t, int64_t, int64_t, int64_t);
