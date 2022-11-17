#include "cppstring.h"
#include <iostream>
String::String() : string_(nullptr), size_(0), capacity_(1) {
}
String::String(const size_t& size, const char& symbol) : string_(nullptr), size_(size), capacity_(1) {
  if (size > 0) {
    while (capacity_ < size) {
      capacity_ *= 2;
    }
    string_ = new char[capacity_];
    for (size_t i = 0; i < size; ++i) {
      *(string_ + i) = symbol;
    }
  }
}
String::String(const char* str) : string_(nullptr), size_(0), capacity_(1) {
  size_ = Cstrsize(str);
  if (size_ > 0) {
    while (capacity_ < size_) {
      capacity_ *= 2;
    }
    string_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      *(string_ + i) = str[i];
    }
  }
}
String::String(const char* str, const size_t& size) : string_(nullptr), size_(size), capacity_(1) {
  if (size_ > 0) {
    while (capacity_ < size_) {
      capacity_ *= 2;
    }
    string_ = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      *(string_ + i) = *(str + i);
    }
  }
}
String::String(const String& str) : string_(nullptr), size_(str.size_), capacity_(str.capacity_) {
  if (size_ == 0) {
    return;
  }
  string_ = new char[capacity_];
  for (size_t i = 0; i < str.size_; ++i) {
    *(string_ + i) = *(str.string_ + i);
  }
}
const char& String::At(const size_t& index) const {
  if (index < size_) {
    return *(string_ + index);
  }
  throw StringOutOfRange();
}
char& String::At(const size_t& index) {
  if (index < size_) {
    return *(string_ + index);
  }
  throw StringOutOfRange();
}
const char& String::Front() const {
  return *string_;
}
char& String::Front() {
  return *string_;
}
const char& String::Back() const {
  return *(string_ + size_ - 1);
}
char& String::Back() {
  return *(string_ + size_ - 1);
}
const char* String::CStr() const {
  return string_;
}
const char* String::Data() const {
  return string_;
}
char* String::CStr() {
  return string_;
}
char* String::Data() {
  return string_;
}
bool String::Empty() const {
  bool flag = true;
  return (size_ != 0 ? !flag : flag);
}
size_t String::Size() const {
  return size_;
}
size_t String::Length() const {
  return size_;
}
size_t String::Capacity() const {
  if (capacity_ == 1) {
    return capacity_ - 1;
  }
  return capacity_;
}
void String::Clear() {
  size_ = 0;
}
void String::Swap(String& other) {
  char* tmp = string_;
  size_t tmp_size = size_;
  size_t tmp_capacity = capacity_;
  string_ = other.string_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.string_ = tmp;
  other.size_ = tmp_size;
  other.capacity_ = tmp_capacity;
}
void String::PopBack() {
  --size_;
}
void String::PushBack(const char& symbol) {
  if (size_ == 0) {
    String tmp(1, symbol);
    Swap(tmp);
    return;
  }
  if (size_ < capacity_) {
    *(string_ + size_) = symbol;
    ++size_;
  } else {
    auto tmp = new char[capacity_ * 2];
    for (size_t i = 0; i < size_; ++i) {
      *(tmp + i) = *(string_ + i);
    }
    tmp[size_] = symbol;
    delete[] string_;
    string_ = tmp;
    ++size_;
    capacity_ *= 2;
  }
}
void String::Resize(const size_t& new_size, const char& symbol) {
  if (size_ < new_size) {
    if (capacity_ < new_size) {
      auto tmp = new char[new_size];
      for (size_t i = 0; i < size_; ++i) {
        *(tmp + i) = *(string_ + i);
      }
      delete[] string_;
      string_ = tmp;
      capacity_ = new_size;
    }
    for (size_t i = size_; i < new_size; ++i) {
      *(string_ + i) = symbol;
    }
  }
  size_ = new_size;
}
void String::Reserve(const size_t& new_capacity) {
  if (capacity_ < new_capacity) {
    auto tmp = new char[new_capacity];
    for (size_t i = 0; i < size_; ++i) {
      *(tmp + i) = *(string_ + i);
    }
    delete[] string_;
    string_ = tmp;
    capacity_ = new_capacity;
  }
}
void String::ShrinkToFit() {
  if (size_ > 0) {
    auto tmp = new char[size_];
    for (size_t i = 0; i < size_; ++i) {
      *(tmp + i) = *(string_ + i);
    }
    delete[] string_;
    string_ = tmp;
    capacity_ = size_;
    return;
  }
  delete[] string_;
  string_ = nullptr;
  capacity_ = size_;
}
String& String::operator=(const String& str) {
  if (*this == str) {
    return *this;
  }
  String tmp(str);
  Swap(tmp);
  return *this;
}
const char& String::operator[](size_t index) const {
  return *(string_ + index);
}
char& String::operator[](size_t index) {
  return *(string_ + index);
}
String& String::operator+=(const String& str) {
  if (size_ + str.size_ < capacity_) {
    for (size_t i = size_; i < size_ + str.size_; ++i) {
      *(string_ + i) = *(str.string_ + i - size_);
    }
  } else {
    while (capacity_ < size_ + str.size_) {
      capacity_ *= 2;
    }
    auto tmp = new char[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      *(tmp + i) = *(string_ + i);
    }
    for (size_t i = size_; i < size_ + str.size_; ++i) {
      *(tmp + i) = *(str.string_ + i - size_);
    }
    delete[] string_;
    string_ = tmp;
  }
  size_ += str.size_;
  return *this;
}
String operator+(const String& str1, const String& str2) {
  String tmp(str1);
  tmp += str2;
  return tmp;
}
bool operator<(const String& str1, const String& str2) {
  bool flag = true;
  size_t min_size = 0;
  if (str1.Size() < str2.Size()) {
    min_size = str1.Size();
  } else {
    min_size = str2.Size();
  }
  for (size_t i = 0; i < min_size; ++i) {
    if (*(str1.CStr() + i) > *(str2.CStr() + i)) {
      return !flag;
    }
    if (*(str1.CStr() + i) < *(str2.CStr() + i)) {
      return flag;
    }
  }
  if (str1.Size() < str2.Size()) {
    return flag;
  }
  return !flag;
}
bool operator>(const String& str1, const String& str2) {
  bool flag = true;
  size_t min_size = 0;
  if (str1.Size() < str2.Size()) {
    min_size = str1.Size();
  } else {
    min_size = str2.Size();
  }
  for (size_t i = 0; i < min_size; ++i) {
    if (*(str1.CStr() + i) < *(str2.CStr() + i)) {
      return !flag;
    }
    if (*(str1.CStr() + i) > *(str2.CStr() + i)) {
      return flag;
    }
  }
  if (str1.Size() > str2.Size()) {
    return flag;
  }
  return !flag;
}
bool operator<=(const String& str1, const String& str2) {
  bool flag = true;
  size_t min_size = 0;
  if (str1.Size() < str2.Size()) {
    min_size = str1.Size();
  } else {
    min_size = str2.Size();
  }
  for (size_t i = 0; i < min_size; ++i) {
    if (*(str1.CStr() + i) > *(str2.CStr() + i)) {
      return !flag;
    }
    if (*(str1.CStr() + i) < *(str2.CStr() + i)) {
      return flag;
    }
  }
  if (str1.Size() <= str2.Size()) {
    return flag;
  }
  return !flag;
}
bool operator>=(const String& str1, const String& str2) {
  bool flag = true;
  size_t min_size = 0;
  if (str1.Size() < str2.Size()) {
    min_size = str1.Size();
  } else {
    min_size = str2.Size();
  }
  for (size_t i = 0; i < min_size; ++i) {
    if (*(str1.CStr() + i) < *(str2.CStr() + i)) {
      return !flag;
    }
    if (*(str1.CStr() + i) > *(str2.CStr() + i)) {
      return flag;
    }
  }
  if (str1.Size() >= str2.Size()) {
    return flag;
  }
  return !flag;
}
bool operator==(const String& str1, const String& str2) {
  bool flag = true;
  size_t min_size = 0;
  if (str1.Size() < str2.Size()) {
    min_size = str1.Size();
  } else {
    min_size = str2.Size();
  }
  for (size_t i = 0; i < min_size; ++i) {
    if (*(str1.CStr() + i) < *(str2.CStr() + i)) {
      return !flag;
    }
    if (*(str1.CStr() + i) > *(str2.CStr() + i)) {
      return !flag;
    }
  }
  if (str1.Size() == str2.Size()) {
    return flag;
  }
  return !flag;
}
bool operator!=(const String& str1, const String& str2) {
  bool flag = true;
  size_t min_size = 0;
  if (str1.Size() < str2.Size()) {
    min_size = str1.Size();
  } else {
    min_size = str2.Size();
  }
  for (size_t i = 0; i < min_size; ++i) {
    if (*(str1.CStr() + i) < *(str2.CStr() + i)) {
      return flag;
    }
    if (*(str1.CStr() + i) > *(str2.CStr() + i)) {
      return flag;
    }
  }
  if (str1.Size() != str2.Size()) {
    return flag;
  }
  return !flag;
}
std::ostream& operator<<(std::ostream& os, const String& str) {
  for (size_t i = 0; i < str.Size(); ++i) {
    os << *(str.string_ + i);
  }
  return os;
}
String::~String() {
  delete[] string_;
}
size_t Cstrsize(const char* str) {
  size_t size = 0;
  while (str[size] != '\0') {
    ++size;
  }
  return size;
}