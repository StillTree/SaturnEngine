#include "Management/ErrorManager.h"

#include "Management/LogManager.h"

namespace SaturnEngine
{
	ErrorManager* ErrorManager::s_instance = nullptr;

	ErrorManager::ErrorManager() : m_lastError(SaturnError::Ok)
	{
		assert(!s_instance && L"You can't create a second instance of ErrorManager!");
		s_instance = this;
	}

	ErrorManager::~ErrorManager()
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

	void ErrorManager::SetError(SaturnError error, const char* fileName, I32 lineNumber)
	{
#ifdef ST_BUILD_DEBUG
		ST_ERROR("Error {0} was thrown in {1}: {2}", error, fileName, lineNumber);
#endif

		m_lastError = error;
	}

	void ErrorManager::ClearError()
	{
		m_lastError = SaturnError::Ok;
	}
}
