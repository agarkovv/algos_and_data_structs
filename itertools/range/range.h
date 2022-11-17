#pragma once
#include <cstddef>
#include <cstdint>

class Iterator {
 public:
  Iterator() = default;

  Iterator(int64_t state, int64_t step) : state_(state), step_(step) {
  }

  int64_t& operator*() {
    return state_;
  }

  Iterator& operator++() {
    state_ += step_;
    return *this;
  }

  bool operator!=(const Iterator& other) const {
    if (step_ > 0) {
      return state_ < other.state_;
    }

    if (step_ < 0) {
      return state_ > other.state_;
    }

    return false;
  }

 private:
  int64_t state_ = 0;
  int64_t step_ = 1;
};

class Range {
 public:
  Range() = default;

  explicit Range(int64_t stop) : start_(0), stop_(stop), step_(1) {
  }

  Range(int64_t start, int64_t stop, int64_t step = 1) : start_(start), stop_(stop), step_(step) {
  }

  Iterator begin() const {  // NOLINT
    return Iterator(start_, step_);
  }

  Iterator end() const {  // NOLINT
    return Iterator(stop_, step_);
  }

 private:
  int64_t start_ = 0;
  int64_t stop_ = 0;
  int64_t step_ = 1;
};
