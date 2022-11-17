#pragma once
#define WEAK_PTR_IMPLEMENTED
#include <stdexcept>

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

struct Counter {
  size_t strong_count;
  size_t weak_count;
};

template <class T>
class SharedPtr;
template <class T>
class WeakPtr;

template <class T, class... Args>
SharedPtr<T> MakeShared(Args&&... args) {
  auto shared = SharedPtr<T>(new T(std::forward<Args>(args)...));
  return shared;
}

template <class T>
class SharedPtr {
 public:
  SharedPtr() : ptr_(nullptr), counter_(nullptr) {
  }
  SharedPtr(T* ptr) : ptr_(ptr), counter_(nullptr) {  // NOLINT
    if (ptr_ != nullptr) {
      counter_ = new Counter{1, 0};
    }
  }
  SharedPtr(const WeakPtr<T>& weak_ptr) {  // NOLINT
    if (weak_ptr.Expired()) {
      throw BadWeakPtr{};
    } else {
      ptr_ = weak_ptr.Get();
      counter_ = weak_ptr.GetCounter();
      if (ptr_ != nullptr) {
        ++counter_->strong_count;
      }
    }
  }
  SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (ptr_ != nullptr) {
      ++counter_->strong_count;
    }
  }
  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      Deleter();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      if (ptr_ != nullptr) {
        ++counter_->strong_count;
      }
    }
    return *this;
  }
  SharedPtr(SharedPtr&& other) noexcept : SharedPtr() {
    Swap(other);
  }
  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      Deleter();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      other.ptr_ = nullptr;
      other.counter_ = nullptr;
    }
    return *this;
  }
  SharedPtr& Reset(T* ptr = nullptr) {
    Deleter();
    ptr_ = ptr;
    if (ptr_ != nullptr) {
      counter_ = new Counter{1, 0};
    } else {
      counter_ = nullptr;
    }
    return *this;
  }
  void Swap(SharedPtr<T>& other) {
    std::swap(this->ptr_, other.ptr_);
    std::swap(this->counter_, other.counter_);
  }
  T* Get() const {
    return ptr_;
  }
  Counter* GetCounter() const {
    return counter_;
  }
  size_t UseCount() const {
    return (ptr_ != nullptr ? counter_->strong_count : 0);
  }
  T& operator*() const {
    return *ptr_;
  }
  T* operator->() const {
    return ptr_;
  }
  explicit operator bool() const {
    return ptr_ != nullptr;
  }
  void Deleter() {
    if (ptr_ != nullptr && --counter_->strong_count == 0) {
      delete ptr_;
      if (counter_->weak_count == 0) {
        delete counter_;
      }
    }
  }
  ~SharedPtr() {
    Deleter();
  }

 private:
  T* ptr_;
  Counter* counter_;
};

template <class T>
class WeakPtr {
 public:
  WeakPtr() : ptr_(nullptr), counter_(nullptr) {
  }
  WeakPtr(const WeakPtr& other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (ptr_ != nullptr) {
      ++counter_->weak_count;
    }
  }
  WeakPtr& operator=(const WeakPtr& other) {
    if (this != &other) {
      Deleter();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      if (ptr_ != nullptr) {
        ++counter_->weak_count;
      }
    }
    return *this;
  }
  WeakPtr(WeakPtr&& other) noexcept : WeakPtr() {
    Swap(other);
  }
  WeakPtr& operator=(WeakPtr&& other) noexcept {
    if (this != &other) {
      Deleter();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      other.ptr_ = nullptr;
      other.counter_ = nullptr;
    }
    return *this;
  }
  WeakPtr(const SharedPtr<T>& other) : ptr_(other.Get()), counter_(other.GetCounter()) {  // NOLINT
    if (ptr_ != nullptr) {
      ++counter_->weak_count;
    }
  }
  T* Get() const {
    return ptr_;
  }
  Counter* GetCounter() const {
    return counter_;
  }
  void Swap(WeakPtr<T>& other) {
    std::swap(this->ptr_, other.ptr_);
    std::swap(this->counter_, other.counter_);
  }
  void Reset() {
    Deleter();
    ptr_ = nullptr;
    counter_ = nullptr;
  }
  size_t UseCount() const {
    return (ptr_ != nullptr ? counter_->strong_count : 0);
  }
  bool Expired() const {
    return UseCount() == 0;
  }
  SharedPtr<T> Lock() const {
    if (Expired()) {
      return SharedPtr<T>();
    }
    return SharedPtr<T>(*this);
  }
  void Deleter() {
    if (ptr_ != nullptr && (--counter_->weak_count + counter_->strong_count) == 0) {
      delete counter_;
    }
  }
  ~WeakPtr() {
    Deleter();
  }

 private:
  T* ptr_;
  Counter* counter_;
};