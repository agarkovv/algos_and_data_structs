#pragma once
#include <forward_list>
#include <functional>
#include <list>
#include <vector>

template <class KeyT>
class UnorderedSet {
 public:
  UnorderedSet() = default;

  explicit UnorderedSet(size_t count) : table_(std::vector<std::list<KeyT>>(count)), size_(0) {
  }

  template <class ForwardIterator>
  UnorderedSet(const ForwardIterator &first, const ForwardIterator &second) : UnorderedSet() {
    for (auto iter = first; iter != second; ++iter) {
      table_.emplace_back(std::list<KeyT>());
      ++size_;
    }

    for (auto iter = first; iter != second; ++iter) {
      size_t idx = std::hash<KeyT>{}(*iter) % table_.size();
      table_[idx].push_back(*iter);
    }
  }

  UnorderedSet(const UnorderedSet &other) : table_(other.table_), size_(other.size_) {
  }

  UnorderedSet(UnorderedSet &&other) : table_(std::move(other.table_)), size_(other.size_) {
    other.size_ = 0;
  }

  UnorderedSet &operator=(const UnorderedSet &other) {
    table_ = other.table_;
    size_ = other.size_;

    return *this;
  }

  UnorderedSet &operator=(UnorderedSet &&other) {
    table_ = std::move(other.table_);
    size_ = other.size_;

    other.size_ = 0;

    return *this;
  }

  size_t Size() const {
    return size_;
  }

  bool Empty() const {
    return size_ == 0;
  }

  void Clear() {
    size_ = 0;
  };

  void Insert(const KeyT &value) {
    if (Find(value)) {
      return;
    }

    if (table_.empty()) {
      Reserve(++size_);
      table_[0].push_back(value);
      return;
    }

    size_t idx = std::hash<KeyT>{}(value) % table_.size();

    table_[idx].push_back(value);
    ++size_;

    if (size_ > table_.size()) {
      Rehash(table_.size() * 2);
    }
  }

  void Insert(KeyT &&value) {
    if (Find(value)) {
      return;
    }

    if (table_.empty()) {
      Reserve(++size_);
      table_[0].push_back(std::move(value));
      return;
    }

    size_t idx = std::hash<KeyT>{}(value) % table_.size();

    table_[idx].push_back(std::move(value));
    ++size_;

    if (size_ > table_.size()) {
      Rehash(table_.size() * 2);
    }
  }

  void Erase(const KeyT &value) {
    while (Find(value)) {
      size_t idx = std::hash<KeyT>{}(value) % table_.size();

      table_[idx].remove(value);
      --size_;
    }
  }

  bool Find(const KeyT &value) const {
    if (size_ == 0) {
      return false;
    }

    size_t idx = std::hash<KeyT>{}(value) % table_.size();

    for (auto &iter : table_[idx]) {
      if (iter == value) {
        return true;
      }
    }

    return false;
  }

  void Rehash(const size_t new_bucket_count) {
    if (new_bucket_count == table_.size() || new_bucket_count < size_) {
      return;
    }

    std::vector<std::list<KeyT>> new_table(new_bucket_count);

    for (size_t i = 0; i < table_.size(); ++i) {
      for (auto iter = table_[i].begin(); iter != table_[i].end(); ++iter) {
        size_t new_idx = std::hash<KeyT>{}(*iter) % new_bucket_count;

        new_table[new_idx].push_back(std::move(*iter));
      }
    }

    table_ = std::move(new_table);
  }

  void Reserve(const size_t new_bucket_count) {
    if (new_bucket_count <= table_.size()) {
      return;
    }

    std::vector<std::list<KeyT>> new_table(new_bucket_count);

    for (size_t i = 0; i < table_.size(); ++i) {
      for (auto iter = table_[i].begin(); iter != table_[i].end(); ++iter) {
        size_t new_idx = std::hash<KeyT>{}(*iter) % new_bucket_count;

        new_table[new_idx].push_back(std::move(*iter));
      }
    }

    table_ = std::move(new_table);
  }

  size_t BucketCount() const {
    return table_.size();
  }

  size_t BucketSize(size_t id) const {
    if (id < table_.size()) {
      return table_[id].size();
    }

    return 0;
  }

  size_t Bucket(const KeyT &key) const {
    return std::hash<KeyT>{}(key) % table_.size();
  }

  double LoadFactor() const {
    if (!table_.empty()) {
      return static_cast<double>(size_) / static_cast<double>(table_.size());
    }

    return 0;
  }

  ~UnorderedSet() = default;

 private:
  std::vector<std::list<KeyT>> table_ = std::vector<std::list<KeyT>>();
  size_t size_ = 0;
};