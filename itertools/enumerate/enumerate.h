#pragma once
#include <cstdint>

template <class Container>
class Enumerate {

  class Iterator {
   public:
    explicit Iterator(const typename Container::iterator& iterator, const size_t& idx = 0)
        : iterator_(iterator), idx_(idx) {
    }

    std::pair<size_t, typename Container::reference> operator*() const {
      return std::pair<size_t, typename Container::reference>(idx_, *iterator_);
    }

    Iterator& operator++() {
      ++iterator_;
      ++idx_;
      return *this;
    }

    bool operator!=(const Iterator& other) {
      return iterator_ != other.iterator_;
    }

   private:
    typename Container::iterator iterator_;
    size_t idx_;
  };

  class ConstIterator {
   public:
    explicit ConstIterator(const typename Container::const_iterator& iterator, const size_t& idx = 0)
        : iterator_(iterator), idx_(idx) {
    }

    std::pair<size_t, typename Container::const_reference> operator*() const {
      return std::pair<size_t, typename Container::const_reference>(idx_, *iterator_);
    }

    ConstIterator& operator++() {
      ++iterator_;
      ++idx_;
      return *this;
    }

    bool operator!=(const ConstIterator& other) {
      return iterator_ != other.iterator_;
    }

   private:
    typename Container::const_iterator iterator_;
    size_t idx_;
  };

 public:
  explicit Enumerate(Container& container) : beg_(container.begin()), end_(container.end()) {
  }

  explicit Enumerate(const Container& container) : cbeg_(container.cbegin()), cend_(container.cend()) {
  }

  Iterator begin() {  // NOLINT
    return Iterator(beg_, 0);
  }

  Iterator end() {  // NOLINT
    return Iterator(end_, 0);
  }

  ConstIterator begin() const {  // NOLINT
    return ConstIterator(cbeg_, 0);
  }

  ConstIterator end() const {  // NOLINT
    return ConstIterator(cend_, 0);
  }

 private:
  typename Container::iterator beg_;
  typename Container::iterator end_;
  typename Container::const_iterator cbeg_;
  typename Container::const_iterator cend_;
};