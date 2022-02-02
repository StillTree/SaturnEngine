#pragma once

#include "SaturnEngine/Core.h"

#include <cstring>

namespace SaturnEngine
{
	/**
	 * String class for Saturn Engine.
	 *
	 * Uses UTF-16 LE encoding.
	 */
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

		// Returns the length of the string currently being stored.
		size_t Length() const;
		// Returns a constant pointer to the string currently being stored.
		const wchar_t* Pointer() const;
		// Returns a non-constant pointer to the string currently being stored.
		wchar_t* Pointer();
		/**
		 * Reallocates the currently stored string, with the new size provided.
		 *
		 * If the size is too small, reallocation will abort.
		 *
		 * @param newSize size of the new buffer
		 */
		void ReAlloc(size_t newSize);
	private:
		wchar_t* m_str;
	};
}
