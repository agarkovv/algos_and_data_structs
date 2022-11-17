#pragma once

template <class Container>
class Reversed {
 public:
  explicit Reversed(Container &cont) : rbeg_(cont.rbegin()), rend_(cont.rend()) {
  }

  explicit Reversed(const Container &cont) : crbeg_(cont.crbegin()), crend_(cont.crend()) {
  }

  typename Container::reverse_iterator begin() {  // NOLINT
    return rbeg_;
  }

  typename Container::reverse_iterator end() {  // NOLINT
    return rend_;
  }

  typename Container::const_reverse_iterator begin() const {  // NOLINT
    return crbeg_;
  }

  typename Container::const_reverse_iterator end() const {  // NOLINT
    return crend_;
  }

 private:
  typename Container::reverse_iterator rbeg_;
  typename Container::reverse_iterator rend_;
  typename Container::const_reverse_iterator crbeg_;
  typename Container::const_reverse_iterator crend_;
};