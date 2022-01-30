#pragma once

#include "SaturnEngine/Core.h"

namespace SaturnEngine
{
	class SATURN_API FrameAllocator
	{
	public:
		FrameAllocator();
		~FrameAllocator() = default;

		void StartUp();
		void ShutDown();
		void* Alloc(I64 size);
		void Clear();
		static FrameAllocator* Get();

		FrameAllocator(const FrameAllocator& other) = default;
		FrameAllocator(FrameAllocator&& other) = default;

		FrameAllocator& operator=(const FrameAllocator& other) = default;
		FrameAllocator& operator=(FrameAllocator&& other) = default;

	private:
		I8* m_memoryPool;
		I8* m_stackTop;
		I8* m_stackLimit;

		static FrameAllocator* s_instance;
	};
}

#define ST_FRAME_ALLOC(x) FrameAllocator::Get()->Alloc(x)
#define ST_FRAME_ARRAY(x, size) FrameAllocator::Get()->Alloc((x) * (size))
