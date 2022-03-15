#pragma once

#include "SaturnEngine/Core.h"

namespace SaturnEngine
{
	/**
	 * Single-Frame memory allocator for Saturn Engine.
	 *
	 * Every frame allocates a specified number of bytes and clears this memory every frame.
	 */
	class SATURN_API FrameAllocator
	{
	public:
		FrameAllocator();
		~FrameAllocator();

		/**
		 * Allocates memory of the specified size.
		 *
		 * @param size the number of bytes to allocate
		 * @return pointer to allocated memory
		 */
		void* Alloc(I64 size);
		/**
		 * Clear the memory allocator
		 */
		void Clear();
		//Singleton instance getter function. Present in every manager.
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

#define ST_ALLOC(x) FrameAllocator::Get()->Alloc(x)
#define ST_ALLOC_ARRAY(x, size) FrameAllocator::Get()->Alloc((x) * (size))
