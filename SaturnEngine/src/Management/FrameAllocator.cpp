#include "Management/FrameAllocator.h"

#include <cassert>
#include "Management/LogManager.h"

namespace SaturnEngine
{
	FrameAllocator* FrameAllocator::s_instance = nullptr;

	FrameAllocator::FrameAllocator() : m_memoryPool(nullptr), m_stackTop(nullptr), m_stackSize(nullptr)
	{
		assert(!s_instance && "You can't create a second instance of FrameAllocator!");
		s_instance = this;
	}

	SaturnError FrameAllocator::StartUp()
	{
		m_memoryPool = new I8[1024];
		m_stackTop = m_memoryPool;
		m_stackSize = m_stackTop + 1024;

		ST_LOG_DEBUG("FrameManager initialized successfully");

		return SaturnError::Ok;
	}

	SaturnError FrameAllocator::ShutDown()
	{
		delete[] m_memoryPool;

		ST_LOG_DEBUG("FrameManager shut down successfully");

		return SaturnError::Ok;
	}

	FrameAllocator* FrameAllocator::Get()
	{
		return s_instance;
	}

	void* FrameAllocator::Alloc(I64 size)
	{
		if(m_stackTop + size > m_stackSize)
		{
			return nullptr;
		}

		I8* tmp = m_stackTop;
		m_stackTop += size;

		return tmp;
	}

	SaturnError FrameAllocator::Clear()
	{
		m_stackTop = m_memoryPool;

		return SaturnError::Ok;
	}
}
