#pragma once

#include <Windows.h>

#include "Management/ErrorManager.h"
#include "Utils/String.h"

namespace SaturnEngine
{
	class SATURN_API File
	{
	public:
		File() = delete;
		explicit File(const String& path);
		~File();

		void WriteText( const String& buffer);
		void WriteBytes(const U8* buffer);
		String ReadText();
		U8* ReadBytes();

		String Name() const;
		String Drive() const;
		String Directory() const;
		String Extension() const;

	public:
		//Byte Order Mask for UTF-16 LE encoding
		static constexpr wchar_t s_byteOrderMask = 0xFEFF;

	private:
		HANDLE m_fileHandle;
		String m_path;
	};
}
