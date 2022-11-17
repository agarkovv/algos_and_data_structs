#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <deque>
#include <string>
#include <memory>

#include "inserter.h"
#include "inserter.h"  // check include guards

TEST_CASE("BackInserter", "[Inserter]") {
  {
    std::deque<std::string> d;
    BackInsertIterator back_inserter(d);
    ++back_inserter = "a";
    back_inserter++ = d[0];
    *back_inserter = "c";
    back_inserter = "d";
    REQUIRE(d == (std::deque<std::string>{"a", "a", "c", "d"}));

    std::deque<std::string> dd{"x", "y"};
    std::copy(d.begin() + 2, d.end(), BackInserter(dd));
    REQUIRE(dd == (std::deque<std::string>{"x", "y", "c", "d"}));
  }

  {
    std::deque<std::unique_ptr<int>> d;
    BackInsertIterator back_inserter(d);
    ++back_inserter = std::make_unique<int>(1);
    back_inserter++ = std::make_unique<int>(2);
    *back_inserter = std::make_unique<int>(3);
    back_inserter = std::make_unique<int>(4);
    REQUIRE(*d[0] == 1);
    REQUIRE(*d[1] == 2);
    REQUIRE(*d[2] == 3);
    REQUIRE(*d[3] == 4);

    std::deque<std::unique_ptr<int>> dd;
    dd.push_back(std::make_unique<int>(5));
    dd.push_back(std::make_unique<int>(6));
    std::move(d.begin() + 2, d.end(), BackInserter(dd));
    REQUIRE(*dd[0] == 5);
    REQUIRE(*dd[1] == 6);
    REQUIRE(*dd[2] == 3);
    REQUIRE(*dd[3] == 4);
  }
}

TEST_CASE("FrontInserter", "[Inserter]") {
  {
    std::deque<std::string> d;
    FrontInsertIterator front_inserter(d);
    ++front_inserter = "a";
    front_inserter++ = d[0];
    *front_inserter = "c";
    front_inserter = "d";
    REQUIRE(d == (std::deque<std::string>{"d", "c", "a", "a"}));

    std::deque<std::string> b{"x", "y"};
    std::copy(d.begin() + 2, d.end(), FrontInserter(b));
    REQUIRE(b == (std::deque<std::string>{"a", "a", "x", "y"}));
  }

  {
    std::deque<std::unique_ptr<int>> d;
    FrontInsertIterator front_inserter(d);
    ++front_inserter = std::make_unique<int>(1);
    front_inserter++ = std::make_unique<int>(2);
    *front_inserter = std::make_unique<int>(3);
    front_inserter = std::make_unique<int>(4);
    REQUIRE(*d[0] == 4);
    REQUIRE(*d[1] == 3);
    REQUIRE(*d[2] == 2);
    REQUIRE(*d[3] == 1);

    std::deque<std::unique_ptr<int>> dd;
    dd.push_back(std::make_unique<int>(5));
    dd.push_back(std::make_unique<int>(6));
    std::move(d.begin() + 2, d.end(), FrontInserter(dd));
    REQUIRE(*dd[0] == 1);
    REQUIRE(*dd[1] == 2);
    REQUIRE(*dd[2] == 5);
    REQUIRE(*dd[3] == 6);
  }
}

TEST_CASE("Inserter", "[Inserter]") {
  std::string s("ab");
  InsertIterator inserter(s, std::next(s.begin()));
  ++inserter = 'a';
  inserter++ = 'b';
  *inserter = 'c';
  inserter = 'd';
  REQUIRE(s == "aabcdb");

  std::fill_n(Inserter(s, s.begin() + 2), 100, 'e');
  REQUIRE(s == "aa" + std::string(100, 'e') + "bcdb");
}
