#include "Utils/File.h"
#include "Management/LogManager.h"

namespace SaturnEngine
{
	File::File(const String& path)
	{
		m_path = path.Pointer();
		m_fileHandle = CreateFileW(m_path.Pointer(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_DELETE, nullptr,
				OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if(m_fileHandle == INVALID_HANDLE_VALUE)
		{
			ST_THROW_ERROR(SaturnError::CouldNotOpenFile);
			return;
		}

		SetFilePointer(m_fileHandle, 0, nullptr, FILE_BEGIN);

		if(!WriteFile(m_fileHandle, &File::s_byteOrderMask, sizeof File::s_byteOrderMask, nullptr, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotOpenFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	File::~File()
	{
		if(!CloseHandle(m_fileHandle))
		{
			ST_THROW_ERROR(SaturnError::CouldNotCloseFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	void File::WriteText(const String& buffer)
	{
		//Before writing to a file truncate it to not cause corruption in the file itself
		SetFilePointer(m_fileHandle, 2, nullptr, FILE_BEGIN);
		SetEndOfFile(m_fileHandle);

		if(!WriteFile(m_fileHandle, buffer.Pointer(), buffer.Length() * sizeof(wchar_t), nullptr, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotModifyFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	void File::WriteBytes(const U8* buffer)
	{
		//Before writing to a file truncate it to not cause corruption in the file itself
		SetFilePointer(m_fileHandle, 0, nullptr, FILE_BEGIN);
		SetEndOfFile(m_fileHandle);

		if(!WriteFile(m_fileHandle, buffer, sizeof buffer, nullptr, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotModifyFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	String File::ReadText()
	{
		SetFilePointer(m_fileHandle, 2, nullptr, FILE_BEGIN);

		DWORD bytesToRead = GetFileSize(m_fileHandle, nullptr) - 2;
		String text(bytesToRead / sizeof(wchar_t));

		if(!ReadFile(m_fileHandle, text.Pointer(), bytesToRead, nullptr, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotReadFile);
			return {};
		}

		ST_CLEAR_ERROR();
		return text;
	}

	U8* File::ReadBytes()
	{
		SetFilePointer(m_fileHandle, 0, nullptr, FILE_BEGIN);

		auto* buffer = new U8[GetFileSize(m_fileHandle, nullptr)];

		if(!ReadFile(m_fileHandle, buffer, sizeof buffer, nullptr, nullptr))
		{
			ST_THROW_ERROR(SaturnError::CouldNotReadFile);
			return nullptr;
		}

		ST_CLEAR_ERROR();
		return buffer;
	}

	String File::Name() const
	{
		auto* name = new wchar_t[_MAX_FNAME];
		_wsplitpath_s(m_path.Pointer(), nullptr, 0, nullptr, 0, name, _MAX_FNAME, nullptr, 0);
		String str(name);
		delete[] name;

		return str;
	}

	String File::Drive() const
	{
		auto* drive = new wchar_t[_MAX_FNAME];
		_wsplitpath_s(m_path.Pointer(), drive, _MAX_DRIVE, nullptr, 0, nullptr, 0, nullptr, 0);
		String str(drive);
		delete[] drive;

		return str;
	}

	String File::Directory() const
	{
		auto* dir = new wchar_t[_MAX_FNAME];
		_wsplitpath_s(m_path.Pointer(), nullptr, 0, dir, _MAX_DIR, nullptr, 0, nullptr, 0);
		String str(dir);
		delete[] dir;

		return str;
	}

	String File::Extension() const
	{
		auto* ext = new wchar_t[_MAX_FNAME];
		_wsplitpath_s(m_path.Pointer(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
		String str(ext);
		delete[] ext;

		return str;
	}

	void File::Delete()
	{
		if(!DeleteFileW(m_path.Pointer()))
		{
			ST_THROW_ERROR(SaturnError::CouldNotModifyFile);
			return;
		}

		ST_CLEAR_ERROR();
	}
}
