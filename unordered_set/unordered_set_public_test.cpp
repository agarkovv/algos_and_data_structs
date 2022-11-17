#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <forward_list>
#include <vector>
#include <sstream>

#include "unordered_set.h"
#include "unordered_set.h"  // check include guards

TEST_CASE("DefaultConstructor", "[Constructors]") {
  const UnorderedSet<int> us;
  REQUIRE(us.Size() == 0u);
  REQUIRE(us.Empty());
  REQUIRE(us.BucketCount() == 0u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }
  for (size_t i = 0u; i < 10u; ++i) {
    REQUIRE(us.BucketSize(i) == 0u);
  }
  REQUIRE(us.LoadFactor() == Approx(0.0f));
}

TEST_CASE("BucketCountConstructor", "[Constructors]") {
  const UnorderedSet<std::string> us(5u);
  REQUIRE(us.Size() == 0u);
  REQUIRE(us.Empty());
  REQUIRE(us.BucketCount() == 5u);
  for (int i = 0; i < 10; ++i) {
    const auto str = std::to_string(i);
    const auto bucket = std::hash<std::string>{}(str) % 5u;
    REQUIRE(us.Bucket(str) == bucket);
    REQUIRE_FALSE(us.Find(str));
  }
  for (size_t i = 0u; i < 10u; ++i) {
    REQUIRE(us.BucketSize(i) == 0u);
  }
  REQUIRE(us.LoadFactor() == Approx(0.0f));
}

TEST_CASE("RangeConstructor", "[Constructors]") {
  std::forward_list<int> fl{0, 1, 2, 3};
  const UnorderedSet<int> us(fl.begin(), fl.end());
  REQUIRE(us.Size() == 4u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 4u);
  for (int i = 0; i < 10; ++i) {
    const auto bucket = std::hash<int>{}(i) % 4u;
    REQUIRE(us.Bucket(i) == bucket);
    REQUIRE(us.Find(i) == (i < 4));
  }
  size_t bucket_size_sum = 0;
  for (size_t i = 0u; i < 10u; ++i) {
    bucket_size_sum += us.BucketSize(i);
  }
  REQUIRE(bucket_size_sum == 4u);
  REQUIRE(us.LoadFactor() == Approx(1.0f));
}

TEST_CASE("Copy", "[Constructors]") {
  std::forward_list<int> fl{0, 1, 2, 3};
  const UnorderedSet<int> us(fl.begin(), fl.end());
  auto us_copy = us;

  REQUIRE(us.Size() == 4u);
  REQUIRE(us.Size() == us_copy.Size());
  REQUIRE(!us.Empty());
  REQUIRE(!us_copy.Empty());
  REQUIRE(us.BucketCount() == 4u);
  REQUIRE(us.BucketCount() == us_copy.BucketCount());
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i) == (i < 4));
    REQUIRE(us_copy.Find(i) == (i < 4));
  }

  us_copy.Clear();
  REQUIRE(us_copy.Size() == 0u);
  REQUIRE(us_copy.Empty());
  for (int i = 0; i < 10; ++i) {
    REQUIRE_FALSE(us_copy.Find(i));
  }

  REQUIRE(us.Size() == 4u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 4u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i) == (i < 4));
  }
}

TEST_CASE("Move", "[Constructors]") {
  std::forward_list<int> fl{0, 1, 2, 3};
  UnorderedSet<int> us(fl.begin(), fl.end());
  const auto us_copy = std::move(us);

  REQUIRE(us.Size() == 0);
  REQUIRE(us.Empty());
  REQUIRE(us.BucketCount() == 0u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }

  REQUIRE(us_copy.Size() == 4u);
  REQUIRE_FALSE(us_copy.Empty());
  REQUIRE(us_copy.BucketCount() == 4u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us_copy.Find(i) == (i < 4));
  }
}
// Size empty clear find bucket bucket_count bucket_size load_factor rehash reserve

