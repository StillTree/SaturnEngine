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
		/**
		 * An absurdly slow iterator for Saturn Engine's string class.
		 *
		 * Uses UTF-16 LE encoding.
		 */
		class SATURN_API Iterator
		{
		public:
			//You can't create an empty iterator
			Iterator() = delete;
			explicit Iterator(wchar_t* ptr);
			~Iterator() = default;

			Iterator& operator++();
			Iterator& operator--();
			Iterator operator++(I32);
			Iterator operator--(I32);
			wchar_t& operator*();
			wchar_t* operator->();
			bool operator<(const Iterator& other);
			bool operator>(const Iterator& other);
			bool operator==(const Iterator& other);
			bool operator!=(const Iterator& other);

		private:
			wchar_t* m_ptr;
		};

		//Initializes an empty string, with null byte included
		String();
		/**
		 * Initializes the string with the `const char*` provided.
		 *
		 * It is explicit to make it easier to use.
		 */
		String(const wchar_t* str);
		//Initializes and empty string with the number of characters specified.
		explicit String(U64 size);
		~String();

		String(const String& other);
		String(String&& other) noexcept;

		String& operator=(const wchar_t* str);
		String& operator=(const String& other);
		String& operator=(String&& other) noexcept;
		bool operator==(const String& other);
		bool operator!=(const String& other);
		bool operator==(const wchar_t* str);
		bool operator!=(const wchar_t* str);
		const wchar_t& operator[](U64 index) const;
		wchar_t& operator[](U64 index);

		//Returns the length of the string currently being stored.
		inline U64 Length() const;
		//Returns a constant pointer to the string currently being stored.
		inline const wchar_t* Pointer() const;
		//Returns a non-constant pointer to the string currently being stored.
		inline wchar_t* Pointer();

		//Returns an iterator at the beginning of the string.
		inline Iterator begin();
		//Returns an iterator at the end of the string.
		inline Iterator end();
		/**
		 * Reallocates the currently stored string, with the new size provided.
		 *
		 * If the size is too small, reallocation will abort.
		 *
		 * @param newSize size of the new buffer
		 */
		void ReAlloc(U64 newSize);
	private:
		wchar_t* m_str;
		U64 m_size;
	};
}
