#pragma once
#include <stdexcept>
#include <memory>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char *what() const noexcept override {
    return "BadAnyCast error";
  }
};

class IHolder {

 public:
  virtual IHolder *Clone() const = 0;

  virtual ~IHolder() = default;
};

template <class T>
class AnyHolder : public IHolder {

 public:
  T data;

  AnyHolder(const T &other_data) : data(other_data) {  // NOLINT
  }

  AnyHolder(T &&other_data) noexcept : data(other_data) {  // NOLINT
  }

  AnyHolder *Clone() const override {
    return new AnyHolder<T>(data);
  }

  ~AnyHolder() override = default;
};

class Any {
 public:
  Any() : ptr_(nullptr) {
  }

  Any(const Any &other) : ptr_(other.ptr_->Clone()) {
  }

  template <class T>
  Any(T &&other_data) noexcept  // NOLINT
      : ptr_(static_cast<std::shared_ptr<IHolder>>((new AnyHolder<T>(std::forward<T>(other_data))))) {
  }

  Any(Any &&other) noexcept : ptr_(std::move(other.ptr_->Clone())) {
  }

  Any &operator=(Any &other) {
    ptr_ = static_cast<std::shared_ptr<IHolder>>(other.ptr_->Clone());
    return *this;
  }

  Any &operator=(Any &&other) {
    ptr_ = static_cast<std::shared_ptr<IHolder>>(other.ptr_->Clone());
    other.ptr_ = nullptr;
    return *this;
  }

  template <class T>
  Any &operator=(const T &other_data) {
    ptr_ = static_cast<std::shared_ptr<IHolder>>((new AnyHolder<T>(std::forward<T>(other_data))));
    return *this;
  }

  template <class T>
  Any &operator=(T &&other_data) {
    ptr_ = static_cast<std::shared_ptr<IHolder>>((new AnyHolder<T>(std::forward<T>(other_data))));
    return *this;
  }

  void Reset() {
    ptr_ = nullptr;
  }

  void Swap(Any &other) {
    std::shared_ptr<IHolder> tmp = std::move(ptr_);
    ptr_ = std::move(other.ptr_);
    other.ptr_ = std::move(tmp);
  }

  bool HasValue() const {
    return ptr_ != nullptr;
  }

  template <class T>
  friend T AnyCast(const Any &other);

  ~Any() = default;

 private:
  std::shared_ptr<IHolder> ptr_;
};

template <class T>
T AnyCast(const Any &other) {

  if (dynamic_cast<AnyHolder<T> *>(other.ptr_.get()) != nullptr) {
    return dynamic_cast<AnyHolder<T> *>(other.ptr_.get())->data;
  }

  throw BadAnyCast{};
}