TEST_CASE("Copy Assignment", "[Assignment]") {
  std::forward_list<int> fl{0, 1, 2, 3};
  const UnorderedSet<int> us(fl.begin(), fl.end());
  UnorderedSet<int> us_copy(fl.begin(), std::next(fl.begin()));
  us_copy = us;

  REQUIRE(us.Size() == 4u);
  REQUIRE(us.Size() == us_copy.Size());
  REQUIRE(!us.Empty());
  REQUIRE(!us_copy.Empty());
  REQUIRE(us.BucketCount() == 4u);
  REQUIRE(us.BucketCount() == us_copy.BucketCount());
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i) == (i < 4));
    REQUIRE(us_copy.Find(i) == (i < 4));
  }

  us_copy.Clear();
  REQUIRE(us_copy.Size() == 0u);
  REQUIRE(us_copy.Empty());
  for (int i = 0; i < 10; ++i) {
    REQUIRE_FALSE(us_copy.Find(i));
  }

  REQUIRE(us.Size() == 4u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 4u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i) == (i < 4));
  }
}

TEST_CASE("Move Assignment", "[Assignment]") {
  std::forward_list<int> fl{0, 1, 2, 3};
  UnorderedSet<int> us(fl.begin(), fl.end());
  UnorderedSet<int> us_copy(fl.begin(), std::next(fl.begin()));
  us_copy = std::move(us);

  REQUIRE(us.Size() == 0);
  REQUIRE(us.Empty());
  REQUIRE(us.BucketCount() == 0u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }

  REQUIRE(us_copy.Size() == 4u);
  REQUIRE_FALSE(us_copy.Empty());
  REQUIRE(us_copy.BucketCount() == 4u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us_copy.Find(i) == (i < 4));
  }
}

TEST_CASE("Insert", "[Usage]") {
  UnorderedSet<std::string> us;
  size_t expected_capacity = 1;
  for (size_t i = 0u; i < 10u; ++i) {
    const auto str = std::to_string(i);
    if (i % 2u == 0u) {
      us.Insert(str);
    } else {
      us.Insert(std::move(str));
    }
    if (i + 1 > expected_capacity) {
      expected_capacity *= 2;
    }
    REQUIRE(us.Size() == i + 1);
    REQUIRE_FALSE(us.Empty());
    REQUIRE(us.BucketCount() == expected_capacity);
    REQUIRE(us.LoadFactor() == Approx(static_cast<float>(i + 1) / expected_capacity));
  }
  for (size_t i = 0; i < 10u; ++i) {
    const auto str = std::to_string(i);
    REQUIRE(us.Find(str));
  }
  for (size_t i = 10u; i < 20u; ++i) {
    const auto str = std::to_string(i);
    REQUIRE_FALSE(us.Find(str));
  }
}

TEST_CASE("Erase", "[Usage]") {
  std::forward_list<size_t> fl{0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
  UnorderedSet<size_t> us(fl.begin(), fl.end());
  for (size_t i = 0; i < 5; ++i) {
    us.Erase(2 * i);
    const auto size = 10u - i - 1u;
    REQUIRE(us.Size() == size);
    REQUIRE_FALSE(us.Empty());
  }
  for (size_t i = 0; i < 5; ++i) {
    REQUIRE(us.Find(2 * i + 1));
    REQUIRE_FALSE(us.Find(2 * i));
  }
}

TEST_CASE("Rehash", "[Bucket]") {
  UnorderedSet<int> us;
  us.Rehash(11u);

  REQUIRE(us.Size() == 0u);
  REQUIRE(us.Empty());
  REQUIRE(us.BucketCount() == 11u);
  for (int i = 0; i < 10; ++i) {
    const auto bucket = std::hash<int>{}(i) % 11u;
    REQUIRE(us.Bucket(i) == bucket);
    REQUIRE_FALSE(us.Find(i));
  }

  for (int i = 0; i < 10; ++i) {
    us.Insert(i);
  }

  REQUIRE(us.Size() == 10u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 11u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i));
  }
  for (int i = 10; i < 20; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }

  us.Rehash(5u);

  REQUIRE(us.Size() == 10u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 11u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i));
  }
  for (int i = 10; i < 20; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }

  us.Rehash(10u);

  REQUIRE(us.Size() == 10u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 10u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i));
  }
  for (int i = 10; i < 20; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }

  us.Rehash(50u);

  REQUIRE(us.Size() == 10u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 50u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i));
  }
  for (int i = 10; i < 20; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }
}

