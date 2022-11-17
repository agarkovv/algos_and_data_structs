#pragma once
#include <iostream>
#include <stdexcept>

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
  }
};

class BigIntegerDivisionByZero : public std::runtime_error {
 public:
  BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {
  }
};

class BigInteger {
 public:
  static const int64_t kCapacity = 4000;
  static const int64_t kLimit = 30000;
  static const int64_t kBase = 1000000000;
  static const int64_t kChunkSize = 9;

  BigInteger();
  BigInteger(const char*);
  BigInteger(const int64_t);
  ~BigInteger();

  bool IsNegative();

  BigInteger& operator=(const BigInteger&);

  BigInteger operator+();
  BigInteger operator-();

  BigInteger& operator++();
  BigInteger& operator--();

  BigInteger operator++(int);
  BigInteger operator--(int);

  explicit operator bool();

  friend const BigInteger operator+(const BigInteger&, const BigInteger&);
  friend const BigInteger operator-(const BigInteger&, const BigInteger&);
  friend const BigInteger operator*(const BigInteger&, const BigInteger&);

  friend bool operator<(const BigInteger&, const BigInteger&);
  friend bool operator>(const BigInteger&, const BigInteger&);

  friend std::ostream& operator<<(std::ostream&, const BigInteger&);

 private:
  bool negative_;
  int64_t chunk_count_;
  int64_t* number_;
};

BigInteger& operator+=(BigInteger&, const BigInteger&);
BigInteger& operator-=(BigInteger&, const BigInteger&);
BigInteger& operator*=(BigInteger&, const BigInteger&);

bool operator<=(const BigInteger&, const BigInteger&);
bool operator>=(const BigInteger&, const BigInteger&);

bool operator==(const BigInteger&, const BigInteger&);
bool operator!=(const BigInteger&, const BigInteger&);

bool operator<=(const int64_t&, const BigInteger&);
bool operator>=(const int64_t&, const BigInteger&);

bool operator==(const int64_t&, const BigInteger&);
bool operator!=(const int64_t&, const BigInteger&);

std::istream& operator>>(std::istream&, BigInteger&);