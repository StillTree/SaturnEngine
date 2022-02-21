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
		 * Writes text to the current file.
		 *
		 * Doesn't overwrite text being currently written in a file, appends to it. Uses an UTF-16 LE byte order mask.
		 *
		 * @param buffer text to write
		 */
		void WriteText(const String& buffer);
		/**
		 * Writes pure bytes to the file, not byte order mask or anything.
		 *
		 * @param buffer pointer to the buffer containing the bytes to write
		 */
		void WriteBytes(const U8* buffer);
		/**
		 * Returns text written to a file.
		 *
		 * Accounts for UTF-16 LE byte order mask only. It is recommended that every file read that way,
		 * should have an UTF-16 LE byte order mask.
		 *
		 * @return
		 */
		String ReadText();
		/**
		 * Returns pure bytes written to the file.
		 *
		 * No byte order mask is being accounted to.
		 *
		 * @return pointer to an initialized buffer with contains of the file
		 */
		U8* ReadBytes();

		//Deletes current file.
		void Delete();

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
		HANDLE m_fileHandle;
		String m_path;
	};
}
