#include "Utils/File.h"
#include "Management/ErrorManager.h"

namespace SaturnEngine
{
	void OpenFile(File& fileData)
	{
		fileData.FileHandle = CreateFileW(fileData.Path, GENERIC_READ | GENERIC_WRITE,
				0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if(fileData.FileHandle == INVALID_HANDLE_VALUE)
		{
			ST_THROW_ERROR(SaturnError::CouldNotOpenFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	void TextToFile(const File& fileData, const wchar_t* buffer)
	{
		DWORD bytesWritten = 0;

		if(!WriteFile(fileData.FileHandle, &c_bom, sizeof c_bom, nullptr, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotWriteToFile);
			return;
		}
		SetFilePointer(fileData.FileHandle, 0, nullptr, FILE_END);

		if(!WriteFile(fileData.FileHandle, buffer, wcslen(buffer) * sizeof(wchar_t), &bytesWritten, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotWriteToFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	void BytesToFile(const File& fileData, const U8* buffer)
	{
		DWORD bytesWritten = 0;

		SetFilePointer(fileData.FileHandle, 0, nullptr, FILE_BEGIN);
		if(!WriteFile(fileData.FileHandle, buffer, sizeof buffer, &bytesWritten, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotWriteToFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	void SATURN_API TextFromFile(const File& fileData, wchar_t* buffer)
	{
		DWORD bytesRead = 0;

		SetFilePointer(fileData.FileHandle, 2, nullptr, FILE_BEGIN);
		if(!ReadFile(fileData.FileHandle, buffer, wcslen(buffer) * sizeof(wchar_t), &bytesRead, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotReadFromFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	void SATURN_API BytesFromFile(const File& fileData, U8* buffer)
	{
		DWORD bytesRead = 0;

		SetFilePointer(fileData.FileHandle, 0, nullptr, FILE_BEGIN);
		if(!ReadFile(fileData.FileHandle, buffer, sizeof buffer, &bytesRead, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotReadFromFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	void CloseFile(const File& fileData)
	{
		if(!CloseHandle(fileData.FileHandle))
		{
			ST_THROW_ERROR(SaturnError::CouldNotCloseFile);
			return;
		}

		ST_CLEAR_ERROR();
	}
}
