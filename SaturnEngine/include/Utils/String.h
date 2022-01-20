#pragma once

#include "SaturnEngine/Core.h"

#include <cstring>

namespace SaturnEngine
{
	class SATURN_API String
	{
	public:
		String();
		String(const wchar_t* str);
		explicit String(size_t size);
		~String();

		String(String& other);
		String(String&& other) noexcept;

		String& operator=(const wchar_t* str);
		String& operator=(const String& other);
		String& operator=(String&& other) noexcept;
		bool operator==(const String& other);
		bool operator!=(const String& other);

		size_t Length() const;
		const wchar_t* Pointer() const;
		wchar_t* Pointer();
		void ReAlloc(size_t newSize);
	private:
		wchar_t* m_str;
	};
}
