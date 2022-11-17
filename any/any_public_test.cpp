#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

#include "any.h"
#include "any.h"  // check include guards

TEST_CASE("Constructors") {
  const Any a;  // no CE check

  const Any b(11);
  REQUIRE(AnyCast<int>(b) == 11);

  Any c(b);
  REQUIRE(AnyCast<int>(b) == 11);
  REQUIRE(AnyCast<int>(c) == 11);

  const Any d(std::move(c));
  REQUIRE(AnyCast<int>(d) == 11);

  const Any e(std::vector<int>(10));
  REQUIRE(AnyCast<std::vector<int>>(e).size() == 10);
}

TEST_CASE("Assignment") {
  Any a;
  Any b;

  {  // value assignment
    a = 11;
    REQUIRE(AnyCast<int>(a) == 11);
  }

  {  // reassigning
    a = &a;
    REQUIRE(AnyCast<Any*>(a) == &a);
  }

  {  // copy assignment
    b = a;
    REQUIRE(AnyCast<Any*>(b) == &a);
  }

  {  // copy is independent
    b = 1.0;
    REQUIRE(AnyCast<Any*>(a) == &a);
    REQUIRE(AnyCast<double>(b) == 1.0);
  }

  {  // move
    a = std::move(b);
    REQUIRE(AnyCast<double>(a) == 1.0);
  }

  {  // self-assignment
    a = a;
    REQUIRE(AnyCast<double>(a) == 1.0);
  }
}

TEST_CASE("Swap") {
  Any a = 1;
  Any b = &a;

  a.Swap(b);
  REQUIRE(AnyCast<Any*>(a) == &a);
  REQUIRE(AnyCast<int>(b) == 1);

  b.Swap(b);
  REQUIRE(AnyCast<int>(b) == 1);
}

TEST_CASE("HasValue") {
  Any a;
  REQUIRE_FALSE(a.HasValue());

  Any b = 11;
  REQUIRE(b.HasValue());

  a = b;
  REQUIRE(a.HasValue());
  REQUIRE(b.HasValue());

  a = std::move(b);
  REQUIRE(a.HasValue());
  REQUIRE_FALSE(b.HasValue());  // NOLINT check moved valid state

  a.Reset();
  REQUIRE_FALSE(a.HasValue());
}

TEST_CASE("BadAnyCast") {
  Any a;
  REQUIRE_THROWS_AS(AnyCast<int>(a), BadAnyCast);  // NOLINT

  a = 11;
  REQUIRE_THROWS_AS(AnyCast<char*>(a), BadAnyCast);  // NOLINT
}
