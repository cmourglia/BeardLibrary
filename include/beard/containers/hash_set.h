#pragma once

#include <initializer_list>
#include <unordered_set>

#include "beard/core/macros.h"

namespace beard {
// For now this is just a wrapper around std::unorederd_map, with convenience
// methods added along the road. At some point, the STL will just get dropped.
template <typename Key>
class hash_set {
 public:
  using iterator = typename std::unordered_set<Key>::iterator;
  using const_iterator = typename std::unordered_set<Key>::const_iterator;

  DEFAULT_CTORS(hash_set);

  hash_set() = default;
  ~hash_set() = default;
  hash_set(std::initializer_list<Key> init) : m_hash_set{std::move(init)} {}

  iterator begin() { return m_hash_set.begin(); }
  const_iterator begin() const { return m_hash_set.begin(); }
  const_iterator cbegin() const { return m_hash_set.cbegin(); }
  iterator end() { return m_hash_set.end(); }
  const_iterator end() const { return m_hash_set.end(); }
  const_iterator cend() const { return m_hash_set.cend(); }

  bool is_empty() const { return m_hash_set.empty(); }

  i32 element_count() const { return (i32)m_hash_set.size(); }

  void clear() { m_hash_set.clear(); }

  void add(const Key& key) { m_hash_set.insert(key); }
  void add(Key&& key) { m_hash_set.insert(std::move(key)); }

  void remove(const Key& key) { m_hash_set.erase(key); }
  void remove(Key&& key) { m_hash_set.erase(std::move(key)); }

  iterator find(const Key& key) { return m_hash_set.find(key); }
  iterator find(Key&& key) { return m_hash_set.find(key); }
  const_iterator find(const Key& key) const { return m_hash_set.find(key); }
  const_iterator find(Key&& key) const { return m_hash_set.find(key); }

  bool contains(const Key& key) const { return m_hash_set.contains(key); }
  bool contains(Key&& key) const { return m_hash_set.contains(key); }

 private:
  std::unordered_set<Key> m_hash_set;
};

class string_hash_set : public hash_set<std::string> {
 public:
  string_hash_set() = default;
  string_hash_set(std::initializer_list<std::string> init)
      : hash_set<std::string>{init} {}
};
}  // namespace beard