#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string_view>

#include "cppstring.h"
#include "cppstring.h"  // check include guards

void CheckEqual(const String& actual, std::string_view expected) {
  REQUIRE(actual.Capacity() >= actual.Size());
  REQUIRE(actual.Size() == expected.size());
  REQUIRE(actual.Length() == expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    REQUIRE(actual[i] == expected[i]);
  }
}

TEST_CASE("Default", "[Constructor]") {
  const String s;
  REQUIRE(s.Capacity() == 0u);
  REQUIRE(s.Size() == 0u);
  REQUIRE(s.Data() == nullptr);
  REQUIRE(s.Empty());
  CheckEqual(String(s), "");
}

TEST_CASE("FillInitialization", "[Constructor]") {
  {
    const String s(0, 'z');
    REQUIRE(s.Size() == 0u);
    REQUIRE(s.Capacity() == 0u);
    REQUIRE(s.Data() == nullptr);
  }

  {
    const String s(5, 'a');
    CheckEqual(s, "aaaaa");
  }
}

TEST_CASE("From C String", "[Constructor]") {
  {
    const String s = "abacaba";
    CheckEqual(s, "abacaba");
  }

  {
    const String s = "";
    REQUIRE(s.Capacity() == 0u);
    CheckEqual(s, "");
  }

  {
    const String s("abacaba", 5u);
    CheckEqual(s, "abaca");
  }

  {
    const String s("abacaba", 0u);
    REQUIRE(s.Capacity() == 0u);
    CheckEqual(s, "");
  }
}

TEST_CASE("Copy Constructor", "[Constructor]") {
  {
    const String empty;
    const auto copy = empty;
    REQUIRE(empty.Size() == 0u);
    REQUIRE(empty.Capacity() == 0u);
    REQUIRE(empty.Data() == nullptr);
    REQUIRE(copy.Size() == 0u);
    REQUIRE(copy.Capacity() == 0u);
    REQUIRE(copy.Data() == nullptr);
  }

  {
    const String s = "abacaba";
    const auto copy = s;
    CheckEqual(copy, "abacaba");
    CheckEqual(s, "abacaba");
  }
}

TEST_CASE("Copy Assignment", "[Assignment]") {
  SECTION("Empty to empty") {
    const String empty;
    String s;
    s = empty;
    REQUIRE(empty.Size() == 0u);
    REQUIRE(empty.Capacity() == 0u);
    REQUIRE(empty.Data() == nullptr);
    REQUIRE(s.Size() == 0u);
    REQUIRE(s.Capacity() == 0u);
    REQUIRE(s.Data() == nullptr);

    s = s;
    REQUIRE(s.Size() == 0u);
    REQUIRE(s.Capacity() == 0u);
    REQUIRE(s.Data() == nullptr);
  }

  SECTION("Empty to filled") {
    const String empty;
    String s = "abacaba";
    s = empty;
    REQUIRE(empty.Size() == 0u);
    REQUIRE(empty.Capacity() == 0u);
    REQUIRE(empty.Data() == nullptr);
    REQUIRE(s.Size() == 0u);
  }

  SECTION("Filled to empty") {
    const String init = "abacaba";
    String s;
    s = init;
    CheckEqual(s, "abacaba");
    CheckEqual(init, "abacaba");

    s = s;
    CheckEqual(s, "abacaba");
    CheckEqual(init, "abacaba");
  }

  SECTION("Small to large") {
    const String small(10, 'a');
    String large(1000, 'b');
    large = small;
    CheckEqual(large, std::string(10, 'a'));
    CheckEqual(small, std::string(10, 'a'));
  }

  SECTION("Large to small") {
    const String large(1000, 'b');
    String small(10, 'a');
    small = large;
    CheckEqual(large, std::string(1000, 'b'));
    CheckEqual(small, std::string(1000, 'b'));
  }
}

TEST_CASE("DataAccess", "[Methods]") {
  String s = "abcdef";

  {
    REQUIRE(s.Front() == 'a');
    s.Front() = 'z';
    REQUIRE(std::as_const(s).Front() == 'z');
  }

  {
    REQUIRE(s.Back() == 'f');
    s.Back() = 'y';
    REQUIRE(std::as_const(s).Back() == 'y');
  }

  {
    REQUIRE(s[1] == 'b');
    s[1] = 'x';
    REQUIRE(std::as_const(s)[1] == 'x');
  }

  {
    REQUIRE(s.At(2) == 'c');
    s.At(2) = 'w';
    REQUIRE(std::as_const(s).At(2) == 'w');
    REQUIRE_THROWS_AS(s.At(6), StringOutOfRange);                 // NOLINT
    REQUIRE_THROWS_AS(std::as_const(s).At(6), StringOutOfRange);  // NOLINT
  }

  {
    REQUIRE(s.CStr()[3] == 'd');
    REQUIRE(s.Data()[3] == 'd');
    s.CStr()[3] = 'v';
    REQUIRE(s.CStr()[3] == 'v');
    REQUIRE(s.Data()[3] == 'v');
    s.CStr()[3] = 'u';
    REQUIRE(s.CStr()[3] == 'u');
    REQUIRE(s.Data()[3] == 'u');

    REQUIRE((std::is_same_v<decltype(std::declval<const String&>().Data()), const char*>));
    REQUIRE((std::is_same_v<decltype(std::declval<const String&>().CStr()), const char*>));
  }
}

