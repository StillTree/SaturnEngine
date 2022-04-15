#include "Management/AllocSubsystem.h"

#include "Management/LogSubsystem.h"
#include "Management/ErrorSubsystem.h"
#include "Management/ConfigSubsystem.h"

namespace SaturnEngine
{
	AllocSubsystem* AllocSubsystem::s_instance = nullptr;

	AllocSubsystem::AllocSubsystem()
		: m_memoryPool(nullptr), m_stackTop(nullptr), m_stackLimit(nullptr)
	{
		ST_ASSERT(!s_instance, L"You can't create a second instance of AllocSubsystem!")
		s_instance = this;
		I32 allocationSize = CONFIG_REQUEST_INT32(L"singleFrameMemoryPoolSize", 1024);

		m_memoryPool = new I8[allocationSize];
		m_stackTop = m_memoryPool;
		m_stackLimit = m_stackTop + allocationSize;

		ST_DEBUG(L"AllocSubsystem initialized successfully");
	}

	AllocSubsystem::~AllocSubsystem()
	{
		delete[] m_memoryPool;

		ST_DEBUG(L"AllocSubsystem shut down successfully");
	}

	AllocSubsystem* AllocSubsystem::Get()
	{
		return s_instance;
	}

	void* AllocSubsystem::Alloc(I64 size)
	{
		if(m_stackTop + size > m_stackLimit)
		{
			ST_THROW_ERROR(SaturnError::MemoryOverflow);

			return nullptr;
		}

		I8* tmp = m_stackTop;
		m_stackTop += size;

		ST_CLEAR_ERROR();
		return tmp;
	}

	void AllocSubsystem::Clear()
	{
		m_stackTop = m_memoryPool;
	}
}
