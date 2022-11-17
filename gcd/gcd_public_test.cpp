#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <type_traits>
#include <cstdint>

#include "gcd.h"
#include "gcd.h"  // check include guards

TEST_CASE("Gcd", "[Gcd]") {
  REQUIRE(Gcd(1, 1) == 1);
  REQUIRE(Gcd<int>(1000, 1000000) == 1000);
  REQUIRE(Gcd<uint32_t>(1000000000, 1000000) == 1000000);
  REQUIRE(Gcd<long long>(17, 7) == 1);
  REQUIRE(Gcd<int8_t>(4, 4) == 4);
  REQUIRE(Gcd<uint64_t>(25, 50) == 25);
  REQUIRE(Gcd(10, 1) == 1);
  REQUIRE(Gcd(12345, 67899) == 3);
  REQUIRE(Gcd(11111, 11112) == 1);
  REQUIRE(Gcd(std::numeric_limits<int>::max() - 1, std::numeric_limits<int>::max()) == 1);
  REQUIRE(Gcd(std::numeric_limits<int>::max() - 1, std::numeric_limits<int>::max() - 3) == 2);
}

TEST_CASE("ReturnTypeMatchesTemplateParameter", "[Gcd]") {
  using SignedType = decltype(Gcd<int32_t>(1, 1));
  using UnsignedType = decltype(Gcd<uint64_t>(1, 1));
  REQUIRE((std::is_same_v<SignedType, int32_t>));
  REQUIRE((std::is_same_v<UnsignedType, uint64_t>));
}
