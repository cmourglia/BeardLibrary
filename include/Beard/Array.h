#pragma once

#include <Beard/Macros.h>

#include <vector>

namespace Beard
{

// For now this is just a wrapper around std::vector with convenience methods
// added along the road. At some point, the STL will just get dropped.

template <typename T>
class Array
{
public:
	using Iterator      = typename std::vector<T>::iterator;
	using ConstIterator = typename std::vector<T>::const_iterator;

	Array() noexcept = default;

	explicit Array(const i32 size, const T& defaultValue = T{}) noexcept
	    : m_Array(size, defaultValue)
	{
	}

	Array(std::initializer_list<T> list)
	    : m_Array(std::move(list))
	{
	}

	~Array() noexcept = default;

	DEFAULT_CTORS(Array);

	void Reserve(const i32 size) { m_Array.reserve(size); }

	void Resize(const i32 size) { m_Array.resize(size); }

	void Clear() { m_Array.clear(); }

	i32 ElementCount() const { return static_cast<i32>(m_Array.size()); }

	i32 DataSize() const { return ElementCount() * sizeof(T); }

	bool IsEmpty() const { return m_Array.empty(); }

	const T& Get(const i32 index) const { return m_Array.at(index); }

	T& Get(const i32 index) { return m_Array.at(index); }

	const T& operator[](const i32 index) const { return m_Array[index]; }

	T& operator[](const i32 index) { return m_Array[index]; }

	const T* Data() const { return m_Array.data(); }

	T* Data() { return m_Array.data(); }

	Iterator begin() { return m_Array.begin(); }

	ConstIterator begin() const { return m_Array.begin(); }

	ConstIterator cbegin() const { return m_Array.cbegin(); }

	Iterator end() { return m_Array.end(); }

	ConstIterator end() const { return m_Array.end(); }

	ConstIterator cend() const { return m_Array.cend(); }

	void Add(const T& value) { m_Array.push_back(value); }

	void Add(T&& value) { m_Array.push_back(std::move(value)); }

	template <typename... Args>
	void Emplace(Args... args)
	{
		m_Array.emplace_back(std::forward<Args>(args)...);
	}

	void Insert(const T& elem, i32 index) { m_Array.insert(begin() + index, elem); }
	void Insert(T&& elem, i32 index) { m_Array.insert(begin() + index, elem); }
	void Insert(Iterator where, Iterator rangeStart, Iterator rangeEnd) { m_Array.insert(where, rangeStart, rangeEnd); }

	void Append(const Array<T>& other)
	{
		Reserve(ElementCount() + other.ElementCount());
		m_Array.insert(m_Array.end(), other.m_Array.begin(), other.m_Array.end());
	}

	// FIXME: Return iterator ?
	void RemoveRange(const ConstIterator& begin, const ConstIterator& end) { m_Array.erase(begin, end); }
	void Remove(const ConstIterator& element) { m_Array.erase(element); }

	T&       First() { return m_Array.front(); }
	const T& First() const { return m_Array.front(); }

	T&       Last() { return m_Array.back(); }
	const T& Last() const { return m_Array.back(); }

	[[nodiscard]] T Pop()
	{
		T last = Last();
		m_Array.pop_back();
		return last;
	}

	void PopAndDiscard() { m_Array.pop_back(); }

private:
	std::vector<T> m_Array;
};
}