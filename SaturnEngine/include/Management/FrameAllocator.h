#pragma once

#include "SaturnEngine/Core.h"
#include "SaturnEngine/Errors.h"

namespace SaturnEngine
{
	class SATURN_API FrameAllocator
	{
	public:
		FrameAllocator();
		~FrameAllocator() = default;

		SaturnError StartUp();
		SaturnError ShutDown();
		void* Alloc(size_t size);
		SaturnError Clear();
		static FrameAllocator* Get();

		FrameAllocator(const FrameAllocator& other) = default;
		FrameAllocator(FrameAllocator&& other) = default;

		FrameAllocator& operator=(const FrameAllocator& other) = default;
		FrameAllocator& operator=(FrameAllocator&& other) = default;

	private:
		int8_t* m_memoryPool;
		int8_t* m_stackTop;

		static FrameAllocator* s_instance;
	};
}

#define FrameAlloc(x) FrameAllocator::Get()->Alloc(x)
