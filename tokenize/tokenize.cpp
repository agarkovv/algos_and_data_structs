#include <sstream>
#include <variant>
#include <vector>

#include "tokenize.h"

Token MakeToken(std::string_view string_view) {
  if (string_view == "+") {
    return PlusToken{};
  }
  if (string_view == "*") {
    return MultiplyToken{};
  }
  if (string_view == "(") {
    return OpeningBracketToken{};
  }
  if (string_view == ")") {
    return ClosingBracketToken{};
  }
  if (string_view == "sqr") {
    return SqrToken{};
  }
  if (string_view == "-") {
    return MinusToken{};
  }
  if (string_view == "/") {
    return DivideToken{};
  }
  if (string_view == "abs") {
    return AbsToken{};
  }
  if (string_view == "%") {
    return ResidualToken{};
  }
  if (string_view == "min") {
    return MinToken{};
  }
  if (string_view == "max") {
    return MaxToken{};
  }

  std::string string = std::string(string_view);
  int64_t value = 0;
  std::istringstream is(string);
  is >> value;
  if (is.eof()) {
    return NumberToken{value};
  }
  return UnknownToken{std::move(string)};
}

std::vector<Token> Tokenize(std::string_view string_view) {
  std::vector<Token> token;
  while (!string_view.empty()) {
    uint64_t index = string_view.find(' ');
    if (index != 0) {
      if (index == string_view.npos) {
        token.emplace_back(MakeToken(string_view));
        return token;
      }
      token.emplace_back(MakeToken(string_view.substr(0, index)));
    }
    string_view.remove_prefix(index + 1);
  }
  return token;
}
