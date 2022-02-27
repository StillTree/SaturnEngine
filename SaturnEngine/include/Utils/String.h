#pragma once

#include "SaturnEngine/Core.h"

namespace SaturnEngine
{
	/**
	 * An absurdly slow string class for Saturn Engine.
	 *
	 * Uses UTF-16 LE encoding.
	 */
	class SATURN_API String
	{
	public:
		//Initializes an empty string, with null byte included
		String();
		/**
		 * Initializes the string with the `const char*` provided.
		 *
		 * It is explicit to make it easier to use.
		 */
		String(const wchar_t* str);
		//Initializes and empty string with the number of bytes specified.
		explicit String(size_t size);
		~String();

		String(const String& other);
		String(String&& other) noexcept;

		String& operator=(const wchar_t* str);
		String& operator=(const String& other);
		String& operator=(String&& other) noexcept;
		bool operator==(const String& other);
		bool operator!=(const String& other);

		//Returns the length of the string currently being stored.
		inline size_t Length() const;
		//Returns a constant pointer to the string currently being stored.
		inline const wchar_t* Pointer() const;
		//Returns a non-constant pointer to the string currently being stored.
		inline wchar_t* Pointer();
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
