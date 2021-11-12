#pragma once

#include <beard/core/macros.h>

#include <vector>

namespace beard
{

// For now this is just a wrapper around std::vector with convenience methods
// added along the road. At some point, the STL will just get dropped.

template <typename T>
class array
{
public:
	using iterator       = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;

	array() noexcept = default;

	explicit array(const i32 size, const T& default_value = T{}) noexcept
	    : m_array(size, default_value)
	{
	}

	array(std::initializer_list<T> list)
	    : m_array(std::move(list))
	{
	}

	~array() noexcept = default;

	DEFAULT_CTORS(array);

	void reserve(const i32 size) { m_array.reserve(size); }

	void resize(const i32 size) { m_array.resize(size); }

	void clear() { m_array.clear(); }

	i32 element_count() const { return static_cast<i32>(m_array.size()); }

	i32 data_size() const { return element_count() * sizeof(T); }

	bool is_empty() const { return m_array.empty(); }

	const T& get(const i32 index) const { return m_array.at(index); }

	T& get(const i32 index) { return m_array.at(index); }

	const T& operator[](const i32 index) const { return m_array[index]; }

	T& operator[](const i32 index) { return m_array[index]; }

	const T* data() const { return m_array.data(); }

	T* data() { return m_array.data(); }

	iterator begin() { return m_array.begin(); }

	const_iterator begin() const { return m_array.begin(); }

	const_iterator cbegin() const { return m_array.cbegin(); }

	iterator end() { return m_array.end(); }

	const_iterator end() const { return m_array.end(); }

	const_iterator cend() const { return m_array.cend(); }

	void add(const T& value) { m_array.push_back(value); }

	void add(T&& value) { m_array.push_back(std::move(value)); }

	template <typename... Args>
	void emplace(Args... args)
	{
		m_array.emplace_back(std::forward<Args>(args)...);
	}

	void insert(const T& elem, i32 index) { m_array.insert(begin() + index, elem); }
	void insert(T&& elem, i32 index) { m_array.insert(begin() + index, elem); }
	void insert(iterator where, iterator rangeStart, iterator rangeEnd) { m_array.insert(where, rangeStart, rangeEnd); }

	void append(const array<T>& other)
	{
		reserve(element_count() + other.element_count());
		m_array.insert(m_array.end(), other.m_array.begin(), other.m_array.end());
	}

	// FIXME: Return iterator ?
	void remove_range(const const_iterator& begin, const const_iterator& end) { m_array.erase(begin, end); }
	void remove(const const_iterator& element) { m_array.erase(element); }

	T&       first() { return m_array.front(); }
	const T& first() const { return m_array.front(); }

	T&       last() { return m_array.back(); }
	const T& last() const { return m_array.back(); }

	[[nodiscard]] T pop()
	{
		T last_element = last();
		m_array.pop_back();
		return last_element;
	}

	void pop_and_discard() { m_array.pop_back(); }

private:
	std::vector<T> m_array;
};
}