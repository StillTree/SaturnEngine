#pragma once

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
		Unknown = 255
	};

	/**
	 * Error management singleton in Saturn Engine.
	 *
	 * Every thrown error is being managed by this singleton. You can set and check the last error.
	 * You shall not use any other error throwing method.
	 */
	class SATURN_API ErrorManager
	{
	public:
		ErrorManager();
		~ErrorManager() = default;

		// Start up function. Present in every manager.
		void StartUp();
		// Shut down function. Present in every manager.
		void ShutDown();
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
		void SetError(SaturnError error, const char* fileName, I32 lineNumber);
		/**
		 * Clears the last throw error.
		 *
		 * In practice, just sets the latest thrown error to "Ok".
		 */
		void ClearError();
		//Singleton instance getter function. Present in every manager.
		static ErrorManager* Get();

		ErrorManager(const ErrorManager& other) = default;
		ErrorManager(ErrorManager&& other) = default;

		ErrorManager& operator=(const ErrorManager& other) = default;
		ErrorManager& operator=(ErrorManager&& other) = default;

	private:
		static ErrorManager* s_instance;

		SaturnError m_lastError;
	};
}

#define ST_THROW_ERROR(err) ErrorManager::Get()->SetError(err, __FILE__, __LINE__)
#define ST_LAST_ERROR() ErrorManager::Get()->GetError()
//Do not overuse! Should only be called in functions that throw errors and only there.
#define ST_CLEAR_ERROR() ErrorManager::Get()->ClearError()
#define ST_FAILED_ERROR() static_cast<U8>(ErrorManager::Get()->GetError())
