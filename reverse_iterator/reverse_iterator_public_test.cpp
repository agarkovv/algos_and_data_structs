#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <list>

#include "reverse_iterator.h"
#include "reverse_iterator.h"  // check include guards

struct A {
  int x;
};

TEST_CASE("Read", "[ReverseIterator]") {
  std::vector<A> v{{1}, {2}, {3}, {4}, {5}};
  ReverseIterator<std::vector<A>::iterator> rit;
  rit = MakeReverseIterator(v.begin() + 2);
  REQUIRE(rit.Base() == v.begin() + 2);
  REQUIRE((*rit).x == 2);
  REQUIRE(rit->x == 2);
  REQUIRE(rit[1].x == 1);
  REQUIRE(rit[-2].x == 4);
}

TEST_CASE("Write", "[ReverseIterator]") {
  std::vector<A> v{{1}, {2}, {3}, {4}, {5}};
  const ReverseIterator<std::vector<A>::iterator> rit(v.begin() + 2);
  REQUIRE(rit.Base() == v.begin() + 2);
  (*rit).x = -2;
  REQUIRE(v[1].x == -2);
  (*rit).x = -4;
  REQUIRE(v[1].x == -4);
  rit[1].x = -1;
  REQUIRE(v[0].x == -1);
  rit[-2].x = -5;
  REQUIRE(v[3].x == -5);
}

TEST_CASE("Increment", "[ReverseIterator]") {
  const std::list<int> l{1, 2, 3, 4, 5};
  auto rit = MakeReverseIterator(l.end());
  ++rit;
  REQUIRE(*rit == 4);
  REQUIRE(rit.Base() == std::next(l.begin(), 4));
  rit++;
  REQUIRE(*rit == 3);
  REQUIRE(rit.Base() == std::next(l.begin(), 3));
  ++rit;
  rit++;
  REQUIRE(rit.Base() == std::next(l.begin(), 1));
  ++rit = MakeReverseIterator(std::next(l.begin(), 2));
  REQUIRE(rit.Base() == std::next(l.begin(), 2));
}

TEST_CASE("Decrement", "[ReverseIterator]") {
  const std::list<int> l{1, 2, 3, 4, 5};
  auto rit = MakeReverseIterator(l.begin());
  --rit;
  REQUIRE(*rit == 1);
  REQUIRE(rit.Base() == std::next(l.begin(), 1));
  rit--;
  REQUIRE(*rit == 2);
  REQUIRE(rit.Base() == std::next(l.begin(), 2));
  --rit;
  rit--;
  REQUIRE(rit.Base() == std::next(l.begin(), 4));
  --rit = MakeReverseIterator(std::next(l.begin(), 2));
  REQUIRE(rit.Base() == std::next(l.begin(), 2));
}

TEST_CASE("RandomAccess", "[ReverseIterator]") {
  const std::vector<int> v{1, 2, 3, 4, 5};
  auto rit = MakeReverseIterator(v.end());
  rit += 3;
  REQUIRE(*rit == 2);
  REQUIRE(rit.Base() == std::next(v.begin(), 2));

  rit -= 2;
  REQUIRE(*rit == 4);
  REQUIRE(rit.Base() == std::next(v.begin(), 4));

  (rit -= 1) = MakeReverseIterator(v.end());
  REQUIRE(*rit == 5);
  REQUIRE(rit.Base() == v.end());

  (rit += 1) = MakeReverseIterator(std::next(v.begin(), 3));
  REQUIRE(*rit == 3);
  REQUIRE(rit.Base() == std::next(v.begin(), 3));

  REQUIRE(*(rit + 2) == 1);
  REQUIRE((rit + 2).Base() == std::next(v.begin(), 1));

  REQUIRE(*(rit - 1) == 4);
  REQUIRE((rit - 1).Base() == std::next(v.begin(), 4));

  REQUIRE(*(2 + rit) == 1);
  REQUIRE((2 + rit).Base() == std::next(v.begin(), 1));

  REQUIRE(MakeReverseIterator(std::next(v.begin(), 2)) - MakeReverseIterator(v.end()) == 3);
}

TEST_CASE("Comparisons", "[ReverseIterator]") {
  std::vector<int> v{1, 2, 3, 4, 5};
  auto x = MakeReverseIterator(std::next(v.begin(), 2));
  auto y = MakeReverseIterator(std::next(v.begin(), 2));
  auto z = MakeReverseIterator(std::next(v.begin(), 4));

  REQUIRE(z < x);
  REQUIRE_FALSE(x < z);
  REQUIRE_FALSE(x < y);

  REQUIRE_FALSE(z > x);
  REQUIRE(x > z);
  REQUIRE_FALSE(x > y);

  REQUIRE(z <= x);
  REQUIRE_FALSE(x <= z);
  REQUIRE(x <= y);

  REQUIRE_FALSE(z >= x);
  REQUIRE(x >= z);
  REQUIRE(x >= y);

  REQUIRE_FALSE(z == x);
  REQUIRE_FALSE(x == z);
  REQUIRE(x == y);

  REQUIRE(z != x);
  REQUIRE(x != z);
  REQUIRE_FALSE(x != y);
}
