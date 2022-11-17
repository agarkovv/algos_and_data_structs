#include "../vector.h"

geometry::Vector &geometry::Vector::operator+() {
  return *this;
}
geometry::Vector &geometry::Vector::operator-() {
  x = -x;
  y = -y;
  return *this;
}

geometry::Vector operator+(const geometry::Vector &vec1, const geometry::Vector &vec2) {
  geometry::Vector tmp;
  tmp.x = vec1.x + vec2.x;
  tmp.y = vec1.y + vec2.y;
  return tmp;
}
geometry::Vector operator-(const geometry::Vector &vec1, const geometry::Vector &vec2) {
  geometry::Vector tmp;
  tmp.x = vec1.x - vec2.x;
  tmp.y = vec1.y - vec2.y;
  return tmp;
}

int64_t geometry::Vector::Length() {
  return x * x + y * y;
}

template <class T>
geometry::Vector operator*(const geometry::Vector &vec, const T scal) {
  geometry::Vector tmp;
  tmp.x = vec.x * scal;
  tmp.y = vec.y * scal;
  return tmp;
}
template <class T>
geometry::Vector operator/(const geometry::Vector &vec, const T scal) {
  geometry::Vector tmp;
  tmp.x = vec.x / scal;
  tmp.y = vec.y / scal;
  return tmp;
}

geometry::Vector &operator+=(geometry::Vector &vec1, const geometry::Vector &vec2) {
  vec1.x += vec2.x;
  vec1.y += vec2.y;
  return vec1;
}
geometry::Vector &operator-=(geometry::Vector &vec1, const geometry::Vector &vec2) {
  vec1.x -= vec2.x;
  vec1.y -= vec2.y;
  return vec1;
}

template <class T>
geometry::Vector &operator*=(geometry::Vector &vec, const T scal) {
  vec.x *= scal;
  vec.y *= scal;
  return vec;
}
template <class T>
geometry::Vector &operator/=(geometry::Vector &vec, const T scal) {
  vec.x /= scal;
  vec.y /= scal;
  return vec;
}

bool operator==(const geometry::Vector &vec1, const geometry::Vector &vec2) {
  return vec1.x * vec1.x + vec1.y * vec1.y == vec2.x * vec2.x + vec2.y * vec2.y && vec1.y * vec2.x == vec1.x * vec2.y;
}

int64_t VectorProduct(const geometry::Vector &vector1, const geometry::Vector &vector2) {
  return vector1.x * vector2.y - vector1.y * vector2.x;
}
int64_t ScalarProduct(const geometry::Vector &vector1, const geometry::Vector &vector2) {
  return vector1.x * vector2.x + vector1.y * vector2.y;
}