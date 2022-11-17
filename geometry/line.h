#pragma once
#include "IShape.h"
#include "point.h"

class geometry::Line : public geometry::IShape {
 public:
  int64_t a;
  int64_t b;
  int64_t c;

  Line(int64_t, int64_t, int64_t);
  Line(const geometry::Point &, const geometry::Point &);
  IShape &Move(const geometry::Vector &) override;
  bool ContainsPoint(const geometry::Point &) const override;
  bool CrossesSegment(const geometry::Segment &) const override;
  IShape *Clone() const override;
  std::string ToString() const override;
};
