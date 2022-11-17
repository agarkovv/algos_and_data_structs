#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <limits>

#include "sum.h"
#include "sum.h"  // check include guards

TEST_CASE("PositiveSmall", "[Sum]") {
  REQUIRE(Sum(2, 5) == 7);
  REQUIRE(Sum(6, 4) == 10);
}

TEST_CASE("NegativeSmall", "[Sum]") {
  REQUIRE(Sum(-3, -6) == -9);
  REQUIRE(Sum(-7, -5) == -12);
}

TEST_CASE("MixSmall", "[Sum]") {
  REQUIRE(Sum(-4, 5) == 1);
  REQUIRE(Sum(4, -6) == -2);
  REQUIRE(Sum(-11, 11) == 0);
}

TEST_CASE("PositiveLarge", "[Sum]") {
  const int32_t max_value = std::numeric_limits<int32_t>::max();
  REQUIRE(Sum(max_value, max_value) == int64_t{max_value} + int64_t{max_value});
  REQUIRE(Sum(max_value, max_value / 2) == int64_t{max_value / 2} + int64_t{max_value});
  REQUIRE(Sum(5, max_value) == int64_t{max_value} + int64_t{5});
}

TEST_CASE("NegativeLarge", "[Sum]") {
  const int32_t max_value = std::numeric_limits<int32_t>::max();
  REQUIRE(Sum(-max_value, -max_value) == int64_t{-max_value} + int64_t{-max_value});
  REQUIRE(Sum(-max_value / 2, -max_value) == int64_t{-max_value / 2} + int64_t{-max_value});
  REQUIRE(Sum(-5, -max_value) == int64_t{-max_value} + int64_t{-5});
}

TEST_CASE("MixLarge", "[Sum]") {
  const int32_t max_value = std::numeric_limits<int32_t>::max();
  REQUIRE(Sum(-max_value, max_value) == int64_t{-max_value} + int64_t{max_value});
  REQUIRE(Sum(-max_value / 2, max_value) == int64_t{-max_value / 2} + int64_t{max_value});
  REQUIRE(Sum(-max_value, max_value / 2) == int64_t{max_value / 2} + int64_t{-max_value});
  REQUIRE(Sum(5, -max_value) == int64_t{-max_value} + int64_t{5});
  REQUIRE(Sum(max_value, -5) == int64_t{-5} + int64_t{max_value});
}