TEST_CASE("Swap", "[String]") {
  auto a = String();
  auto b = String();
  a.Swap(b);
  CheckEqual(a, "");
  CheckEqual(b, "");

  b = String("abacaba");
  a.Swap(b);
  CheckEqual(a, "abacaba");
  CheckEqual(b, "");

  b = String(5, 'a');
  b.Swap(a);
  CheckEqual(a, "aaaaa");
  CheckEqual(b, "abacaba");
}

TEST_CASE("Append", "[String]") {
  SECTION("PushBack") {
    String s;
    std::string actual("a");
    s.PushBack('a');
    for (size_t size = 1u; size < 1'000'000; size *= 2u) {
      for (size_t i = 0u; i < size; ++i) {
        s.PushBack(static_cast<char>('a' + i % 26));
        actual.push_back(static_cast<char>('a' + i % 26));
      }
      REQUIRE(s.Capacity() >= size * 2);
      CheckEqual(s, actual);
    }
  }

  SECTION("+=") {
    const String other = "abacaba";
    String s;
    (s += other) += other;
    CheckEqual(s, "abacabaabacaba");
    std::string actual("abacabaabacaba");
    for (size_t i = 0; i < 100000; ++i) {
      s += other;
      actual += "abacaba";
    }
    CheckEqual(s, actual);
  }

  SECTION("+") {
    {
      const String a;
      const String b;
      CheckEqual(a + b, "");
    }

    {
      const String a;
      const String b("caba");
      CheckEqual(a + b, "caba");
    }

    {
      const String a("aba");
      const String b;
      CheckEqual(a + b, "aba");
    }

    {
      const String a("aba");
      const String b("caba");
      CheckEqual(a + b, "abacaba");
    }

    {
      const String a("aba");
      CheckEqual(a + "caba", "abacaba");
    }

    {
      const String b("caba");
      CheckEqual("" + b, "caba");
    }
  }
}

TEST_CASE("Clear", "[String]") {
  SECTION("Clear") {
    String s;
    s.Clear();
    CheckEqual(s, "");

    s = "aba";
    s.Clear();
    CheckEqual(s, "");

    for (size_t size = 1u; size < 1'000'000; size *= 2u) {
      for (size_t i = 0u; i < size; ++i) {
        s.PushBack(static_cast<char>('a' + i % 26));
      }
      s.Clear();
      CheckEqual(s, "");
    }
  }

  SECTION("PopBack") {
    String s("abacaba");
    s.PopBack();
    s.PopBack();
    CheckEqual(s, "abaca");

    for (size_t size = 1u; size < 1'000'000; size *= 2u) {
      for (size_t i = 0u; i < size; ++i) {
        s.PushBack(static_cast<char>('a' + i % 26));
      }
      for (size_t i = 0u; i < size; ++i) {
        s.PopBack();
      }
      CheckEqual(s, "abaca");
    }
  }
}

TEST_CASE("Resize", "[String]") {
  SECTION("Resize") {
    String a;
    a.Resize(5, 'a');
    CheckEqual(a, "aaaaa");

    a.Resize(3, 'b');
    CheckEqual(a, "aaa");

    a.Resize(7, 'c');
    CheckEqual(a, "aaacccc");

    a.Resize(0, 'a');
    CheckEqual(a, "");

    a = "aba";
    CheckEqual(a, "aba");
    REQUIRE(a.Capacity() >= 3u);
  }

  SECTION("Reserve") {
    String a("abacaba");
    REQUIRE(a.Capacity() < 15);

    a.Reserve(20);
    REQUIRE(a.Capacity() >= 20);
    CheckEqual(a, "abacaba");

    a.Reserve(1000);
    REQUIRE(a.Capacity() >= 1000);
    CheckEqual(a, "abacaba");

    a.Reserve(1000000);
    REQUIRE(a.Capacity() >= 1000000);
    CheckEqual(a, "abacaba");

    a.Reserve(10);
    REQUIRE(a.Capacity() >= 1000000);
    CheckEqual(a, "abacaba");
  }

  SECTION("ShrinkToFit") {
    String a("abacaba");
    a.Reserve(100);
    REQUIRE(a.Capacity() > a.Size());
    a.ShrinkToFit();
    REQUIRE(a.Capacity() == a.Size());
    CheckEqual(a, "abacaba");

    a.Resize(0, 'a');
    CheckEqual(a, "");
    REQUIRE(a.Capacity() > 0u);
    a.ShrinkToFit();
    REQUIRE(a.Size() == 0u);
    REQUIRE(a.Capacity() == 0u);

    a = "aba";
    CheckEqual(a, "aba");
    REQUIRE(a.Capacity() >= 3u);
  }
}

