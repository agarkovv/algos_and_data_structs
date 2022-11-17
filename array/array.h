#ifndef CONTEST_TEMPLATES_AND_LONG_ARITHMETIC__A_ARRAY_H_
#define CONTEST_TEMPLATES_AND_LONG_ARITHMETIC__A_ARRAY_H_
#define ARRAY_TRAITS_IMPLEMENTED
#include <stdexcept>
class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};
template <class T, size_t N>
class Array {
 public:
  T buffer_[N];
  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return buffer_[idx];
  }
  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return buffer_[idx];
  }
  T& operator[](size_t idx) {
    return buffer_[idx];
  }
  const T& operator[](size_t idx) const {
    return buffer_[idx];
  }
  T& Front() {
    return At(0);
  }
  const T& Front() const {
    return At(0);
  }
  T& Back() {
    return At(N - 1);
  }
  const T& Back() const {
    return At(N - 1);
  }
  const T* Data() const {
    return buffer_;
  }
  size_t Size() const {
    return N;
  }
  bool Empty() const {
    bool empty = true;
    if (N != 0) {
      empty = false;
      return empty;
    }
    return empty;
  }
  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      buffer_[i] = value;
    }
  }
  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      T tmp = buffer_[i];
      buffer_[i] = other.buffer_[i];
      other.buffer_[i] = tmp;
    }
  }
};

template <class T>
size_t GetSize(const T) {
  return 0;
}
template <class T, size_t N>
size_t GetSize(const T (&)[N]) {
  return N;
}
template <class T>
size_t GetRank(const T) {
  return 0;
}
template <class T, size_t N>
size_t GetRank(const T (&array)[N]) {
  return 1 + GetRank(array[0]);
}
template <class T>
size_t GetNumElements(const T) {
  return 1;
}
template <class T, size_t N>
size_t GetNumElements(const T (&array)[N]) {
  return GetSize(array) * GetNumElements(array[0]);
}
#endif  // CONTEST_TEMPLATES_AND_LONG_ARITHMETIC__A_ARRAY_H_