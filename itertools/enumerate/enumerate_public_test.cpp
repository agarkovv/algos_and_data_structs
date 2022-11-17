#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <array>
#include <vector>
#include <forward_list>

#include "enumerate.h"
#include "enumerate.h"  // check include guards

TEST_CASE("Empty", "[Enumerate]") {
  const auto empty = std::vector<int>{};
  for ([[maybe_unused]] auto&& [i, x] : Enumerate(empty)) {
    REQUIRE(false);
  }

#ifdef TEMPORARY_ENUMERATE_IMPLEMENTED

  for ([[maybe_unused]] auto&& [i, x] : Enumerate(std::vector<int>{})) {
    REQUIRE(false);
  }

#endif  // TEMPORARY_ENUMERATE_IMPLEMENTED
}

TEST_CASE("Elementary", "[Enumerate]") {
    {
        auto lst = std::forward_list{1, -1, 4, 0, 2};
auto copy = lst;
auto i = 0;
auto lst_it = lst.begin();
auto copy_it = copy.begin();
for (auto&& [id, value] : Enumerate(lst)) {
  REQUIRE(value == *lst_it);
  REQUIRE(static_cast<int>(id) == i);
  ++value;
  ++(*copy_it);
  ++i;
  ++lst_it;
  ++copy_it;
}
REQUIRE(i == 5);
REQUIRE(lst_it == lst.end());
REQUIRE(copy_it == copy.end());
REQUIRE(lst == copy);

i = 0;
copy_it = copy.begin();
const auto enumerate = Enumerate(std::as_const(lst));
for (auto&& [id, value] : enumerate) {
  REQUIRE((std::is_same_v<decltype(value), const int&>));
  REQUIRE(static_cast<int>(id) == i);
  REQUIRE(value == *copy_it);
  ++i;
  ++copy_it;
}
REQUIRE(i == 5);
}

#ifdef TEMPORARY_ENUMERATE_IMPLEMENTED

{
  const auto arr = std::array{2, 0, 4, -1, 1};
  int i = 0;
  for (auto&& [id, value] : Enumerate(std::array{2, 0, 4, -1, 1})) {
    REQUIRE(value == arr[i]);
    REQUIRE(static_cast<int>(id) == i);
    ++i;
  }
  REQUIRE(i == 5);

  i = 0;
  const auto enumerate = Enumerate(std::array{2, 0, 4, -1, 1});
  for (auto&& [id, value] : enumerate) {
    REQUIRE(value == arr[i]);
    REQUIRE(static_cast<int>(id) == i);
    ++i;
  }
  REQUIRE(i == 5);
}

#endif  // TEMPORARY_ENUMERATE_IMPLEMENTED
}

#ifdef TEMPORARY_ENUMERATE_IMPLEMENTED

TEST_CASE("Compound", "[Enumerate]") {
  {
    auto arr = std::array{1, -1, 4, 0, 2};
    auto copy = arr;
    int i = 0;
    for (auto&& [id, i_value] : Enumerate(Enumerate(arr))) {
      REQUIRE(i_value.second == copy[i]);
      REQUIRE(static_cast<int>(i_value.first) == i);
      REQUIRE(static_cast<int>(id) == i);
      ++i_value.second;
      ++copy[i];
      ++i;
    }
    REQUIRE(i == 5);
    REQUIRE(arr == copy);

    i = 0;
    const auto enumerate = Enumerate(Enumerate(Enumerate(std::as_const(arr))));
    for (auto&& [id1, i_i_value] : enumerate) {
      auto&& [id2, i_value] = i_i_value;
      auto&& [id3, value] = i_value;
      REQUIRE((std::is_same_v<decltype(value), const int&>));
      REQUIRE(static_cast<int>(id1) == i);
      REQUIRE(static_cast<int>(id2) == i);
      REQUIRE(static_cast<int>(id3) == i);
      ++i;
    }
    REQUIRE(i == 5);
  }

  {
    const auto arr = std::array{1, -1, 4, 0, 2};

    int i = 0;
    for (auto&& [id, i_value] : Enumerate(Enumerate(std::array{1, -1, 4, 0, 2}))) {
      REQUIRE(i_value.second == arr[i]);
      REQUIRE(static_cast<int>(i_value.first) == i);
      REQUIRE(static_cast<int>(id) == i);
      ++i;
    }
    REQUIRE(i == 5);

    i = 0;
    const auto enumerate = Enumerate(Enumerate(Enumerate(std::array{1, -1, 4, 0, 2})));
    for (auto&& [id1, i_i_value] : enumerate) {
      auto&& [id2, i_value] = i_i_value;
      auto&& [id3, value] = i_value;
      REQUIRE(value == arr[i]);
      REQUIRE(static_cast<int>(id1) == i);
      REQUIRE(static_cast<int>(id2) == i);
      REQUIRE(static_cast<int>(id3) == i);
      ++i;
    }
    REQUIRE(i == 5);
  }
}

#endif  // TEMPORARY_ENUMERATE_IMPLEMENTED
