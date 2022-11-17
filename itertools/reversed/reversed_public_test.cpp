#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <vector>
#include <list>

#include "reversed.h"
#include "reversed.h"  // check include guards

TEST_CASE("Empty", "[Reversed]") {
  const auto empty = std::vector<int>{};
  for ([[maybe_unused]] auto&& x : Reversed(empty)) {
    REQUIRE(false);
  }

#ifdef TEMPORARY_REVERSED_IMPLEMENTED

  for ([[maybe_unused]] auto&& x : Reversed(std::vector<int>{})) {
    REQUIRE(false);
  }

#endif  // TEMPORARY_REVERSED_IMPLEMENTED
}

TEST_CASE("Elementary", "[Reversed]") {
  auto lst = std::list{1, -1, 4, 0, 2};
  auto copy = lst;

  {
    int i = static_cast<int>(lst.size()) - 1;
    auto lst_it = lst.rbegin();
    auto copy_it = copy.rbegin();
    for (auto&& x : Reversed(lst)) {
      REQUIRE(x == *lst_it);
      ++x;
      ++(*copy_it);
      --i;
      ++lst_it;
      ++copy_it;
    }
    REQUIRE(i == -1);
    REQUIRE(lst_it == lst.rend());
    REQUIRE(copy_it == copy.rend());
    REQUIRE(lst == copy);
  }

  {
    int i = static_cast<int>(lst.size()) - 1;
    auto copy_it = copy.rbegin();
    const auto reversed = Reversed(std::as_const(lst));
    for (auto&& x : reversed) {
      REQUIRE((std::is_same_v<decltype(x), const int&>));
      REQUIRE(x == *copy_it);
      --i;
      ++copy_it;
    }
    REQUIRE(i == -1);
  }

#ifdef TEMPORARY_REVERSED_IMPLEMENTED

  {
    const auto reversed_arr = std::array{2, 0, 4, -1, 1};

    int i = 0;
    for (auto&& x : Reversed(std::array{1, -1, 4, 0, 2})) {
      REQUIRE(x == reversed_arr[i]);
      ++i;
    }
    REQUIRE(i == 5);
  }

#endif  // TEMPORARY_REVERSED_IMPLEMENTED
}

#ifdef TEMPORARY_REVERSED_IMPLEMENTED

TEST_CASE("Compound", "[Reversed]") {
  auto arr = std::array{1, -1, 4, 0, 2};
  auto copy = arr;

  {
    int i = 0;
    for (auto& x : Reversed(Reversed(arr))) {
      REQUIRE(x == arr[i]);
      ++x;
      ++copy[i];
      ++i;
    }
    REQUIRE(i == 5);
    REQUIRE(arr == copy);
  }

  {
    int i = 4;
    const auto reversed = Reversed(Reversed(Reversed(std::as_const(arr))));
    for (auto& x : reversed) {
      REQUIRE((std::is_same_v<decltype(x), const int&>));
      REQUIRE(x == arr[i]);
      --i;
    }
    REQUIRE(i == -1);
  }

  {
    const auto arr_copy = std::array{1, -1, 4, 0, 2};
    int i = 0;
    for (auto x : Reversed(Reversed(std::array{1, -1, 4, 0, 2}))) {
      REQUIRE(x == arr_copy[i]);
      ++i;
    }
    REQUIRE(i == 5);
  }
}

#endif  // TEMPORARY_REVERSED_IMPLEMENTED

#ifdef REVERSE_REVERSED_IMPLEMENTED

TEST_CASE("ReverseEmpty", "[ReverseReversed]"){{const auto empty = std::vector<int>{};
const auto reversed = Reversed(empty);
for ([[maybe_unused]] auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
  REQUIRE(false);
}
}

#ifdef TEMPORARY_REVERSED_IMPLEMENTED

{
  const auto reversed = Reversed(std::vector<int>{});
  for ([[maybe_unused]] auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
    REQUIRE(false);
  }
}

#endif  // TEMPORARY_REVERSED_IMPLEMENTED
}

TEST_CASE("ReverseElementary", "[ReverseReversed]") {
    {
        auto arr = std::array{1, -1, 4, 0, 2};
auto copy = arr;
int i = 0;
const auto reversed = Reversed(arr);
for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
  REQUIRE(*it == arr[i]);
  ++(*it);
  ++copy[i];
  ++i;
}
REQUIRE(i == 5);
REQUIRE(arr == copy);
}

{
  auto arr = std::array{1, -1, 4, 0, 2};
  int i = 0;
  const auto reversed = Reversed(std::as_const(arr));
  for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
    REQUIRE((std::is_same_v<decltype(*it), const int&>));
    REQUIRE(*it == arr[i]);
    ++i;
  }
  REQUIRE(i == 5);
}

#ifdef TEMPORARY_REVERSED_IMPLEMENTED

{
  auto arr = std::array{1, -1, 4, 0, 2};
  int i = 0;
  const auto reversed = Reversed(std::array{1, -1, 4, 0, 2});
  for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
    REQUIRE(*it == arr[i]);
    ++i;
  }
  REQUIRE(i == 5);
}

#endif  // TEMPORARY_REVERSED_IMPLEMENTED
}

#ifdef TEMPORARY_REVERSED_IMPLEMENTED

TEST_CASE("ReverseCompound", "[ReverseReversed]") {
  {
    auto arr = std::array{1, -1, 4, 0, 2};
    auto copy = arr;
    int i = 4;
    const auto reversed = Reversed(Reversed(arr));
    for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
      REQUIRE(*it == arr[i]);
      ++(*it);
      ++copy[i];
      --i;
    }
    REQUIRE(i == -1);
    REQUIRE(arr == copy);
  }

  {
    auto arr = std::array{1, -1, 4, 0, 2};
    int i = 0;
    const auto reversed = Reversed(Reversed(Reversed(std::as_const(arr))));
    for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
      REQUIRE((std::is_same_v<decltype(*it), const int&>));
      REQUIRE(*it == arr[i]);
      ++i;
    }
    REQUIRE(i == 5);
  }

  {
    auto arr = std::array{1, -1, 4, 0, 2};
    int i = 4;
    const auto reversed = Reversed(Reversed(std::array{1, -1, 4, 0, 2}));
    for (auto it = reversed.rbegin(); it != reversed.rend(); ++it) {
      REQUIRE(*it == arr[i]);
      --i;
    }
    REQUIRE(i == -1);
  }
}

#endif  // TEMPORARY_REVERSED_IMPLEMENTED

#endif  // REVERSE_REVERSED_IMPLEMENTED
