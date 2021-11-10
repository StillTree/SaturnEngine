#pragma once

#include <Windows.h>

#include "Utils/Errors.h"
#include "Management/LogManager.h"

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
			return wcsrchr(Path, '/') + 1;
		}

		inline const wchar_t* Directory() const
		{
			size_t size = wcsrchr(Path, '/') - Path;
			wchar_t* dir = new wchar_t[size / 2];
			memcpy((void*) dir, Path, size * 2);
			dir[size] = L'\0';

			return dir;
		}

		inline const wchar_t* Extension() const
		{
			return wcsrchr(Path, '.') + 1;
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
