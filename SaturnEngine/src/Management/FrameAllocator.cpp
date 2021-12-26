#include "Management/FrameAllocator.h"

#include <cassert>
#include "Management/LogManager.h"
#include "Management/ErrorManager.h"

namespace SaturnEngine
{
	FrameAllocator* FrameAllocator::s_instance = nullptr;

	FrameAllocator::FrameAllocator() : m_memoryPool(nullptr), m_stackTop(nullptr), m_stackSize(nullptr)
	{
		assert(!s_instance && L"You can't create a second instance of FrameAllocator!");
		s_instance = this;
	}

	void FrameAllocator::StartUp()
	{
		m_memoryPool = new I8[1024];
		m_stackTop = m_memoryPool;
		m_stackSize = m_stackTop + 1024;

		ST_DEBUG(L"FrameManager initialized successfully");

		ST_CLEAR_ERROR();
	}

	void FrameAllocator::ShutDown()
	{
		delete[] m_memoryPool;

		ST_DEBUG(L"FrameManager shut down successfully");

		ST_CLEAR_ERROR();
	}

	FrameAllocator* FrameAllocator::Get()
	{
		return s_instance;
	}

	void* FrameAllocator::Alloc(I64 size)
	{
		if(m_stackTop + size > m_stackSize)
		{
			ST_THROW_ERROR(SaturnError::MemoryOverflow);

			return nullptr;
		}

		I8* tmp = m_stackTop;
		m_stackTop += size;

		return tmp;
	}

	void FrameAllocator::Clear()
	{
		m_stackTop = m_memoryPool;

		ST_CLEAR_ERROR();
	}
}
