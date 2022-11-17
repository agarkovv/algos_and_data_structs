#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <forward_list>

#include "universal_hash.h"
#include "frozen_set.h"
#include "universal_hash.h"  // check include guards
#include "frozen_set.h"      // check include guards

const auto kPrimeModulo = UniversalHash::kMaxValue + 1;
const auto kMaxArgument = 1'000'000'000u;

static constexpr bool IsPrime(uint64_t number) {
  if (number < 2) {
    return false;
  }
  if (number == 2) {
    return true;
  }
  if (number % 2 == 0) {
    return false;
  }
  for (uint64_t divisor = 3; divisor * divisor <= number; divisor += 2) {
    if (number % divisor == 0) {
      return false;
    }
  }
  return true;
}

TEST_CASE("IsPrime", "[UniversalHash]") {
  static_assert(kPrimeModulo > kMaxArgument);
  static_assert(IsPrime(kPrimeModulo));
}

TEST_CASE("HashConstructors", "[UniversalHash]") {
  {
    UniversalHash hash;
    REQUIRE(hash(0u) == 0u);
    REQUIRE(hash(111u) == 111u);
    REQUIRE(hash(123456u) == 123456u);
    REQUIRE(hash(kPrimeModulo + 1u) == 1u);
  }

  {
    UniversalHash hash(10);
    REQUIRE(hash(0u) == 0u);
    REQUIRE(hash(111u) == 1110u);
    REQUIRE(hash(123456u) == 1234560u);
    REQUIRE(hash(kPrimeModulo + 1u) == 10u);
  }

  {
    UniversalHash hash(10, 7);
    REQUIRE(hash(0u) == 7u);
    REQUIRE(hash(111u) == 1117u);
    REQUIRE(hash(123456u) == 1234567u);
    REQUIRE(hash(kPrimeModulo + 1u) == 17u);
  }
}

TEST_CASE("GenerateHash", "[UniversalHash]") {
  std::mt19937_64 generator;
  const auto first_hash = UniversalHash::GenerateHash(generator);
  const auto second_hash = UniversalHash::GenerateHash(generator);
  const auto third_hash = UniversalHash::GenerateHash(generator);

  // the probability of an accidental fail is EXTREMELY SMALL
  REQUIRE_FALSE(first_hash(0u) == second_hash(0u));
  REQUIRE_FALSE(second_hash(0u) == third_hash(0u));
  REQUIRE_FALSE(first_hash(0u) == third_hash(0u));
  REQUIRE_FALSE(first_hash(1u) == second_hash(1u));
  REQUIRE_FALSE(second_hash(1u) == third_hash(1u));
  REQUIRE_FALSE(first_hash(1u) == third_hash(1u));
  REQUIRE_FALSE(first_hash(555u) == second_hash(555u));
  REQUIRE_FALSE(second_hash(555u) == third_hash(555u));
  REQUIRE_FALSE(first_hash(555u) == third_hash(555u));
}

TEST_CASE("SetConstructors", "[FrozenSet]") {
  {
    const FrozenSet<uint32_t, UniversalHash> fs;

    REQUIRE(fs.Size() == 0u);
    REQUIRE(fs.Empty());
    REQUIRE_FALSE(fs.Find(0u));
    REQUIRE_FALSE(fs.Find(10u));
    REQUIRE_FALSE(fs.Find(100u));
    REQUIRE_FALSE(fs.Find(kMaxArgument));
  }

  {
    std::mt19937_64 generator;
    std::forward_list<uint32_t> values{0u, 100u, 1000u, 10000u, kMaxArgument};
    const FrozenSet<uint32_t, UniversalHash> fs(values.begin(), values.end(), generator);

    REQUIRE(fs.Size() == 5u);
    REQUIRE_FALSE(fs.Empty());
    REQUIRE(fs.Find(0u));
    REQUIRE_FALSE(fs.Find(10u));
    REQUIRE(fs.Find(100u));
    REQUIRE(fs.Find(kMaxArgument));
  }
}
