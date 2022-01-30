#pragma once

#include "SaturnEngine/Core.h"

namespace SaturnEngine
{
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
		Unknown = 255
	};

	class SATURN_API ErrorManager
	{
	public:
		ErrorManager();
		~ErrorManager() = default;

		void StartUp();
		void ShutDown();
		SaturnError GetError();
		void SetError(SaturnError error, const char* fileName, int lineNumber);
		void ClearError();
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
//Do not overuse! Should only be called in function that throw errors and only there.
#define ST_CLEAR_ERROR() ErrorManager::Get()->ClearError()
#define ST_FAILED_ERROR() static_cast<U8>(ErrorManager::Get()->GetError())
