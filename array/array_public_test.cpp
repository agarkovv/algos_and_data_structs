#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "array.h"
#include "array.h"  // check include guards

TEST_CASE("Public") {
  Array<int, 4> arr{1, 2, 3};  // aggregate initialization

  {
    static_assert(sizeof(arr) == sizeof(int) * 4);
    REQUIRE(arr.Size() == 4);
    REQUIRE_FALSE(arr.Empty());
  }

  {
    REQUIRE(arr[0] == 1);
    arr[1] = -2;
    REQUIRE(arr[1] == -2);
    arr.At(2) = -3;
    REQUIRE(arr.At(2) == -3);
    REQUIRE(arr.At(3) == 0);
    REQUIRE_THROWS_AS(arr.At(4), ArrayOutOfRange);
  }

  {
    REQUIRE(arr.Front() == 1);  // Front
    arr.Front() = -1;
    REQUIRE(arr.Back() == 0);  // Back
    arr.Back() = 11;
    REQUIRE(arr.Data() == &arr[0]);  // Data
  }

  {
    arr.Fill(-1);
    REQUIRE((arr[0] == -1 && arr[1] == -1 && arr[2] == -1 && arr[3] == -1));

    Array<int, 4>{0, 1, 0, 1}.Swap(arr);
    REQUIRE((arr[0] == 0 && arr[1] == 1 && arr[2] == 0 && arr[3] == 1));
  }
}
