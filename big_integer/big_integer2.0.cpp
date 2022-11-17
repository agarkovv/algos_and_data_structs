#include "big_integer.h"

BigInteger::BigInteger(const char* str) : flag(false), size(10), chunk_count(0), number(nullptr) {

  size_t str_size = strlen(str);
  if (*(str) == '-') {
    flag = true;
  }

  number = new int64_t[size]{};
  int64_t big_int_index = 0;

  const int64_t chunksize = 9;
  char chunk[chunksize + 1]{};
  int64_t chunk_index = 0;

  for (int64_t i = str_size - 1; i != -1 && *(str + i) != '-'; --i) {
    chunk[chunk_index++] = str[i];
    if (chunk_index == chunksize) {
      chunk_index = 0;
      SwapChunk(chunk, chunksize);
      number[big_int_index++] = Atoi(chunk, chunksize);
      ++chunk_count;
      if (chunk_count == size) {
        if (size == kLimit) {
          throw BigIntegerOverflow();
        }
        int64_t new_size = size * 2;
        auto* new_number = new int64_t[new_size]{};
        for (int64_t j = 0; j < size; ++j) {
          new_number[j] = number[j];
        }
        delete[] number;
        number = new_number;
        size = new_size;
      }
    }
  }
  if (chunk_index != 0) {
    chunk[chunk_index] = '\0';
    SwapChunk(chunk, chunk_index);
    number[big_int_index++] = Atoi(chunk, chunk_index);
    ++chunk_count;
    if (chunk_count == size) {
      if (size == kLimit) {
        throw BigIntegerOverflow();
      }
      int64_t new_size = size * 2;
      auto* new_number = new int64_t[new_size]{};
      for (int64_t j = 0; j < size; ++j) {
        new_number[j] = number[j];
      }
      delete[] number;
      number = new_number;
      size = new_size;
    }
  }
}  // Ok. Creating new big_int, which is based on string
// As a result we get array, consisting of elems in reversed order
BigInteger::BigInteger(int64_t num) : flag(false), size(10), chunk_count(0), number(nullptr) {
  if (num < 0) {
    flag = true;
    num *= -1;
  }
  number = new int64_t[size]{};
  const int64_t chunksize = 9;
  number[0] = num % kModulo;
  number[1] = num / kModulo;
}  //Ok. Just creating new big_int, which is based on int32_t (or int64_t)
// In the worst case we can get array, consisting of two elems
void BigInteger::SetCount(BigInteger& x, BigInteger y) {
  if (x.size < y.size) {
    auto* new_number_x = new int64_t[y.size]{};
    for (int64_t i = 0; i < x.size; ++i) {
      new_number_x[i] = x.number[i];
    }
    delete[] x.number;
    x.number = new_number_x;
    x.size = y.size;
  }
  if (y.size < x.size) {
    auto* new_number_y = new int64_t[x.size]{};
    for (int64_t i = 0; i < y.size; ++i) {
      new_number_y[i] = y.number[i];
    }
    delete[] y.number;
    y.number = new_number_y;
    y.size = x.size;
  }
  if (x.chunk_count < y.chunk_count) {
    x.chunk_count = y.chunk_count;
  }
}
bool IsNegative(const BigInteger& num) {
  return num.flag;
} //  Ok
BigInteger operator+(BigInteger& num) {
  return num;
} //  (!) No any ref
BigInteger operator-(BigInteger& num) {
  num.flag = !num.flag;
  return num;
} //  (!) No any ref

void BigInteger::SwapChunk(char chunk[], const int64_t chunksize) {
  char tmp = '0';
  for (int64_t i = 0, j = chunksize - 1; i < chunksize / 2; ++i, --j) {
    tmp = chunk[i];
    chunk[i] = chunk[j];
    chunk[j] = tmp;
  }
}  // Ok (just reversing char array)
int64_t BigInteger::Atoi(char chunk[], const int64_t chunksize) {
  int64_t number = 0;
  for (int64_t i = 0; i < chunksize; ++i) {
    number = number * 10 + (chunk[i] - '0');
  }
  return number;
}  // Ok (char array to int64_t num)

