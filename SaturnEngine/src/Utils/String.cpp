#include "Utils/String.h"

#include "Management/ErrorManager.h"

namespace SaturnEngine
{
	String::Iterator::Iterator(wchar_t* ptr)
		: m_ptr(ptr)
	{
	}

	String::Iterator& String::Iterator::operator++()
	{
		m_ptr++;
		return *this;
	}

	String::Iterator& String::Iterator::operator--()
	{
		return *this;
	}

	String::Iterator String::Iterator::operator++(I32)
	{
		String::Iterator iterator = *this;
		++(*this);
		return iterator;
	}

	String::Iterator String::Iterator::operator--(I32)
	{
		String::Iterator iterator = *this;
		++(*this);
		return iterator;
	}

	wchar_t& String::Iterator::operator*()
	{
		return *m_ptr;
	}

	wchar_t* String::Iterator::operator->()
	{
		return m_ptr;
	}

	bool String::Iterator::operator<(const Iterator& other)
	{
		return m_ptr < other.m_ptr;
	}

	bool String::Iterator::operator>(const Iterator& other)
	{
		return m_ptr > other.m_ptr;
	}

	bool String::Iterator::operator==(const String::Iterator& other)
	{
		return m_ptr == other.m_ptr;
	}

	bool String::Iterator::operator!=(const String::Iterator& other)
	{
		return m_ptr != other.m_ptr;
	}

	String::String()
		: m_size(0)
	{
		m_str = new wchar_t[1];
		m_str[0] = L'\0';
	}

	String::String(const wchar_t* str)
		: m_size(wcslen(str))
	{
		if(str == nullptr)
		{
			ST_THROW_ERROR(SaturnError::InvalidArgument);
			m_str = new wchar_t[1];
			m_str[0] = L'\0';

			return;
		}

		m_str = new wchar_t[m_size + 1];
		wcscpy_s(m_str, m_size + 1, str);
		m_str[m_size] = L'\0';

		ST_CLEAR_ERROR();
	}

	String::String(U64 size)
		: m_size(size)
	{
		m_str = new wchar_t[m_size + 1];
		m_str[m_size] = L'\0';
	}

	String::~String()
	{
		delete[] m_str;
	}

	String::String(const String& other)
		: m_size(other.m_size)
	{
		m_str = new wchar_t[other.m_size + 1];
		wcscpy_s(m_str, other.m_size + 1, other.m_str);
		m_str[other.m_size] = L'\0';
	}

	String::String(String&& other) noexcept
	{
		m_str = other.m_str;
		other.m_str = nullptr;
		m_size = other.m_size;
		other.m_size = 0;
	}

	String& String::operator=(const String& other)
	{
		auto* newStr = new wchar_t[m_size + 1];
		wcscpy_s(newStr, m_size + 1, other.m_str);

		delete[] m_str;
		m_str = newStr;
		m_size = other.m_size;

		return *this;
	}

	String& String::operator=(String&& other) noexcept
	{
		m_str = other.m_str;
		other.m_str = nullptr;
		m_size = other.m_size;
		other.m_size = 0;

		return *this;
	}

	String& String::operator=(const wchar_t* str)
	{
		if(str == nullptr)
		{
			ST_THROW_ERROR(SaturnError::InvalidArgument);
			m_str = new wchar_t[1];
			m_str[0] = L'\0';
			m_size = 0;

			return *this;
		}

		m_size = wcslen(str);
		m_str = new wchar_t[m_size + 1];
		wcscpy_s(m_str, m_size + 1, str);
		m_str[m_size] = L'\0';

		ST_CLEAR_ERROR();
		return *this;
	}

	bool String::operator==(const String& other)
	{
		return !wcscmp(m_str, other.m_str);
	}

	bool String::operator!=(const String& other)
	{
		return wcscmp(m_str, other.m_str);
	}

	bool String::operator==(const wchar_t* str)
	{
		return !wcscmp(m_str, str);
	}

	bool String::operator!=(const wchar_t* str)
	{
		return wcscmp(m_str, str);
	}

	wchar_t& String::operator[](U64 index)
	{
		return m_str[index];
	}

	const wchar_t& String::operator[](U64 index) const
	{
		return m_str[index];
	}

	U64 String::Length() const
	{
		return m_size;
	}

	const wchar_t* String::Pointer() const
	{
		return m_str;
	}

	wchar_t* String::Pointer()
	{
		return m_str;
	}

	String::Iterator String::begin()
	{
		return String::Iterator(m_str);
	}

	String::Iterator String::end()
	{
		return String::Iterator(m_str + m_size);
	}

	void String::ReAlloc(U64 newSize)
	{
		if(m_size > newSize)
		{
			ST_THROW_ERROR(SaturnError::InvalidArgument);
			return;
		}

		auto* newStr = new wchar_t[newSize + 1];

		for(U64 i = 0; i < m_size; ++i)
		{
			newStr[i] = m_str[i];
		}
		newStr[newSize] = L'\0';

		delete[] m_str;
		m_str = newStr;
		m_size = newSize;

		ST_CLEAR_ERROR();
	}
}
