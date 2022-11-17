#include <iostream>
#include <vector>
#include <memory>

#include "vector.h"
#include "point.h"
#include "segment.h"
#include "ray.h"
#include "line.h"
#include "circle.h"
#include "polygon.h"

#include "vector.h"   // check include guards
#include "point.h"    // check include guards
#include "segment.h"  // check include guards
#include "ray.h"      // check include guards
#include "line.h"     // check include guards
#include "circle.h"   // check include guards
#include "polygon.h"  // check include guards

template <class SmartPtrT>
void Delete(const SmartPtrT&) {
}

template <class T>
void Delete(T* ptr) {
  delete ptr;
}

void CheckFunctions(const geometry::IShape* shape_ptr, const geometry::Point& point_a, const geometry::Point& point_b) {
  std::cout << "Given shape " << (shape_ptr->ContainsPoint(point_a) ? "contains" : "does not contain") << " point A\n";

  const auto segment_ab = geometry::Segment(point_a, point_b);
  std::cout << "Given shape " << (shape_ptr->CrossesSegment(segment_ab) ? "crosses" : "does not cross")
            << " segment AB\n";

  const auto vector_ab = point_b - point_a;
  const auto cloned_shape_ptr = shape_ptr->Clone();  // may return either raw or smart pointer
  std::cout << cloned_shape_ptr->Move(vector_ab).ToString();

  Delete(cloned_shape_ptr);  // raw pointer compatibility
}

int main() {
  std::string command;
  std::cin >> command;

  auto shape_ptr = std::unique_ptr<geometry::IShape>();

  int x = 0;
  int y = 0;
  int a = 0;
  int b = 0;

  if (command == "point") {
    std::cin >> x >> y;
    shape_ptr = std::make_unique<geometry::Point>(x, y);
  } else if (command == "segment") {
    std::cin >> x >> y >> a >> b;
    shape_ptr = std::make_unique<geometry::Segment>(geometry::Point(x, y), geometry::Point(a, b));
  } else if (command == "ray") {
    std::cin >> x >> y >> a >> b;
    shape_ptr = std::make_unique<geometry::Ray>(geometry::Point(x, y), geometry::Point(a, b));
  } else if (command == "line") {
    std::cin >> x >> y >> a >> b;
    shape_ptr = std::make_unique<geometry::Line>(geometry::Point(x, y), geometry::Point(a, b));
  } else if (command == "polygon") {
    size_t n_points = 0;
    std::cin >> n_points;
    auto points = std::vector<geometry::Point>();
    points.reserve(n_points);
    for (size_t i = 0; i < n_points; ++i) {
      std::cin >> x >> y;
      points.emplace_back(x, y);
    }
    shape_ptr = std::make_unique<geometry::Polygon>(std::move(points));
  } else if (command == "circle") {
    std::cin >> x >> y;
    const auto center = geometry::Point(x, y);
    uint32_t radius = 0;
    std::cin >> radius;
    shape_ptr = std::make_unique<geometry::Circle>(center, radius);
  } else {
    std::cerr << "Undefined command" << std::endl;
    return 1;
  }

  std::cin >> x >> y;
  const auto point_a = geometry::Point(x, y);
  std::cin >> x >> y;
  const auto point_b = geometry::Point(x, y);

  CheckFunctions(shape_ptr.get(), point_a, point_b);
  return 0;
}