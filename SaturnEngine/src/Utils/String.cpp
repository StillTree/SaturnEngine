#include "Utils/String.h"

#include "Management/ErrorManager.h"

namespace SaturnEngine
{
	String::String()
	{
		m_str = new wchar_t[1];
		m_str[0] = L'\0';
	}

	String::String(const wchar_t* str)
	{
		if(str == nullptr)
		{
			ST_THROW_ERROR(SaturnError::InvalidArgument);
			m_str = new wchar_t[1];
			m_str[0] = L'\0';

			return;
		}

		m_str = new wchar_t[wcslen(str) + 1];
		wcscpy_s(m_str, wcslen(str) + 1, str);
		m_str[wcslen(str)] = L'\0';

		ST_CLEAR_ERROR();
	}

	String::String(size_t size)
	{
		m_str = new wchar_t[size + 1];
		m_str[size] = L'\0';
	}

	String::~String()
	{
		delete[] m_str;
	}

	String::String(const String& other)
	{
		m_str = new wchar_t[wcslen(other.m_str) + 1];
		wcscpy_s(m_str, wcslen(other.m_str) + 1, other.m_str);
		m_str[wcslen(other.m_str)] = L'\0';
	}

	String::String(String&& other) noexcept
	{
		m_str = other.m_str;
		other.m_str = nullptr;
	}

	size_t String::Length() const
	{
		return wcslen(m_str);
	}

	const wchar_t* String::Pointer() const
	{
		return m_str;
	}

	wchar_t* String::Pointer()
	{
		return m_str;
	}

	String& String::operator=(const String& other)
	{
		auto* new_str = new wchar_t[wcslen(other.m_str) + 1];
		wcscpy_s(new_str, wcslen(other.m_str) + 1, other.m_str);

		delete[] m_str;
		m_str = new_str;

		return *this;
	}

	String& String::operator=(String&& other) noexcept
	{
		m_str = other.m_str;
		other.m_str = nullptr;

		return *this;
	}

	String& String::operator=(const wchar_t* str)
	{
		if(str == nullptr)
		{
			ST_THROW_ERROR(SaturnError::InvalidArgument);
			m_str = new wchar_t[1];
			m_str[0] = L'\0';

			return *this;
		}

		m_str = new wchar_t[wcslen(str) + 1];
		wcscpy_s(m_str, wcslen(str) + 1, str);
		m_str[wcslen(str)] = L'\0';

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

	void String::ReAlloc(size_t newSize)
	{
		if(wcslen(m_str) > newSize)
		{
			ST_THROW_ERROR(SaturnError::InvalidArgument);
			return;
		}

		auto* newStr = new wchar_t[newSize + 1];

		for(size_t i = 0; i < wcslen(m_str); ++i)
		{
			newStr[i] = m_str[i];
		}
		newStr[newSize] = L'\0';

		delete[] m_str;
		m_str = newStr;

		ST_CLEAR_ERROR();
	}
}
