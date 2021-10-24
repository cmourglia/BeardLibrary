#pragma once

#include <Beard/Macros.h>

#include <initializer_list>
#include <unordered_map>

namespace Beard
{
// For now this is just a wrapper around std::unorederd_map, with convenience
// methods added along the road. At some point, the STL will just get dropped.
template <typename Key, typename Value>
class HashMap
{
public:
	using Iterator      = typename std::unordered_map<Key, Value>::iterator;
	using ConstIterator = typename std::unordered_map<Key, Value>::const_iterator;
	using ValueType     = typename std::pair<const Key, Value>;

	DEFAULT_CTORS(HashMap);

	HashMap()  = default;
	~HashMap() = default;
	HashMap(std::initializer_list<ValueType> init)
	    : m_HashMap{std::move(init)}
	{
	}

	Iterator      begin() { return m_HashMap.begin(); }
	ConstIterator begin() const { return m_HashMap.begin(); }
	ConstIterator cbegin() const { return m_HashMap.cbegin(); }
	Iterator      end() { return m_HashMap.end(); }
	ConstIterator end() const { return m_HashMap.end(); }
	ConstIterator cend() const { return m_HashMap.cend(); }

	bool IsEmpty() const { return m_HashMap.empty(); }

	i32 ElementCount() const { return (i32)m_HashMap.size(); }

	void Clear() { m_HashMap.clear(); }

	void Add(const Key& key, const Value& value) { m_HashMap[key] = value; }

	void Add(Key&& key, Value&& value) { m_HashMap[std::move(key)] = std::move(value); }

	Iterator Remove(const Key& key) { return m_HashMap.erase(key); }

	Iterator Remove(Key&& key) { return m_HashMap.erase(key); }

	const Value& GetValueOr(const Key& key, const Value& other) const
	{
		if (auto found = m_HashMap.find(key); found != m_HashMap.end()) { return found->second; }

		return other;
	};

	Value& GetValueOr(const Key& key, Value& other)
	{
		if (auto found = m_HashMap.find(key); found != m_HashMap.end()) { return found->second; }

		return other;
	}

	Value& operator[](const Key& key) { return m_HashMap[key]; }

	Value& operator[](Key&& key) { return m_HashMap[key]; }

	Iterator      Find(const Key& key) { return m_HashMap.find(key); }
	Iterator      Find(Key&& key) { return m_HashMap.find(key); }
	ConstIterator Find(const Key& key) const { return m_HashMap.find(key); }
	ConstIterator Find(Key&& key) const { return m_HashMap.find(key); }

	bool Contains(const Key& key) const { return m_HashMap.contains(key); }
	bool Contains(Key&& key) const { return m_HashMap.contains(key); }

private:
	std::unordered_map<Key, Value> m_HashMap;
};

template <typename Value>
class StringHashMap : public HashMap<std::string, Value>
{
public:
	using ValueType = typename std::pair<const std::string, Value>;

	StringHashMap() = default;
	StringHashMap(std::initializer_list<ValueType> init)
	    : HashMap<std::string, Value>{std::move(init)}
	{
	}
};
}