TEST_CASE("Reserve", "[Bucket]") {
  UnorderedSet<int> us;
  us.Reserve(11u);

  REQUIRE(us.Size() == 0u);
  REQUIRE(us.Empty());
  REQUIRE(us.BucketCount() == 11u);
  for (int i = 0; i < 10; ++i) {
    const auto bucket = std::hash<int>{}(i) % 11u;
    REQUIRE(us.Bucket(i) == bucket);
    REQUIRE_FALSE(us.Find(i));
  }

  for (int i = 0; i < 10; ++i) {
    us.Insert(i);
  }

  REQUIRE(us.Size() == 10u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 11u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i));
  }
  for (int i = 10; i < 20; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }

  us.Reserve(5u);

  REQUIRE(us.Size() == 10u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 11u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i));
  }
  for (int i = 10; i < 20; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }

  us.Reserve(10u);

  REQUIRE(us.Size() == 10u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 11u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i));
  }
  for (int i = 10; i < 20; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }

  us.Reserve(50u);

  REQUIRE(us.Size() == 10u);
  REQUIRE_FALSE(us.Empty());
  REQUIRE(us.BucketCount() == 50u);
  for (int i = 0; i < 10; ++i) {
    REQUIRE(us.Find(i));
  }
  for (int i = 10; i < 20; ++i) {
    REQUIRE_FALSE(us.Find(i));
  }
}

#ifdef ITERATOR_IMPLEMENTED

TEST_CASE("Iterators", "[UnorderedSet]") {
  using DifferenceType = UnorderedSet<int>::DifferenceType;
  using Iterator = UnorderedSet<int>::Iterator;
  using ConstIterator = UnorderedSet<int>::ConstIterator;

  static_assert(std::is_integral_v<DifferenceType>);
  static_assert(std::is_base_of_v<std::forward_iterator_tag, std::iterator_traits<Iterator>::iterator_category>);
  static_assert(std::is_convertible_v<Iterator, ConstIterator>);

  std::forward_list<int> fl{1, 2};
  UnorderedSet<int> us(fl.begin(), fl.end());
  const UnorderedSet<int> const_us(fl.begin(), fl.end());

  static_assert(std::is_same_v<decltype(us.begin()), Iterator>);
  static_assert(std::is_same_v<decltype(us.end()), Iterator>);
  static_assert(std::is_same_v<decltype(us.cbegin()), ConstIterator>);
  static_assert(std::is_same_v<decltype(us.cend()), ConstIterator>);
  static_assert(std::is_same_v<decltype(const_us.begin()), ConstIterator>);
  static_assert(std::is_same_v<decltype(const_us.end()), ConstIterator>);
  static_assert(std::is_same_v<decltype(const_us.cbegin()), ConstIterator>);
  static_assert(std::is_same_v<decltype(const_us.cend()), ConstIterator>);

  std::ostringstream oss;
  for (const auto& value : us) {
    oss << value << ' ';
  }
  for (const auto& value : const_us) {
    oss << value << ' ';
  }
  REQUIRE(((oss.str() == "1 2 1 2 ") || (oss.str() == "2 1 2 1 ")));
}

#endif

#ifdef FORWARD_LIST_IMPLEMENTED

TEST_CASE("ForwardList", "[UnorderedSet]") {
  REQUIRE((std::is_same_v<UnorderedSet<int>::Iterator, std::forward_list<int>::const_iterator>));
  REQUIRE((std::is_same_v<UnorderedSet<int>::ConstIterator, std::forward_list<int>::const_iterator>));
}

#endif
