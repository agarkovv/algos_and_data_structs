#pragma once
#include <cstddef>
#include <cstring>
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
  bool flag;
  int64_t size;
  int64_t chunk_count;
  int64_t* number;
  static const int64_t kModulo = 1000000000;
  static const int64_t kLimit = 30000;
  BigInteger(char str[]);
  BigInteger(int64_t num);
  void SetCount(BigInteger& x, BigInteger y);
  ~BigInteger() {
    delete[] number;
  }

 private:
  void SwapChunk(char chunk[], const int64_t chunksize);
  int64_t Atoi(char chunk[], const int64_t chunksize);
};

BigInteger operator+(BigInteger& x, BigInteger& y);
BigInteger operator-(BigInteger& x, BigInteger& y);

bool operator<(BigInteger& x, BigInteger& y);
bool operator>(BigInteger& x, BigInteger& y);
bool operator<=(BigInteger& x, BigInteger& y);
bool operator>=(BigInteger& x, BigInteger& y);
bool operator==(BigInteger& x, BigInteger& y);
bool operator!=(BigInteger& x, BigInteger& y);

void PrintBigInteger(BigInteger& x);
