#include "big_integer2.0.h"

BigInteger::BigInteger() : negative_(false), chunk_count_(0), number_(nullptr) {
}
BigInteger::BigInteger(const char* str) : negative_(false), chunk_count_(0), number_(nullptr) {

  int64_t* number_ = new int64_t[kCapacity]{};
  int64_t big_int_idx = 0;

  int64_t str_size = strlen(str);
  if (*(str) == '-') {
    negative_ = true;
  }

  char chunk[kChunkSize + 1]{};
  int64_t chunk_idx = 0;

  for (int64_t i = str_size - 1; i != -1; --i) {
    chunk[chunk_idx++] = str[i];
    if (chunk_idx == kChunkSize) {
      chunk_idx = 0;
      SwapChunk(chunk, kChunkSize);
      number_[big_int_idx++] = Atoi(chunk, kChunkSize);
      ++chunk_count;
      if (chunk_count >= kLimit) {
        throw BigIntegerOverflow();
      }
    }
  }
  if (chunk_idx != 0) {
    chunk[chunk_idx] = '\0';
    SwapChunk(chunk, chunk_idx);
    number_[big_int_idx++] = Atoi(chunk, chunk_idx);
    ++chunk_count_;
    if (chunk_count >= kLimit) {
      throw BigIntegerOverflow();
    }
  }
}
BigInteger::BigInteger(const int64_t num) : negative_(false), chunk_count_(0), number_(nullptr) { //  NOLINT

  int64_t* number_ = new int64_t[kCapacity]{};
  int64_t big_int_idx = 0;

  if (num < 0) {
    negative_ = true;
    num = -num;
  }

  number[big_int_idx++] = num % kBase;
  ++chunk_count_;
  if (num / kBase != 0) {
    number[big_int_idx++] = num / kBase;
    ++chunk_count_;
  }
}
BigInteger::~BigInteger() {
  delete[] number;
}

bool BigInteger::IsNegative() {
  return negative_;
}

BigInteger& BigInteger::operator=(const BigInteger& num) {
  this->number_ = new int64_t[kCapacity]{};
  for (int64_t i = 0; i < num.chunk_count_; ++i) {
    this->number_[i] = num.number_[i];
  }
  this->negative_ = num.negative_;
  this->chunk_count_ = num.chunk_count_;
  return *this;
}

const BigInteger BigInteger::operator+() const {
  BigInteger tmp = *this;
  return tmp;
}
const BigInteger BigInteger::operator-() const {
  BigInteger tmp = *this;
  tmp.negative_ = !this->negative_;
  return tmp;
}

BigInteger& BigInteger::operator++() {
  return (*this += 1);
}
BigInteger& BigInteger::operator--() {
    return (*this -= 1)
}

BigInteger BigInteger::operator++(int) {
  *this += 1;
  return *this - 1;
}
BigInteger BigInteger::operator--(int) {
  *this -= 1;
  return *this + 1;
}

BigInteger::operator bool() {
  bool flag = true;
  return (*this != 0 ? flag : !flag);
}

const BigInteger operator+(const BigInteger& num1, const BigInteger& num2) {
  if (num1.IsNegative()) {
    return -((-x) - y);
  }
  if (num2.IsNegative()) {
    return x - (-y);
  }
  BigInteger tmp = num1;
  int64_t carry = 0;
  for (int64_t i = 0; i < tmp.kCapacity; ++i) {
    int64_t res = carry + num1.number_[i] + num2.number_[i];
    tmp.number_[i] = res & tmp.kBase;
    carry = res / tmp.kBase;
  }
  return tmp;
}
const BigInteger operator-(const BigInteger& num1, const BigInteger& num2) {
  if (num1.negative_) {
    return -((-num1) + num2);
  }
  if (num2.negative_) {
    return num1 + (-num2);
  }
  if (num1 > num2) {
    BigInteger tmp = num1;
    int64_t carry = 0;
    for (int64_t i = 0; i < tmp.kCapacity; ++i) {
      int64_t res = (num1.kBase + num1.number_[i]) - (num2.number_[i] + carry);
      tmp.number_[i] = res % tmp.kBase;
      carry = res / tmp.kBase;
    }
    return tmp;
  }
  return -(num2 - num1);
}
const BigInteger operator*(const BigInteger& num1, const BigInteger& num2) {
  BigInteger tmp;
  delete[] tmp.number_;
  tmp.number_ = new int64_t[8000];
  for (int64_t i = 0; i < tmp.kCapacity; ++i) {
    int64_t carry = 0;
    for (int64_t j = 0; j < tmp.kCapacity || carry != 0; ++j) {
      int64_t res = tmp.number_[i + j] + num1.number_[i] * num2.number_[j] + carry;
      tmp.number_[i + j] = res % tmp.kBase;
      carry = res / tmp.kBase;
    }
  }
  tmp.negative_ = num1.negative_ != num2.negative_;
  for (int64_t i = tmp.kCapacity - 1; i != 2999; --i) {
    if (tmp.number_[i] != 0) {
      throw BigIntegerOverflow;
    }
  }
  return tmp;
}

