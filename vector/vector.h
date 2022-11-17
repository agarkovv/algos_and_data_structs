#pragma once
#define VECTOR_MEMORY_IMPLEMENTED
#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <iostream>

template <typename T>
class Vector {
 public:
  using ValueType = T;
  using Pointer = ValueType *;
  using ConstPointer = const ValueType *;
  using Reference = ValueType &;
  using ConstReference = const ValueType &;
  using SizeType = size_t;
  using Iterator = Pointer;
  using ConstIterator = ConstPointer;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  Vector() : arr_(nullptr), size_(0), cap_(0) {
  }

  explicit Vector(const size_t &size) : Vector() {
    if (size == 0) {
      return;
    }

    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * size));

    size_t i = 0;
    try {
      for (; i < size; ++i) {
        new (new_arr + i) T();
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        (new_arr + j)->~T();
      }
      operator delete(new_arr);
      throw;
    }
    arr_ = new_arr;
    size_ = size;
    cap_ = size;
  }
  Vector(const size_t &size, const T &value) : Vector() {
    if (size == 0) {
      return;
    }

    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * size));

    size_t i = 0;
    try {
      for (; i < size; ++i) {
        new (new_arr + i) T(value);
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        (new_arr + j)->~T();
      }
      operator delete(new_arr);
      throw;
    }

    arr_ = new_arr;
    size_ = size;
    cap_ = size;
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) : Vector() {
    if (last - first == 0) {
      return;
    }

    size_t new_size = last - first;
    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * new_size));

    size_t i = 0;
    try {
      for (; i < new_size; ++i) {
        new (new_arr + i) T(*(first + i));
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        (new_arr + j)->~T();
      }
      operator delete(new_arr);
      throw;
    }

    arr_ = new_arr;
    size_ = last - first;
    cap_ = last - first;
  }

  Vector(std::initializer_list<T> list) : Vector() {
    if (list.size() == 0) {
      return;
    }

    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * list.size()));

    try {
      std::uninitialized_copy(list.begin(), list.end(), new_arr);
    } catch (...) {
      operator delete(new_arr);
      throw;
    }

    arr_ = new_arr;
    size_ = list.size();
    cap_ = list.size();
  }

  Vector(const Vector &other) : Vector() {
    if (other.arr_ == nullptr) {
      return;
    }

    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * other.cap_));

    size_t i = 0;
    try {
      for (; i < other.size_; ++i) {
        new (new_arr + i) T(other.arr_[i]);
      }
    } catch (...) {
      for (size_t j = 0; j < i; ++j) {
        (new_arr + j)->~T();
      }
      operator delete(new_arr);
      throw;
    }

    arr_ = new_arr;
    size_ = other.size_;
    cap_ = other.cap_;
  }

  Vector(Vector &&other) noexcept : arr_(other.arr_), size_(other.size_), cap_(other.cap_) {
    other.arr_ = nullptr;
    other.size_ = 0;
    other.cap_ = 0;
  }

  Vector &operator=(const Vector &other) {
    if (this != &other) {
      Vector tmp(other);
      Swap(tmp);
    }

    return *this;
  }

  Vector &operator=(Vector &&other) noexcept {
    if (this != &other) {
      Vector tmp(std::move(other));
      Swap(tmp);
    }

    return *this;
  }

  ~Vector() {
    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    operator delete(arr_);
  }

  size_t Size() const {
    return size_;
  }

  size_t Capacity() const {
    return cap_;
  }

  bool Empty() const {
    return size_ == 0;
  };

  T &operator[](const size_t idx) {
    return arr_[idx];
  }

  const T &operator[](const size_t idx) const {
    return arr_[idx];
  }

  T &At(size_t idx) {
    if (idx >= size_) {
      throw std::out_of_range("idx out of range");
    }
    return arr_[idx];
  }

  const T &At(size_t idx) const {
    if (idx >= size_) {
      throw std::out_of_range("idx out of range");
    }
    return arr_[idx];
  }

  T &Front() {  // Can be out of range
    return arr_[0];
  }

  const T &Front() const {  // Can be out of range
    return arr_[0];
  }

  T &Back() {  // Can be out of range
    return arr_[size_ - 1];
  }

  const T &Back() const {  // Can be out of range
    return arr_[size_ - 1];
  }

  T *Data() {
    return arr_;
  }

  const T *Data() const {
    return arr_;
  }

  void Swap(Vector &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(cap_, other.cap_);
  }

  void Resize(const size_t new_size, T &&val = T()) {
    if (new_size > cap_) {
      auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * new_size));
      size_t idx = 0;
      try {
        for (; idx < size_; ++idx) {
          new (new_arr + idx) T();
          new_arr[idx] = std::move(arr_[idx]);
        }
        for (; idx < new_size; ++idx) {
          new (new_arr + idx) T();
          new_arr[idx] = std::move(val);
        }
      } catch (...) {
        for (size_t j = 0; j < idx; ++j) {
          arr_[j] = std::move(new_arr[j]);
          (new_arr + j)->~T();
        }
        operator delete(new_arr);
        throw;
      }
      for (size_t i = 0; i < size_; ++i) {
        (arr_ + i)->~T();
      }
      operator delete(arr_);
      arr_ = new_arr;
      cap_ = new_size;
    } else if (new_size > size_) {
      size_t idx = size_;
      try {
        for (; idx < new_size; ++idx) {
          new (arr_ + idx) T(std::move(val));
        }
      } catch (...) {
        for (size_t i = size_; i < idx; ++i) {
          (arr_ + i)->~T();
        }
        throw;
      }
      size_ = new_size;

      return;
    }

    for (size_t i = new_size; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    size_ = new_size;
  }

  void Reserve(const size_t new_cap) {
    if (new_cap <= cap_) {
      return;
    }

    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * new_cap));

    try {
      std::uninitialized_move(arr_, arr_ + size_, new_arr);
    } catch (...) {
      operator delete(new_arr);
      throw;
    }

    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    operator delete(arr_);
    arr_ = new_arr;
    cap_ = new_cap;
  }

  void ShrinkToFit() {
    if (cap_ == size_) {
      return;
    }

    if (size_ != 0) {
      auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * size_));

      try {
        std::uninitialized_move(arr_, arr_ + size_, new_arr);
      } catch (...) {
        operator delete(new_arr);
        throw;
      }

      for (size_t i = 0; i < size_; ++i) {
        (arr_ + i)->~T();
      }
      operator delete(arr_);
      arr_ = new_arr;
      cap_ = size_;

    } else {

      operator delete(arr_);
      arr_ = nullptr;
      cap_ = size_;
    }
  }

  void Clear() {
    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    size_ = 0;
  }

  void PushBack(const T &val) {
    if (size_ < cap_) {
      new (arr_ + size_) T(val);
      ++size_;
      return;
    }
    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * (cap_ * 2 + 1)));
    size_t k = 0;
    try {
      for (size_t i = 0; i < size_; i++) {
        k++;
        new (new_arr + i) T(arr_[i]);
      }
      k++;
      new (new_arr + size_) T(val);
    } catch (...) {
      for (size_t i = 0; i < k; i++) {
        (new_arr)->~T();
      }
      operator delete(new_arr);
      throw;
    }

    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    operator delete(arr_);
    arr_ = new_arr;
    cap_ = cap_ * 2 + 1;
    ++size_;
  }

  void PushBack(T &&val) {
    if (size_ < cap_) {
      try {
        new (arr_ + size_) T(std::move(val));
      } catch (...) {
        (arr_ + size_)->~T();
        throw;
      }

      ++size_;

      return;
    }

    size_t new_arr_cap = 0;
    if (cap_ > 0) {
      new_arr_cap = cap_ * 2;
    } else {
      new_arr_cap = 1;
    }

    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * new_arr_cap));

    try {
      std::uninitialized_move(arr_, arr_ + size_, new_arr);
      new (new_arr + size_) T(std::move(val));
    } catch (...) {
      (new_arr + size_)->~T();
      operator delete(new_arr);
      throw;
    }

    if (arr_ == nullptr) {
      arr_ = new_arr;
      cap_ = new_arr_cap;
      ++size_;

      return;
    }

    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    operator delete(arr_);

    arr_ = new_arr;
    cap_ = new_arr_cap;
    ++size_;
  }

  template <class... Args>
  void EmplaceBack(Args &&... args) {
    if (size_ < cap_) {
      try {
        new (arr_ + size_) T(std::forward<Args>(args)...);
      } catch (...) {
        (arr_ + size_)->~T();
        throw;
      }

      ++size_;

      return;
    }

    size_t new_arr_cap = 0;
    if (cap_ > 0) {
      new_arr_cap = cap_ * 2;
    } else {
      new_arr_cap = 1;
    }

    auto new_arr = reinterpret_cast<T *>(operator new(sizeof(T) * new_arr_cap));

    try {
      std::uninitialized_move(arr_, arr_ + size_, new_arr);
      new (new_arr + size_) T(std::forward<Args>(args)...);
    } catch (...) {
      (new_arr + size_)->~T();
      operator delete(new_arr);
      throw;
    }

    if (arr_ == nullptr) {
      arr_ = new_arr;
      cap_ = new_arr_cap;
      ++size_;

      return;
    }

    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }
    operator delete(arr_);

    arr_ = new_arr;
    cap_ = new_arr_cap;
    ++size_;
  }

  void PopBack() {
    if (size_ > 0) {
      --size_;
      (arr_ + size_)->~T();
    }
  }

  bool operator<(const Vector &other) const {
    size_t min_size = std::min(size_, other.size_);
    for (size_t i = 0; i < min_size; ++i) {
      if (arr_[i] < other.arr_[i]) {
        return true;
      }
      if (arr_[i] > other.arr_[i]) {
        return false;
      }
    }
    return size_ < other.size_;
  }

  bool operator>(const Vector &other) const {
    size_t min_size = std::min(size_, other.size_);
    for (size_t i = 0; i < min_size; ++i) {
      if (arr_[i] > other.arr_[i]) {
        return true;
      }
      if (arr_[i] < other.arr_[i]) {
        return false;
      }
    }
    return size_ > other.size_;
  }

  bool operator==(const Vector &other) const {
    return !(*this > other) && !(*this < other);
  }

  bool operator<=(const Vector &other) const {
    return (*this < other) || (*this == other);
  }

  bool operator>=(const Vector other) const {
    return (*this > other) || (*this == other);
  }

  bool operator!=(const Vector &other) const {
    return !(*this == other);
  }

  Iterator begin() {  // NOLINT
    return arr_;
  }

  Iterator end() {  // NOLINT
    return arr_ + size_;
  }

  ConstIterator begin() const {  // NOLINT
    return arr_;
  }

  ConstIterator end() const {  // NOLINT
    return arr_ + size_;
  }

  ConstIterator cbegin() const {  // NOLINT
    return arr_;
  }

  ConstIterator cend() const {  // NOLINT
    return arr_ + size_;
  }

  ReverseIterator rbegin() {  // NOLINT
    return std::reverse_iterator(arr_ + size_);
  }

  ReverseIterator rend() {  // NOLINT
    return std::reverse_iterator(arr_);
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return std::reverse_iterator(arr_ + size_);
  }

  ConstReverseIterator rend() const {  // NOLINT
    return std::reverse_iterator(arr_);
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return std::reverse_iterator(arr_ + size_);
  }

  ConstReverseIterator crend() const {  // NOLINT
    return std::reverse_iterator(arr_);
  }

 private:
  T *arr_;
  size_t size_;
  size_t cap_;
};