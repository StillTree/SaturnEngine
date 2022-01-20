#include <cassert>

#include "Management/ErrorManager.h"
#include "Management/LogManager.h"

namespace SaturnEngine
{
	ErrorManager* ErrorManager::s_instance = nullptr;

	ErrorManager::ErrorManager()
	{
		assert(!s_instance && L"You can't create a second instance of ErrorManager!");
		s_instance = this;
	}

	void ErrorManager::StartUp()
	{
		m_lastError = SaturnError::Ok;
	}

	void ErrorManager::ShutDown()
	{
		m_lastError = SaturnError::Ok;
	}

	ErrorManager* ErrorManager::Get()
	{
		return s_instance;
	}

	SaturnError ErrorManager::GetError()
	{
		return m_lastError;
	}

	void ErrorManager::SetError(SaturnError error)
	{
#ifdef ST_BUILD_DEBUG
		ST_ERROR("An error occurred with code {0}!", error);
#endif

		m_lastError = error;
	}

	void ErrorManager::ClearError()
	{
		m_lastError = SaturnError::Ok;
	}
}
