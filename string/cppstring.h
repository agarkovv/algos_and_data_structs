#ifndef UNTITLED_CMAKE_BUILD_DEBUG_STRING
#define UNTITLED_CMAKE_BUILD_DEBUG_STRING
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 public:
  String();
  String(const size_t&, const char&);
  String(const char*);  // NOLINT
  String(const char*, const size_t&);
  String(const String&);
  const char& At(const size_t&) const;
  char& At(const size_t&);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  const char* CStr() const;
  const char* Data() const;
  char* CStr();
  char* Data();
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(const char& symbol);
  void Resize(const size_t&, const char&);
  void Reserve(const size_t&);
  void ShrinkToFit();
  String& operator=(const String&);
  const char& operator[](size_t) const;
  char& operator[](size_t);
  String& operator+=(const String&);
  friend std::ostream& operator<<(std::ostream& os, const String& str);
  ~String();

 private:
  char* string_;
  size_t size_;
  size_t capacity_;
};
String operator+(const String&, const String&);
bool operator<(const String&, const String&);
bool operator>(const String&, const String&);
bool operator<=(const String&, const String&);
bool operator>=(const String&, const String&);
bool operator==(const String&, const String&);
bool operator!=(const String&, const String&);
size_t Cstrsize(const char*);
#endif  // UNTITLED_CMAKE_BUILD_DEBUG_STRING