#pragma once

#include "Utils/String.h"
#include "SaturnEngine/Core.h"

namespace SaturnEngine
{
	/**
	 * Type of errors in Saturn Engine.
	 *
	 * Very generic, more detailed error cause will most likely be logged to the console.
	 */
	enum class SaturnError : U8
	{
		Ok = 0,
		CouldNotStartUp = 1,
		CouldNotOpenFile = 2,
		CouldNotCloseFile = 3,
		CouldNotModifyFile = 4,
		CouldNotReadFile = 5,
		CouldNotShutDown = 6,
		MemoryOverflow = 7,
		InvalidArgument = 8,
		OperationPending = 9,
		AssertFailure = 10,
		NotFound = 11,
		Unknown = 255
	};

	/**
	 * Error management singleton in Saturn Engine.
	 *
	 * Every thrown error is being managed by this singleton. You can set and check the last error.
	 * You shall not use any other error throwing method.
	 */
	class SATURN_API ErrorSubsystem
	{
	public:
		ErrorSubsystem();
		ErrorSubsystem(const ErrorSubsystem& other) = delete;
		ErrorSubsystem(ErrorSubsystem&& other) = delete;
		~ErrorSubsystem();

		/**
		 * Returns the last thrown error.
		 *
		 * @return last thrown error
		 */
		SaturnError GetError();
		/**
		 * Throws an error.
		 *
		 * Thrown error can be checked later. Gets overwritten every time a new one is thrown.
		 *
		 * @param error error to throw
		 * @param fileName name of the file error occurred in
		 * @param lineNumber line number on which the error occurred
		 */
		void SetError(SaturnError error, const String& fileName, I32 lineNumber);
		/**
		 * Throws an error and displays the specified message.
		 *
		 * Thrown error can be checked later. Gets overwritten every time a new one is thrown.
		 *
		 * @param error error to throw
		 * @param fileName name of the file error occurred in
		 * @param lineNumber line number on which the error occurred
		 */
		void SetError(SaturnError error, const String& message, const String& fileName, I32 lineNumber);
		/**
		 * Clears the last throw error.
		 *
		 * In practice, just sets the latest thrown error to "Ok".
		 */
		void ClearError();

		//Singleton instance getter function. Present in every subsystem.
		static ErrorSubsystem* Get();

		ErrorSubsystem& operator=(const ErrorSubsystem& other) = delete;
		ErrorSubsystem& operator=(ErrorSubsystem&& other) = delete;

	private:
		static ErrorSubsystem* s_instance;

		SaturnError m_lastError;
	};
}

#define ST_THROW_ERROR(err) ErrorSubsystem::Get()->SetError(err, ST_MAKE_WIDE(__FILE__), __LINE__)
#define ST_THROW_ERROR_MSG(err, msg) ErrorSubsystem::Get()->SetError(err, msg, ST_MAKE_WIDE(__FILE__), __LINE__)
#define ST_LAST_ERROR() ErrorSubsystem::Get()->GetError()
//Do not overuse! Should only be called in functions that throw errors and only there.
#define ST_CLEAR_ERROR() ErrorSubsystem::Get()->ClearError()
#define ST_FAILED_ERROR() static_cast<U8>(ErrorSubsystem::Get()->GetError())
#define ST_ASSERT(exp, msg) if((exp)) { } else { ST_THROW_ERROR_MSG(SaturnEngine::SaturnError::AssertFailure, msg); abort(); __debugbreak(); }