BigInteger& operator+=(BigInteger& num1, const BigInteger& num2) {
  num1 = num1 + num2;
  return num1;
}
BigInteger& operator-=(BigInteger& num1, const BigInteger& num2) {
  num1 = num1 - num2;
  return num2;
}
BigInteger& operator*=(BigInteger& num1, const BigInteger& num2) {
  num1 = num1 * num2;
  return num1;
}

bool operator<(const BigInteger& num1, const BigInteger& num2) {
  bool flag = true;
  for (int64_t i = num1.kCapacity; i != -1; --i) {
    if (num1.number_[i] < num2.number_[i]) {
      return flag;
    }
    if (num1.number_[i] > num2.number_[i]) {
      return !flag;
    }
  }
  return !flag;
}
bool operator>(const BigInteger& num1, const BigInteger& num2) {
  bool flag = true;
  for (int64_t i = num1.kCapacity; i != -1; --i) {
    if (num1.number_[i] > num2.number_[i]) {
      return flag;
    }
    if (num1.number_[i] < num2.number_[i]) {
      return !flag;
    }
  }
  return !flag;
}

bool operator<=(const BigInteger& num1, const BigInteger& num2) {
  bool flag = true;
  if ((num1 < num2) || !(num1 < num2) && !(num1 > num2)) {
    return flag;
  }
  return !flag;
}
bool operator>=(const BigInteger& num1, const BigInteger& num2) {
  bool flag = true;
  if ((num1 > num2) || !(num1 < num2) && !(num1 > num2)) {
    return flag;
  }
  return !flag;
}

bool operator==(const BigInteger& num1, const BigInteger& num2) {
  bool flag = true;
  if (!(num1 < num2) && !(num1 > num2)) {
    return flag;
  }
  return !flag;
}
bool operator!=(const BigInteger& num1, const BigInteger& num2) {
  bool flag = true;
  if (num1 == num2) {
    return !flag;
  }
  return flag;
}

bool operator<=(const int64_t& num1, const BigInteger& num2) {
  bool flag = true;
  big_num1 = BigInteger(num1);
  if ((big_num1 < num2) || !(big_num1 < num2) && !(big_num1 > num2)) {
    return flag;
  }
  return !flag;
}
bool operator>=(const int64_t& num1, const BigInteger& num2) {
  bool flag = true;
  big_num1 = BigInteger(num1);
  if ((big_num1 > num2) || !(big_num1 < num2) && !(big_num1 > num2)) {
    return flag;
  }
  return !flag;
}

bool operator==(const int64_t& num1, const BigInteger& num2) {
  bool flag = true;
  big_num1 = BigInteger(num1);
  if (!(big_num1 < num2) && !(big_num1 > num2)) {
    return flag;
  }
  return !flag;
}
bool operator!=(const int64_t& num1, const BigInteger& num2) {
  bool flag = true;
  big_num1 = BigInteger(num1);
  if (big_num1 == num2) {
    return !flag;
  }
  return flag;
}

std::istream& operator>>(std::istream&, BigInteger& num) {
  char str[num.kLimit]{};
  is >> str;
  num = BigInteger(str);
  return is;
}
std::ostream& operator<<(std::ostream&, const BigInteger& num) {
  int64_t stop = num.kCapacity - 1;
  while (stop > 0) {
    if (num.number_[stop] != 0) {
      break;
    }
    --stop;
  }
  for (int64_t i = stop; i != 0; --i) {
    os << num.number_[i];
  }
  return os;
}