#pragma once

#include <beard/core/macros.h>

#include <initializer_list>
#include <string>
#include <unordered_map>

namespace beard {
// For now this is just a wrapper around std::unorederd_map, with convenience
// methods added along the road. At some point, the STL will just get dropped.
template <typename Key, typename Value>
class hash_map {
 public:
  using iterator = typename std::unordered_map<Key, Value>::iterator;
  using const_iterator =
      typename std::unordered_map<Key, Value>::const_iterator;
  using value_type = typename std::pair<const Key, Value>;

  DEFAULT_CTORS(hash_map);

  hash_map() = default;
  ~hash_map() = default;
  hash_map(std::initializer_list<value_type> init)
      : m_hash_map{std::move(init)} {}

  iterator begin() { return m_hash_map.begin(); }
  const_iterator begin() const { return m_hash_map.begin(); }
  const_iterator cbegin() const { return m_hash_map.cbegin(); }
  iterator end() { return m_hash_map.end(); }
  const_iterator end() const { return m_hash_map.end(); }
  const_iterator cend() const { return m_hash_map.cend(); }

  bool is_empty() const { return m_hash_map.empty(); }

  i32 element_count() const { return (i32)m_hash_map.size(); }

  void clear() { m_hash_map.clear(); }

  void add(const Key& key, const Value& value) { m_hash_map[key] = value; }

  void add(Key&& key, Value&& value) {
    m_hash_map[std::move(key)] = std::move(value);
  }

  iterator remove(const Key& key) { return m_hash_map.erase(key); }

  iterator remove(Key&& key) { return m_hash_map.erase(key); }

  const Value& get_value_or(const Key& key, const Value& other) const {
    if (auto found = m_hash_map.find(key); found != m_hash_map.end()) {
      return found->second;
    }

    return other;
  };

  Value& get_value_or(const Key& key, Value& other) {
    if (auto found = m_hash_map.find(key); found != m_hash_map.end()) {
      return found->second;
    }

    return other;
  }

  Value& operator[](const Key& key) { return m_hash_map[key]; }

  Value& operator[](Key&& key) { return m_hash_map[key]; }

  iterator find(const Key& key) { return m_hash_map.find(key); }
  iterator find(Key&& key) { return m_hash_map.find(key); }
  const_iterator find(const Key& key) const { return m_hash_map.find(key); }
  const_iterator find(Key&& key) const { return m_hash_map.find(key); }

  bool contains(const Key& key) const { return m_hash_map.contains(key); }
  bool contains(Key&& key) const { return m_hash_map.contains(key); }

 private:
  std::unordered_map<Key, Value> m_hash_map;
};

template <typename Value>
class string_hash_map : public hash_map<std::string, Value> {
 public:
  using ValueType = typename std::pair<const std::string, Value>;

  string_hash_map() = default;
  string_hash_map(std::initializer_list<ValueType> init)
      : hash_map<std::string, Value>{std::move(init)} {}
};
}  // namespace beard