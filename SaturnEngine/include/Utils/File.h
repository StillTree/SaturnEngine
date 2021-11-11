#pragma once

#include <Windows.h>

#include "Utils/Errors.h"

namespace SaturnEngine
{
	//Byte Order Mask for UTF-16 LE encoding
	constexpr wchar_t c_bom = 0xFEFF;

	typedef struct File
	{
		HANDLE FileHandle;
		const wchar_t* Path;

		inline const wchar_t* Name() const
		{
			wchar_t* name = new wchar_t[_MAX_FNAME];
			_wsplitpath_s(Path, nullptr, 0, nullptr, 0, name, _MAX_FNAME, nullptr, 0);

			return name;
		}

		inline const wchar_t* Drive() const
		{
			wchar_t* drive = new wchar_t[_MAX_DRIVE];
			_wsplitpath_s(Path, drive, _MAX_DRIVE, nullptr, 0, nullptr, 0, nullptr, 0);

			return drive;
		}

		inline const wchar_t* Directory() const
		{
			wchar_t* dir = new wchar_t[_MAX_DIR];
			_wsplitpath_s(Path, nullptr, 0, dir, _MAX_DIR, nullptr, 0, nullptr, 0);

			return dir;
		}

		inline const wchar_t* Extension() const
		{
			wchar_t* ext = new wchar_t[_MAX_EXT];
			_wsplitpath_s(Path, nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);

			return ext;
		}

		~File()
		{
			CloseHandle(FileHandle);
		}
	} File;

	SaturnError SATURN_API OpenFile(File& fileData);
	SaturnError SATURN_API TextToFile(const File& fileData, const wchar_t* buffer);
	SaturnError SATURN_API BytesToFile(const File& fileData, const U8* buffer);
	SaturnError SATURN_API TextFromFile(const File& fileData, wchar_t* buffer);
	SaturnError SATURN_API BytesFromFile(const File& fileData, U8* buffer);
	SaturnError SATURN_API CloseFile(const File& fileData);
}
