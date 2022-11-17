#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iostream>

#include "rational.h"
#include "rational.h"  // check include guards

void RationalEqual(const Rational& rational, int64_t numerator, int64_t denominator) {
  REQUIRE(rational.GetNumerator() == numerator);
  REQUIRE(rational.GetDenominator() == denominator);
}

TEST_CASE("Rational", "[Public]") {
  Rational a;
  Rational b = -1;
  Rational c(2, -4);
  RationalEqual(c, -1, 2);

  a.SetNumerator(6);
  a.SetDenominator(21);
  RationalEqual(a, 2, 7);

  a += b;
  b -= c;
  c *= a;
  b /= a;

  RationalEqual(+a, -5, 7);
  RationalEqual(-b, -7, 10);
  RationalEqual(c, 5, 14);

  RationalEqual(a + c, -5, 14);
  RationalEqual(a - b, -99, 70);
  RationalEqual(b * c, 1, 4);
  RationalEqual(c / a, -1, 2);

  RationalEqual(++b, 17, 10);
  RationalEqual(b++, 17, 10);
  RationalEqual(b--, 27, 10);
  RationalEqual(--b, 7, 10);

  REQUIRE(a < b);
  REQUIRE(b > c);
  REQUIRE_FALSE(a == c);

  std::stringstream is("-7/3 4/6 7");
  is >> a >> b >> c;

  std::stringstream os;
  os << a << ' ' << b << ' ' << c;
  REQUIRE(os.str() == "-7/3 2/3 7");

  REQUIRE_THROWS_AS((void)(a / 0), RationalDivisionByZero);  // NOLINT
}
