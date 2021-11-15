#pragma once

#include <beard/core/macros.h>

#include <utility>

namespace beard
{

template <typename T>
class optional
{
public:
	optional() = default;
	optional(const T& value) // NOLINT we want implicit conversions in this specific case
	    : m_value{value}
	    , m_has_value{true}
	{
	}

	optional(T&& value) // NOLINT we want implicit conversions in this specific case
	    : m_value{std::move(value)}
	    , m_has_value{true}
	{
	}

	DEFAULT_COPYABLE(optional);
	DEFAULT_MOVEABLE(optional);

	~optional() = default;

	optional& operator=(const T& value)
	{
		m_value     = value;
		m_has_value = true;
		return *this;
	}

	optional& operator=(T&& value)
	{
		m_value     = std::move(value);
		m_has_value = true;
		return *this;
	}

	[[nodiscard]] bool has_value() const { return m_has_value; }

	[[nodiscard]] const T& value() const { return m_value; }

	[[nodiscard]] T& value() { return m_value; }

	bool operator==(const optional<T>& other) const
	{
		if (has_value() && other.has_value()) { return value() == other.value(); }
		return false;
	}

private:
	T    m_value     = {};
	bool m_has_value = false;
};

}