void CheckComparisonEqual(const String& lhs, const String& rhs) {
  REQUIRE(lhs == rhs);
  REQUIRE(lhs <= rhs);
  REQUIRE(lhs >= rhs);
  REQUIRE_FALSE(lhs != rhs);
  REQUIRE_FALSE(lhs < rhs);
  REQUIRE_FALSE(lhs > rhs);
}

void CheckComparisonLess(const String& lhs, const String& rhs) {
  REQUIRE_FALSE(lhs == rhs);
  REQUIRE(lhs <= rhs);
  REQUIRE_FALSE(lhs >= rhs);
  REQUIRE(lhs != rhs);
  REQUIRE(lhs < rhs);
  REQUIRE_FALSE(lhs > rhs);
}

void CheckComparisonGreater(const String& lhs, const String& rhs) {
  REQUIRE_FALSE(lhs == rhs);
  REQUIRE_FALSE(lhs <= rhs);
  REQUIRE(lhs >= rhs);
  REQUIRE(lhs != rhs);
  REQUIRE_FALSE(lhs < rhs);
  REQUIRE(lhs > rhs);
}

TEST_CASE("Comparisons", "[String]") {
  {
    String a;
    String b;
    CheckComparisonEqual(a, b);
  }

  {
    String a;
    String b(1, 'a');
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    String a("ac");
    String b("b");
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    String a("abc");
    String b("aa");
    CheckComparisonLess(b, a);
    CheckComparisonGreater(a, b);
  }

  {
    String a("abcd");
    String b("abcd");
    CheckComparisonEqual(a, b);
  }

  {
    String a("abcd");
    String b("abc");
    CheckComparisonLess(b, a);
    CheckComparisonGreater(a, b);
  }

  {
    String a("adfh");
    String b("bceg");
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    String a("abce");
    String b("abde");
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }
}

TEST_CASE("Output", "[String]") {
  auto oss = std::ostringstream();
  oss << String("abacaba") << ' ' << String() << ' ' << String(5, 'a');
  REQUIRE(oss.str() == "abacaba  aaaaa");
}

#ifdef STRING_ITERATORS

TEST_CASE("Types", "[String]") {
  REQUIRE((std::is_same_v<String::ValueType, char>));
  REQUIRE((std::is_same_v<String::SizeType, decltype(std::declval<String>().Size())>));
  REQUIRE((std::is_same_v<String::Reference, decltype(std::declval<String>().Front())>));
  REQUIRE((std::is_same_v<String::ConstReference, decltype(std::declval<const String>().Back())>));
  REQUIRE((std::is_same_v<String::Pointer, decltype(std::declval<String>().Data())>));
  REQUIRE((std::is_same_v<String::ConstPointer, decltype(std::declval<const String>().CStr())>));
  REQUIRE((std::is_same_v<String::Iterator, decltype(std::declval<String>().begin())>));
  REQUIRE((std::is_same_v<String::ConstIterator, decltype(std::declval<String>().cbegin())>));
  REQUIRE((std::is_same_v<String::ConstIterator, decltype(std::declval<const String>().end())>));
  REQUIRE((std::is_same_v<String::ReverseIterator, decltype(std::declval<String>().rbegin())>));
  REQUIRE((std::is_same_v<String::ConstReverseIterator, decltype(std::declval<String>().crend())>));
  REQUIRE((std::is_same_v<String::ConstReverseIterator, decltype(std::declval<const String>().rend())>));
}

TEST_CASE("Iterators", "[String]") {
  String s = "abacaba";

  SECTION("Iterator") {
    size_t i = 0;
    for (auto it = s.begin(), end = s.end(); it != end; ++it, ++i) {
      REQUIRE(i < 7);
      REQUIRE(*it == s[i]);
    }

    std::string_view ss = "bbbbb";
    std::copy(ss.begin(), ss.end(), std::next(s.begin()));
    CheckEqual(s, "abbbbba");
  }

  SECTION("ConstIterator") {
    size_t i = 0;
    for (auto it = s.cbegin(), end = s.cend(); it != end; ++it, ++i) {
      REQUIRE(i < 7);
      REQUIRE(*it == s[i]);
    }
  }

  SECTION("ReverseIterator") {
    size_t i = 6;
    for (auto it = s.rbegin(), end = s.rend(); it != end; ++it, --i) {
      REQUIRE(i < 7);
      REQUIRE(*it == s[i]);
    }

    std::string_view ss = "ccccc";
    std::copy(ss.begin(), ss.end(), std::next(s.rbegin()));
    CheckEqual(s, "accccca");
  }

  SECTION("ConstReverseIterator") {
    size_t i = 6;
    for (auto it = s.crbegin(), end = s.crend(); it != end; ++it, --i) {
      REQUIRE(i < 7);
      REQUIRE(*it == s[i]);
    }
  }

  SECTION("Range-based for") {
    size_t i = 0;
    for (char symbol : s) {
      REQUIRE(i < 7);
      REQUIRE(symbol == s[i]);
      ++i;
    }
  }
}

#endif  // STRING_ITERATORS
