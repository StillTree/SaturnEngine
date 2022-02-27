#pragma once

#include "Management/ErrorManager.h"
#include "Utils/String.h"

namespace SaturnEngine
{
	/**
	 * File API for Saturn Engine.
	 *
	 * Synchronous for now, made with WinAPI. If the file doesn't exists, it will automatically be created.
	 */
	class SATURN_API File
	{
	public:
		//You cannot initialize a file without a path to it.
		File() = delete;
		explicit File(const String& path);
		~File();

		/**
		 * Writes text asynchronously to the current file.
		 *
		 * Overrides the file and uses an UTF-16 LE byte order mask.
		 *
		 * @param text text to write
		 */
		void AsyncWriteText(const String& text);
		/**
		 * Writes pure bytes asynchronously to the current file.
		 *
		 * Overrides the file and does not use any byte order mask.
		 *
		 * @param buffer pointer to the buffer containing the bytes to write
		 */
		void AsyncWriteBytes(const U8* buffer);
		/**
		 * Writes text synchronously to the current file.
		 *
		 * Overrides the file and uses an UTF-16 LE byte order mask.
		 *
		 * @param text text to write
		 */
		void WriteText(const String& text);
		/**
		 * Writes pure bytes synchronously to the current file.
		 *
		 * Overrides the file and does not use any byte order mask.
		 *
		 * @param buffer pointer to the buffer containing the bytes to write
		 */
		void WriteBytes(const U8* buffer);
		/**
		 * Reads text asynchronously.
		 *
		 * Accounts for UTF-16 LE byte order mask only. It is recommended that every file read,
		 * should have an UTF-16 LE byte order mask.
		 *
		 * @return string with the file contains
		 */
		String AsyncReadText();
		/**
		 * Reads bytes asynchronously.
		 *
		 * No byte order mask is being accounted for. Buffer returned must be handled by the user.
		 *
		 * @return pointer to an initialized buffer with contains of the file
		 */
		U8* AsyncReadBytes();
		/**
		 * Reads text synchronously.
		 *
		 * Accounts for UTF-16 LE byte order mask only. It is recommended that every file read,
		 * should have an UTF-16 LE byte order mask.
		 *
		 * @return string with the file contains
		 */
		String ReadText();
		/**
		 * Reads bytes synchronously.
		 *
		 * No byte order mask is being accounted for. Buffer returned must be handled by the user.
		 *
		 * @return pointer to an initialized buffer with contains of the file
		 */
		U8* ReadBytes();

		/**
		 * Checks if an asynchronous operation has been completed.
		 *
		 * @return completion status of the operation
		 */
		bool AsyncOperationCompleted();
		/**
		 * Checks if an asynchronous operation has been completed.
		 *
		 * @param bytesTransferred returns the number of bytes transferred
		 *
		 * @return completion status of the operation
		 */
		bool AsyncOperationCompleted(U32& bytesTransferred);

		//Returns the name of the file
		String Name() const;
		//Returns the drive letter of the file on which it is currently being stored
		String Drive() const;
		//Returns the directory in which the file is currently being stored
		String Directory() const;
		//Returns extension of the file
		String Extension() const;

	public:
		//Byte Order Mask for UTF-16 LE encoding.
		static constexpr wchar_t s_byteOrderMask = 0xFEFF;

	private:
		OVERLAPPED m_overlapped;
		HANDLE m_fileHandle;
		String m_path;
	};
}
