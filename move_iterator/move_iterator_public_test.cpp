#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <list>

#include "move_iterator.h"
#include "move_iterator.h"  // check include guards

TEST_CASE("Read", "[MoveIterator]") {
  std::vector<std::unique_ptr<int>> v;
  v.push_back(std::make_unique<int>(1));
  v.push_back(std::make_unique<int>(2));
  v.push_back(std::make_unique<int>(3));
  MoveIterator<std::vector<std::unique_ptr<int>>::iterator> mit;
  mit = MakeMoveIterator(v.begin() + 1);
  REQUIRE(mit.Base() == v.begin() + 1);

  REQUIRE(*mit == v[1]);
  REQUIRE(mit[1] == v[2]);

  auto ptr = *mit;
  REQUIRE(*ptr == 2);
  REQUIRE(*mit == nullptr);

  ptr = mit[1];
  REQUIRE(*ptr == 3);
  REQUIRE(mit[1] == nullptr);
}

TEST_CASE("Increment", "[MoveIterator]") {
  std::list<std::unique_ptr<int>> l;
  l.push_back(std::make_unique<int>(1));
  l.push_back(std::make_unique<int>(2));
  l.push_back(std::make_unique<int>(3));
  auto mit = MakeMoveIterator(l.begin());
  ++mit;
  REQUIRE(*mit == *std::next(l.begin(), 1));
  REQUIRE(mit.Base() == std::next(l.begin(), 1));
  mit++;
  REQUIRE(*mit == *std::next(l.begin(), 2));
  REQUIRE(mit.Base() == std::next(l.begin(), 2));
  ++mit = MakeMoveIterator(l.begin());
  REQUIRE(mit.Base() == l.begin());
}

TEST_CASE("Decrement", "[MoveIterator]") {
  std::list<std::unique_ptr<int>> l;
  l.push_back(std::make_unique<int>(1));
  l.push_back(std::make_unique<int>(2));
  l.push_back(std::make_unique<int>(3));
  auto mit = MakeMoveIterator(l.end());
  --mit;
  REQUIRE(*mit == *std::next(l.begin(), 2));
  REQUIRE(mit.Base() == std::next(l.begin(), 2));
  mit--;
  REQUIRE(*mit == *std::next(l.begin(), 1));
  REQUIRE(mit.Base() == std::next(l.begin(), 1));
  --mit = MakeMoveIterator(l.end());
  REQUIRE(mit.Base() == l.end());
}

TEST_CASE("RandomAccess", "[MoveIterator]") {
  const std::vector<int> v{1, 2, 3, 4, 5};
  auto mit = MakeMoveIterator(v.end());
  mit -= 3;
  REQUIRE(*mit == 3);
  REQUIRE(mit.Base() == std::next(v.begin(), 2));

  mit += 2;
  REQUIRE(*mit == 5);
  REQUIRE(mit.Base() == std::next(v.begin(), 4));

  (mit -= 1) = MakeMoveIterator(std::prev(v.end(), 1));
  REQUIRE(*mit == 5);
  REQUIRE(mit.Base() == std::prev(v.end(), 1));

  (mit += 1) = MakeMoveIterator(std::next(v.begin(), 3));
  REQUIRE(*mit == 4);
  REQUIRE(mit.Base() == std::next(v.begin(), 3));

  REQUIRE(*(mit + 1) == 5);
  REQUIRE((mit + 1).Base() == std::next(v.begin(), 4));

  REQUIRE(*(mit - 1) == 3);
  REQUIRE((mit - 1).Base() == std::next(v.begin(), 2));

  REQUIRE(*(-2 + mit) == 2);
  REQUIRE((-2 + mit).Base() == std::next(v.begin(), 1));

  REQUIRE(MakeMoveIterator(std::next(v.begin(), 4)) - MakeMoveIterator(std::next(v.begin(), 1)) == 3);
}

TEST_CASE("Comparisons", "[MoveIterator]") {
  std::vector<int> v{1, 2, 3, 4, 5};
  auto x = MakeMoveIterator(std::next(v.begin(), 2));
  auto y = MakeMoveIterator(std::next(v.begin(), 2));
  auto z = MakeMoveIterator(std::next(v.begin(), 4));

  REQUIRE(x < z);
  REQUIRE_FALSE(z < x);
  REQUIRE_FALSE(x < y);

  REQUIRE_FALSE(x > z);
  REQUIRE(z > x);
  REQUIRE_FALSE(x > y);

  REQUIRE(x <= z);
  REQUIRE_FALSE(z <= x);
  REQUIRE(x <= y);

  REQUIRE_FALSE(x >= z);
  REQUIRE(z >= x);
  REQUIRE(x >= y);

  REQUIRE_FALSE(x == z);
  REQUIRE_FALSE(z == x);
  REQUIRE(x == y);

  REQUIRE(x != z);
  REQUIRE(z != x);
  REQUIRE_FALSE(x != y);
}
