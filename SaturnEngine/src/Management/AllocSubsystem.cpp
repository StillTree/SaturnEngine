#include "Management/AllocSubsystem.h"

#include "Management/LogSubsystem.h"
#include "Management/ErrorSubsystem.h"

namespace SaturnEngine
{
	AllocSubsystem* AllocSubsystem::s_instance = nullptr;

	AllocSubsystem::AllocSubsystem() : m_memoryPool(nullptr), m_stackTop(nullptr), m_stackLimit(nullptr)
	{
		assert(!s_instance && L"You can't create a second instance of FrameAllocator!");
		s_instance = this;

		m_memoryPool = new I8[1024];
		m_stackTop = m_memoryPool;
		m_stackLimit = m_stackTop + 1024;

		ST_DEBUG(L"FrameAllocator initialized successfully");
	}

	AllocSubsystem::~AllocSubsystem()
	{
		delete[] m_memoryPool;

		ST_DEBUG(L"FrameAllocator shut down successfully");
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
