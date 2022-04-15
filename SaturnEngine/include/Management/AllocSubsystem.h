#pragma once

#include "SaturnEngine/Core.h"

namespace SaturnEngine
{
	/**
	 * Single-Frame memory allocator for Saturn Engine.
	 *
	 * Every frame allocates a specified number of bytes and clears this memory every frame.
	 */
	class SATURN_API AllocSubsystem
	{
	public:
		AllocSubsystem();
		AllocSubsystem(const AllocSubsystem& other) = delete;
		AllocSubsystem(AllocSubsystem&& other) = delete;
		~AllocSubsystem();

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

		//Singleton instance getter function. Present in every subsystem.
		static AllocSubsystem* Get();

		AllocSubsystem& operator=(const AllocSubsystem& other) = delete;
		AllocSubsystem& operator=(AllocSubsystem&& other) = delete;

	private:
		I8* m_memoryPool;
		I8* m_stackTop;
		I8* m_stackLimit;

		static AllocSubsystem* s_instance;
	};
}

#define ST_ALLOC(x) FrameAllocator::Get()->Alloc(x)
#define ST_ALLOC_ARRAY(x, size) FrameAllocator::Get()->Alloc((x) * (size))
