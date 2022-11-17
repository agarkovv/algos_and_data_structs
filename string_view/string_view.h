#pragma once
#include <stdexcept>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 public:
  StringView() : string_(nullptr), size_(0) {
  }
  StringView(const char* other) : string_(nullptr), size_(0) {  // NOLINT
    size_t other_size = 0;
    while (*(other + other_size) != '\0') {
      ++other_size;
    }
    string_ = other;
    size_ = other_size;
  }
  StringView(const char* other, size_t other_size) : string_(other), size_(other_size) {
  }
  const char& operator[](size_t index) const {
    return *(string_ + index);
  }
  const char& At(size_t index) const {
    if (index >= size_) {
      throw StringViewOutOfRange();
    }
    return *(string_ + index);
  }
  const char& Front() const {
    return *(string_);
  }
  const char& Back() const {
    return *(string_ + size_ - 1);
  }
  size_t Size() const {
    return size_;
  }
  size_t Length() const {
    return size_;
  }
  bool Empty() const {
    bool flag = true;
    return (size_ > 0 ? !flag : flag);
  }
  const char* Data() const {
    return string_;
  }
  void Swap(StringView& other) {
    const char* tmp = string_;
    size_t tmp_size = size_;
    string_ = other.string_;
    size_ = other.size_;
    other.string_ = tmp;
    other.size_ = tmp_size;
  }
  void RemovePrefix(size_t prefix_size) {
    string_ += prefix_size;
    size_ -= prefix_size;
  }
  void RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
  }
  StringView Substr(size_t pos, size_t count = -1) {
    if (pos >= size_) {
      throw StringViewOutOfRange();
    }
    size_t min_size = -1;
    if (count < size_ - pos) {
      min_size = count;
    } else {
      min_size = size_ - pos;
    }
    StringView sub_str(string_ + pos, min_size);
    return sub_str;
  }

 private:
  const char* string_;
  size_t size_;
};