#include "Management/ErrorSubsystem.h"

#include "Management/LogSubsystem.h"

namespace SaturnEngine
{
	ErrorSubsystem* ErrorSubsystem::s_instance = nullptr;

	ErrorSubsystem::ErrorSubsystem() : m_lastError(SaturnError::Ok)
	{
		assert(!s_instance && L"You can't create a second instance of ErrorManager!");
		s_instance = this;
	}

	ErrorSubsystem::~ErrorSubsystem()
	{
		m_lastError = SaturnError::Ok;
	}

	ErrorSubsystem* ErrorSubsystem::Get()
	{
		return s_instance;
	}

	SaturnError ErrorSubsystem::GetError()
	{
		return m_lastError;
	}

	void ErrorSubsystem::SetError(SaturnError error, const char* fileName, I32 lineNumber)
	{
#ifdef ST_BUILD_DEBUG
		ST_ERROR("Error {0} was thrown in {1}: {2}", error, fileName, lineNumber);
#endif

		m_lastError = error;
	}

	void ErrorSubsystem::ClearError()
	{
		m_lastError = SaturnError::Ok;
	}
}
