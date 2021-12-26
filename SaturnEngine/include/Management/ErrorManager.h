#pragma once

#include "Utils/Errors.h"

namespace SaturnEngine
{
	class SATURN_API ErrorManager
	{
	public:
		ErrorManager();
		~ErrorManager() = default;

		void StartUp();
		void ShutDown();
		SaturnError GetError();
		void SetError(SaturnError error);
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

#define ST_THROW_ERROR(err) ErrorManager::Get()->SetError(err)
#define ST_LAST_ERROR() ErrorManager::Get()->GetError()
#define ST_CLEAR_ERROR() ErrorManager::Get()->ClearError()
