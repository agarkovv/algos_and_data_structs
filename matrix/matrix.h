#ifndef UNTITLED_CMAKE_BUILD_DEBUG_MATRIX_DRAFT_H_
#define UNTITLED_CMAKE_BUILD_DEBUG_MATRIX_DRAFT_H_
#include <cstddef>
#include <iostream>
#include <stdexcept>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, const size_t R, const size_t C>
class Matrix {
 public:
  T matrix[R][C];
  size_t RowsNumber() const;
  size_t ColumnsNumber() const;
  T& operator()(size_t, size_t);
  const T& operator()(size_t, size_t) const;
  T& At(size_t, size_t);
  const T& At(size_t, size_t) const;
  Matrix<T, R, C> operator+(const Matrix<T, R, C>&) const;
  Matrix<T, R, C> operator-(const Matrix<T, R, C>&) const;
  Matrix<T, R, C>& operator+=(const Matrix<T, R, C>&);
  Matrix<T, R, C>& operator-=(const Matrix<T, R, C>&);
};
template <class T, const size_t R, const size_t C>
size_t Matrix<T, R, C>::RowsNumber() const {
  return R;
}
template <class T, const size_t R, const size_t C>
size_t Matrix<T, R, C>::ColumnsNumber() const {
  return C;
}
template <class T, const size_t R, const size_t C>
T& Matrix<T, R, C>::operator()(size_t row, size_t col) {
  return matrix[row][col];
}
template <class T, const size_t R, const size_t C>
const T& Matrix<T, R, C>::operator()(size_t row, size_t col) const {
  return matrix[row][col];
}
template <class T, const size_t R, const size_t C>
T& Matrix<T, R, C>::At(size_t row, size_t col) {
  if (row >= R || col >= C) {
    throw MatrixOutOfRange{};
  }
  return matrix[row][col];
}
template <class T, const size_t R, const size_t C>
const T& Matrix<T, R, C>::At(size_t row, size_t col) const {
  if (row >= R || col >= C) {
    throw MatrixOutOfRange{};
  }
  return matrix[row][col];
}
template <class T, const size_t R, const size_t C>
Matrix<T, C, R> GetTransposed(const Matrix<T, R, C> m) {
  Matrix<T, C, R> m_transposed;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      m_transposed.matrix[j][i] = m.matrix[i][j];
    }
  }
  return m_transposed;
}
template <class T, const size_t R, const size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator+(const Matrix<T, R, C>& m) const {
  Matrix<T, R, C> tmp;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      tmp.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
    }
  }
  return tmp;
}
template <class T, const size_t R, const size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator-(const Matrix<T, R, C>& m) const {
  Matrix<T, R, C> tmp;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      tmp.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];
    }
  }
  return tmp;
}
template <class T, const size_t R, const size_t C, const size_t P>
Matrix<T, R, P> operator*(const Matrix<T, R, C>& m1, const Matrix<T, C, P>& m2) {
  Matrix<T, R, P> tmp;
  for (size_t i = 0; i < P; ++i) {
    for (size_t j = 0; j < R; ++j) {
      tmp.matrix[j][i] = 0;
      for (size_t k = 0; k < C; ++k) {
        tmp.matrix[j][i] += m1.matrix[j][k] * m2.matrix[k][i];
      }
    }
  }
  return tmp;
}
template <class T, const size_t R, const size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator+=(const Matrix<T, R, C>& m) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      this->matrix[i][j] += m.matrix[i][j];
    }
  }
  return *this;
}
template <class T, const size_t R, const size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator-=(const Matrix<T, R, C>& m) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      this->matrix[i][j] -= m.matrix[i][j];
    }
  }
  return *this;
}
template <class T, const size_t R, const size_t C, const size_t P>
Matrix<T, R, P>& operator*=(Matrix<T, R, C>& m1, const Matrix<T, C, P>& m2) {
  Matrix<T, R, P> tmp;
  for (size_t i = 0; i < P; ++i) {
    for (size_t j = 0; j < R; ++j) {
      tmp.matrix[j][i] = 0;
      for (size_t k = 0; k < C; ++k) {
        tmp.matrix[j][i] += m1.matrix[j][k] * m2.matrix[k][i];
      }
    }
  }
  m1 = tmp;
  return m1;
}
template <class T, class N, const size_t R, const size_t C>
Matrix<T, R, C> operator*(const Matrix<T, R, C>& m, const N& num) {
  Matrix<T, R, C> tmp;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      tmp.matrix[i][j] = m.matrix[i][j] * num;
    }
  }
  return tmp;
}
template <class T, class N, const size_t R, const size_t C>
Matrix<T, R, C>& operator*=(Matrix<T, R, C>& m, const N& num) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      m.matrix[i][j] *= num;
    }
  }
  return m;
}
template <class T, class N, const size_t R, const size_t C>
Matrix<T, R, C> operator*(const N& num, const Matrix<T, R, C>& m) {
  Matrix<T, R, C> tmp;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      tmp.matrix[i][j] = m.matrix[i][j] * num;
    }
  }
  return tmp;
}
template <class T, class N, const size_t R, const size_t C>
Matrix<T, R, C>& operator*=(const N& num, Matrix<T, R, C>& m) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      m.matrix[i][j] *= num;
    }
  }
  return m;
}
template <class T, class N, const size_t R, const size_t C>
Matrix<T, R, C> operator/(const Matrix<T, R, C>& m, const N& num) {
  Matrix<T, R, C> tmp;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      tmp.matrix[i][j] = m.matrix[i][j] / num;
    }
  }
  return tmp;
}
template <class T, class N, const size_t R, const size_t C>
Matrix<T, R, C>& operator/=(Matrix<T, R, C>& m, const N& num) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      m.matrix[i][j] /= num;
    }
  }
  return m;
}
template <class T, class N, const size_t R, const size_t C>
Matrix<T, R, C> operator/(const N& num, const Matrix<T, R, C>& m) {
  Matrix<T, R, C> tmp;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      tmp.matrix[i][j] = m.matrix[i][j] / num;
    }
  }
  return tmp;
}
template <class T, class N, const size_t R, const size_t C>
Matrix<T, R, C>& operator/=(const N& num, Matrix<T, R, C>& m) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      m.matrix[i][j] /= num;
    }
  }
  return m;
}
template <class T, const size_t R, const size_t C>
bool operator==(Matrix<T, R, C> m1, Matrix<T, R, C> m2) {
  bool equal = true;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      if (m1.matrix[i][j] != m2.matrix[i][j]) {
        return !equal;
      }
    }
  }
  return equal;
}
template <class T, const size_t R, const size_t C>
bool operator!=(Matrix<T, R, C> m1, Matrix<T, R, C> m2) {
  bool not_equal = true;
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      if (m1.matrix[i][j] != m2.matrix[i][j]) {
        return not_equal;
      }
    }
  }
  return !not_equal;
}
template <class T, const size_t R, const size_t C>
std::istream& operator>>(std::istream& is, Matrix<T, R, C>& m) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      is >> m.matrix[i][j];
    }
  }
  return is;
}
template <class T, const size_t R, const size_t C>
std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& m) {
  for (size_t i = 0; i < R; ++i) {
    for (size_t j = 0; j < C; ++j) {
      if (j < C - 1) {
        os << m.matrix[i][j] << ' ';
      } else {
        os << m.matrix[i][j];
      }
    }
    os << '\n';
  }
  return os;
}
#endif  // UNTITLED_CMAKE_BUILD_DEBUG_MATRIX_DRAFT_H_