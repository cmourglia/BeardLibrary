#pragma once

#include <Beard/Macros.h>

#include <initializer_list>
#include <unordered_set>

namespace Beard
{
// For now this is just a wrapper around std::unorederd_map, with convenience
// methods added along the road. At some point, the STL will just get dropped.
template <typename Key>
class HashSet
{
public:
	using Iterator      = typename std::unordered_set<Key>::iterator;
	using ConstIterator = typename std::unordered_set<Key>::const_iterator;

	DEFAULT_CTORS(HashSet);

	HashSet()  = default;
	~HashSet() = default;
	HashSet(std::initializer_list<Key> init)
	    : m_HashSet{std::move(init)}
	{
	}

	Iterator      begin() { return m_HashSet.begin(); }
	ConstIterator begin() const { return m_HashSet.begin(); }
	ConstIterator cbegin() const { return m_HashSet.cbegin(); }
	Iterator      end() { return m_HashSet.end(); }
	ConstIterator end() const { return m_HashSet.end(); }
	ConstIterator cend() const { return m_HashSet.cend(); }

	bool IsEmpty() const { return m_HashSet.empty(); }

	i32 ElementCount() const { return (i32)m_HashSet.size(); }

	void Clear() { m_HashSet.clear(); }

	void Add(const Key& key) { m_HashSet.insert(key); }
	void Add(Key&& key) { m_HashSet.insert(std::move(key)); }

	void Remove(const Key& key) { m_HashSet.erase(key); }
	void Remove(Key&& key) { m_HashSet.erase(std::move(key)); }

	Iterator      Find(const Key& key) { return m_HashSet.find(key); }
	Iterator      Find(Key&& key) { return m_HashSet.find(key); }
	ConstIterator Find(const Key& key) const { return m_HashSet.find(key); }
	ConstIterator Find(Key&& key) const { return m_HashSet.find(key); }

	bool Contains(const Key& key) const { return m_HashSet.contains(key); }
	bool Contains(Key&& key) const { return m_HashSet.contains(key); }

private:
	std::unordered_set<Key> m_HashSet;
};

class StringHashSet : public HashSet<std::string>
{
public:
	StringHashSet() = default;
	StringHashSet(std::initializer_list<std::string> init)
	    : HashSet<std::string>{init}
	{
	}
};
}