BigInteger operator+(BigInteger& x, BigInteger& y) {
  if (x.flag) {
    return -((-x) - y);
  }
  if (y.flag) {
    return x - (-y);
  }
  x.SetCount(x, y);
  int64_t carry = 0;
  for (int64_t i = 0; i < x.chunk_count; ++i) {
    int64_t tmp = carry + x.number[i] + y.number[i];
    x.number[i] = tmp % x.kModulo;
    carry = tmp / x.kModulo;
  }
  if (carry != 0) {
    x.number[x.chunk_count] = carry;
    ++x.chunk_count;
    if (x.chunk_count == x.size) {
      int64_t64_t new_size = x.size * 2;
      auto* new_number = new int64_t[new_size]{};
      for (int64_t j = 0; j < x.size; ++j) {
        new_number[j] = x.number[j];
      }
      delete[] x.number;
      x.number = new_number;
    }
  }
  return x;
}
BigInteger operator-(BigInteger& x, BigInteger& y) {
  x.SetCount(x, y);
  if (x.flag) {
    return -((-x) + y);
  }
  if (y.flag) {
    return x + (-y);
  }
  if (x > y) {
    int64_t carry = 0;
    for (int64_t i = 0; i < x.chunk_count; ++i) {
      int64_t tmp = (x.kModulo + x.number[i]) - (y.number[i] + carry);
      x.number[i] = tmp % x.kModulo;
      carry = tmp / x.kModulo;
    }
    // FixChunks();
    return x;
  }
  return -(y - x);
}
bool operator<(BigInteger& x, BigInteger& y) {
  bool flag = true;
  x.SetCount(x, y);
  for (int64_t i = x.chunk_count - 1; i != -1; --i) {
    if (x.number[i] < y.number[i]) {
      return flag;
    }
    if (x.number[i] > y.number[i]) {
      return !flag;
    }
  }
  return !flag;
}
bool operator>(BigInteger& x, BigInteger& y) {
  bool flag = true;
  x.SetCount(x, y);
  for (int64_t i = x.chunk_count - 1; i != -1; --i) {
    if (x.number[i] > y.number[i]) {
      return flag;
    }
    if (x.number[i] < y.number[i]) {
      return !flag;
    }
  }
  return !flag;
}
bool operator<=(BigInteger& x, BigInteger& y) {
  bool flag = true;
  x.SetCount(x, y);
  for (int64_t i = x.chunk_count - 1; i != -1; --i) {
    if (x.number[i] < y.number[i]) {
      return flag;
    }
    if (x.number[i] < y.number[i]) {
      return !flag;
    }
  }
  return flag;
}
bool operator>=(BigInteger& x, BigInteger& y) {
  bool flag = true;
  x.SetCount(x, y);
  for (int64_t i = x.chunk_count - 1; i != -1; --i) {
    if (x.number[i] > y.number[i]) {
      return flag;
    }
    if (x.number[i] < y.number[i]) {
      return !flag;
    }
  }
  return flag;
}
bool operator==(BigInteger& x, BigInteger& y) {
  bool flag = true;
  x.SetCount(x, y);
  for (int64_t i = x.chunk_count - 1; i != -1; --i) {
    if (x.number[i] > y.number[i]) {
      return !flag;
    }
    if (x.number[i] < y.number[i]) {
      return !flag;
    }
  }
  return flag;
}
bool operator!=(BigInteger& x, BigInteger& y) {
  bool flag = true;
  x.SetCount(x, y);
  for (int64_t i = x.chunk_count - 1; i != -1; --i) {
    if (x.number[i] > y.number[i]) {
      return flag;
    }
    if (x.number[i] < y.number[i]) {
      return flag;
    }
  }
  return !flag;
}

void PrintBigInteger(BigInteger& x) {
  if (x.chunk_count == 0) {
    std::cout << "null" << std::endl;
  }
  int64_t stop_point = x.chunk_count - 1;
  for (; stop_point != -1; --stop_point) {
    if (x.number[stop_point] != 0) {
      break;
    }
  }
  std::cout << x.number[stop_point--];
  for (int64_t i = stop_point; i != -1; --i) {
    int64_t chunk_number = x.number[i];
    int64_t chunk_size = 0;
    do {
      chunk_number /= 10;
      chunk_size++;
    } while (chunk_number != 0);
    for (int64_t j = chunk_size; j < 9; ++j) {
      std::cout << 0;
    }
    std::cout << x.number[i];
  }
}
int main() {
  char number1[10001]{};
  char number2[10001]{};
  std::cin.getline(number1, 10001);
  std::cin.getline(number2, 10001);
  int64_t size1 = strlen(number1);
  int64_t size2 = strlen(number2);
  BigInteger n1(number1, size1);
  BigInteger n2(number2, size2);
  n1 = n1 + n2;
  PrintBigInteger(n1);
  delete[] n1.number;
  delete[] n2.number;
}
