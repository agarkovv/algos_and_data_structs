#pragma once

#include <string>
#include <string_view>
#include <variant>
#include <vector>

struct PlusToken {
  friend bool operator==(const PlusToken &, const PlusToken &) {
    return true;
  }
};

struct MinusToken {
  friend bool operator==(const MinusToken &, const MinusToken &) {
    return true;
  }
};

struct MultiplyToken {
  friend bool operator==(const MultiplyToken &, const MultiplyToken &) {
    return true;
  }
};

struct DivideToken {
  friend bool operator==(const DivideToken &, const DivideToken &) {
    return true;
  }
};

struct ResidualToken {
  friend bool operator==(const ResidualToken &, const ResidualToken &) {
    return true;
  }
};

struct NumberToken {
  int64_t value;
  friend bool operator==(const NumberToken &a, const NumberToken &b) {
    return (a.value == b.value);
  }
};

struct OpeningBracketToken {
  friend bool operator==(const OpeningBracketToken &, const OpeningBracketToken &) {
    return true;
  }
};

struct ClosingBracketToken {
  friend bool operator==(const ClosingBracketToken &, const ClosingBracketToken &) {
    return true;
  }
};

struct MaxToken {
  friend bool operator==(const MaxToken &, const MaxToken &) {
    return true;
  }
};

struct MinToken {
  friend bool operator==(const MinToken &, const MinToken &) {
    return true;
  }
};

struct AbsToken {
  friend bool operator==(const AbsToken &, const AbsToken &) {
    return true;
  }
};

struct SqrToken {
  friend bool operator==(const SqrToken &, const SqrToken &) {
    return true;
  }
};

struct UnknownToken {
  std::string value;
  friend bool operator==(const UnknownToken &a, const UnknownToken &b) {
    return (a.value == b.value);
  }
};

using Token = std::variant<PlusToken, MultiplyToken, NumberToken, OpeningBracketToken, ClosingBracketToken, SqrToken,
                           UnknownToken, MinusToken, ResidualToken, DivideToken, MaxToken, MinToken, AbsToken>;
Token MakeToken(std::string_view string_view);
std::vector<Token> Tokenize(std::string_view string_view);
