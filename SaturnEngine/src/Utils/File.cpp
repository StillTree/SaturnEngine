#include "Utils/File.h"
#include "Management/LogManager.h"

namespace SaturnEngine
{
	SaturnError OpenFile(File& fileData)
	{
		fileData.FileHandle = CreateFileW(fileData.Path, GENERIC_READ | GENERIC_WRITE,
				0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if(fileData.FileHandle == INVALID_HANDLE_VALUE)
		{
			ST_LOG_ERROR("Could not open a file with error code {0}", GetLastError());

			return SaturnError::CouldNotOpenFile;
		}

		return SaturnError::Ok;
	}

	SaturnError TextToFile(const File& fileData, const wchar_t* buffer)
	{
		DWORD bytesWritten = 0;

		if(!WriteFile(fileData.FileHandle, &c_bom, sizeof c_bom, nullptr, nullptr))
		{
			ST_LOG_ERROR("Failed to write Byte Order Mask to a file with error code {1}", GetLastError());

			return SaturnError::CouldNotWriteToFile;
		}
		SetFilePointer(fileData.FileHandle, 0, nullptr, FILE_END);

		if(!WriteFile(fileData.FileHandle, buffer, wcslen(buffer) * sizeof(wchar_t), &bytesWritten, nullptr))
		{
			ST_LOG_ERROR("Failed to write contents to a file, {0} bytes were written with error code {1}", bytesWritten, GetLastError());

			return SaturnError::CouldNotWriteToFile;
		}

		return SaturnError::Ok;
	}

	SaturnError BytesToFile(const File& fileData, const U8* buffer)
	{
		DWORD bytesWritten = 0;

		SetFilePointer(fileData.FileHandle, 0, nullptr, FILE_BEGIN);
		if(!WriteFile(fileData.FileHandle, buffer, sizeof buffer, &bytesWritten, nullptr))
		{
			ST_LOG_ERROR("Failed to write contents to a file, {0} bytes were written with error code {1}", bytesWritten, GetLastError());

			return SaturnError::CouldNotWriteToFile;
		}

		return SaturnError::Ok;
	}

	SaturnError SATURN_API TextFromFile(const File& fileData, wchar_t* buffer)
	{
		DWORD bytesRead = 0;

		SetFilePointer(fileData.FileHandle, 2, nullptr, FILE_BEGIN);
		if(!ReadFile(fileData.FileHandle, buffer, wcslen(buffer) * sizeof(wchar_t), &bytesRead, nullptr))
		{
			ST_LOG_ERROR("Failed to read contents of a file, {0} bytes were read with error code {1}", bytesRead, GetLastError());

			return SaturnError::CouldNotReadFromFile;
		}

		return SaturnError::Ok;
	}

	SaturnError SATURN_API BytesFromFile(const File& fileData, U8* buffer)
	{
		DWORD bytesRead = 0;

		SetFilePointer(fileData.FileHandle, 0, nullptr, FILE_BEGIN);
		if(!ReadFile(fileData.FileHandle, buffer, sizeof buffer, &bytesRead, nullptr))
		{
			ST_LOG_ERROR("Failed to read contents of a file, {0} bytes were read with error code {1}", bytesRead, GetLastError());

			return SaturnError::CouldNotReadFromFile;
		}

		return SaturnError::Ok;
	}

	SaturnError CloseFile(const File& fileData)
	{
		if(!CloseHandle(fileData.FileHandle))
		{
			ST_LOG_ERROR("Failed to close a file with error code {0}", GetLastError());

			return SaturnError::CouldNotCloseFile;
		}

		return SaturnError::Ok;
	}
}
