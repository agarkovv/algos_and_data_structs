#pragma once
#include <algorithm>
#include <cstddef>

template <class T>
class UniquePtr {
 public:
  UniquePtr() : ptr_(nullptr) {
  }
  explicit UniquePtr(T* ptr) : ptr_(ptr) {
  }
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }
  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }
  ~UniquePtr() {
    delete ptr_;
  }
  T& operator*() const {
    return *ptr_;
  }
  T* operator->() const {
    return ptr_;
  }
  T* Release() {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  }
  UniquePtr& Reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
    return *this;
  }
  void Swap(UniquePtr<T>& other) {
    auto tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
  }
  T* Get() const {
    return ptr_;
  }
  explicit operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T* ptr_;
};