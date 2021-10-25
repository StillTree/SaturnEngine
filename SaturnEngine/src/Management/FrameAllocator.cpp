#include "Management/FrameAllocator.h"

#include <cassert>
#include "Management/LogManager.h"

namespace SaturnEngine
{
	FrameAllocator* FrameAllocator::s_instance = nullptr;

	FrameAllocator::FrameAllocator()
		: m_memoryPool(nullptr), m_stackTop(nullptr)
	{
		assert(!s_instance && "You can't create a second instance of FrameAllocator!");
		s_instance = this;
	}

	SaturnError FrameAllocator::StartUp()
	{
		m_memoryPool = new int8_t[1024];
		m_stackTop = m_memoryPool;

		ST_LOG_DEBUG("FrameManager initialized successfully");

		return SaturnError::Ok;
	}

	SaturnError FrameAllocator::ShutDown()
	{
		delete[] m_memoryPool;

		ST_LOG_DEBUG("FrameManager shut down successfully");

		return SaturnError::Ok;
	}

	FrameAllocator *FrameAllocator::Get()
	{
		return s_instance;
	}

	void *FrameAllocator::Alloc(size_t size)
	{
		int8_t* tmp = m_stackTop;
		m_stackTop += size;

		return tmp;
	}

	SaturnError FrameAllocator::Clear()
	{
		m_stackTop = m_memoryPool;

		return SaturnError::Ok;
	}
}
