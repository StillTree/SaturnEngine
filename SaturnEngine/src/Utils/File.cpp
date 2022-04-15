#include "Utils/File.h"

#include "Management/LogSubsystem.h"

namespace SaturnEngine
{
	File::File(const String& path)
		: m_path(path.Pointer()), m_overlapped()
	{
		m_fileHandle = CreateFileW(m_path.Pointer(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr,
				OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, nullptr);
		m_overlapped.hEvent = CreateEvent(nullptr, true, false, nullptr);

		if(m_fileHandle == INVALID_HANDLE_VALUE)
		{
			ST_THROW_ERROR(SaturnError::CouldNotOpenFile);
			return;
		}

		wchar_t bom;
		if(!ReadFile(m_fileHandle, &bom, 2, nullptr, &m_overlapped))
		{
			if(GetLastError() != ERROR_IO_PENDING)
			{
				ST_THROW_ERROR(SaturnError::CouldNotReadFile);
				return;
			}
		}
		WaitForSingleObject(m_overlapped.hEvent, INFINITE);
		if(bom != s_byteOrderMask)
		{
			ST_WARN(L"Invalid byte order mask, writing a new one. File data may be corrupt.");
			WriteByteOrderMask();

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

		if(!CloseHandle(m_overlapped.hEvent))
		{
			ST_THROW_ERROR(SaturnError::CouldNotCloseFile);
			return;
		}

		ST_CLEAR_ERROR();
	}

	void File::AsyncWriteText(const String& text)
	{
		if(!AsyncOperationCompleted())
		{
			ST_THROW_ERROR(SaturnError::OperationPending);
			return;
		}

		//Before writing to a file truncate it and rewrite the byte order mask
		Truncate();
		WriteByteOrderMask();
		m_overlapped.Offset = 2;

		if(!WriteFile(m_fileHandle, text.Pointer(), text.Length() * sizeof(wchar_t), nullptr, &m_overlapped))
		{
			if(GetLastError() != ERROR_IO_PENDING)
			{
				ST_THROW_ERROR(SaturnError::CouldNotModifyFile);
				return;
			}
		}

		ST_CLEAR_ERROR();
		m_overlapped.Offset = 0;
	}

	void File::AsyncWriteBytes(const U8* buffer)
	{
		if(!AsyncOperationCompleted())
		{
			ST_THROW_ERROR(SaturnError::OperationPending);
			return;
		}

		//Before writing to a file truncate it
		Truncate();
		if(!WriteFile(m_fileHandle, buffer, sizeof buffer, nullptr, &m_overlapped))
		{
			if(GetLastError() != ERROR_IO_PENDING)
			{
				ST_THROW_ERROR(SaturnError::CouldNotModifyFile);
				return;
			}
		}

		ST_CLEAR_ERROR();
	}

	void File::WriteText(const String& text)
	{
		AsyncWriteText(text);
		if(ST_FAILED_ERROR())
		{
			return;
		}
		WaitForSingleObject(m_overlapped.hEvent, INFINITE);
	}

	void File::WriteBytes(const U8* buffer)
	{
		AsyncWriteBytes(buffer);
		if(ST_FAILED_ERROR())
		{
			return;
		}
		WaitForSingleObject(m_overlapped.hEvent, INFINITE);
	}

	String File::AsyncReadText()
	{
		if(!AsyncOperationCompleted())
		{
			ST_THROW_ERROR(SaturnError::OperationPending);
			return {};
		}

		m_overlapped.Offset = 2;
		U32 bytesToRead = GetFileSize(m_fileHandle, nullptr);
		String text(bytesToRead / sizeof(wchar_t) - 1);

		if(!ReadFile(m_fileHandle, text.Pointer(), bytesToRead, nullptr, &m_overlapped))
		{
			if(GetLastError() != ERROR_IO_PENDING)
			{
				ST_THROW_ERROR(SaturnError::CouldNotReadFile);
				return {};
			}
		}

		ST_CLEAR_ERROR();
		m_overlapped.Offset = 0;
		return text;
	}

	U8* File::AsyncReadBytes()
	{
		if(!AsyncOperationCompleted())
		{
			ST_THROW_ERROR(SaturnError::OperationPending);
			return nullptr;
		}

		U32 bytesToRead = GetFileSize(m_fileHandle, nullptr);
		auto* buffer = new U8[bytesToRead];

		if(!ReadFile(m_fileHandle, buffer, bytesToRead, nullptr, &m_overlapped))
		{
			if(GetLastError() != ERROR_IO_PENDING)
			{
				ST_THROW_ERROR(SaturnError::CouldNotReadFile);
				return nullptr;
			}
		}

		ST_CLEAR_ERROR();
		return buffer;
	}

	String File::ReadText()
	{
		String str = std::move(AsyncReadText());
		if(ST_FAILED_ERROR())
		{
			return {};
		}
		WaitForSingleObject(m_overlapped.hEvent, INFINITE);

		return str;
	}

	U8* File::ReadBytes()
	{
		U8* buffer = AsyncReadBytes();
		if(ST_FAILED_ERROR())
		{
			return nullptr;
		}
		WaitForSingleObject(m_overlapped.hEvent, INFINITE);

		return buffer;
	}

	bool File::AsyncOperationCompleted()
	{
		//Discarding the number of bytes transferred, although it is required to pass into the method
		DWORD bytesTransferred;
		BOOL finished = GetOverlappedResult(m_fileHandle, &m_overlapped, &bytesTransferred, false);
		//I don't really know how to deal with that, so there's a hacky workaround
		if(GetLastError() == ERROR_HANDLE_EOF)
		{
			return !finished;
		}
		return finished;
	}

	bool File::AsyncOperationCompleted(U32& bytesTransferred)
	{
		//Creating and passing it through a method to not mess with sketchy casts
		DWORD transferred;
		bool finished = GetOverlappedResult(m_fileHandle, &m_overlapped, &transferred, false);
		bytesTransferred = transferred;
		//I don't really know how to deal with that, so there's a hacky workaround
		if(GetLastError() == ERROR_HANDLE_EOF)
		{
			return !finished;
		}
		return finished;
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

	void File::Truncate()
	{
		SetFilePointer(m_fileHandle, 0, nullptr, FILE_BEGIN);
		SetEndOfFile(m_fileHandle);
	}

	void File::WriteByteOrderMask()
	{
		if(!WriteFile(m_fileHandle, &File::s_byteOrderMask, sizeof File::s_byteOrderMask, nullptr, &m_overlapped))
		{
			if(GetLastError() != ERROR_IO_PENDING)
			{
				ST_THROW_ERROR(SaturnError::CouldNotModifyFile);
				return;
			}
		}
		WaitForSingleObject(m_overlapped.hEvent, INFINITE);

		ST_CLEAR_ERROR();
	}
}
