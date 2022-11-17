#pragma once
#include <cmath>
#include "IShape.h"

class geometry::Vector {
 public:
  int64_t x, y;
  geometry::Vector &operator+();
  geometry::Vector &operator-();
  int64_t Length();
};

geometry::Vector operator+(const geometry::Vector &, const geometry::Vector &);
geometry::Vector operator-(const geometry::Vector &, const geometry::Vector &);

template <class T>
geometry::Vector operator*(const geometry::Vector &, const T);
template <class T>
geometry::Vector operator/(const geometry::Vector &, const T);

geometry::Vector &operator+=(geometry::Vector &, const geometry::Vector &);
geometry::Vector &operator-=(geometry::Vector &, const geometry::Vector &);

template <class T>
geometry::Vector &operator*=(const geometry::Vector &, const T);
template <class T>
geometry::Vector &operator/=(const geometry::Vector &, const T);

bool operator==(const geometry::Vector &, const geometry::Vector &);

int64_t VectorProduct(const geometry::Vector &, const geometry::Vector &);
int64_t ScalarProduct(const geometry::Vector &, const geometry::Vector &);