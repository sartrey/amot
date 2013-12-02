#pragma once

//Memory Block General Purpose

#include "mem_block.h"
#include "mem_record.h"

namespace mempool
{
	class MemoryBlockGP : public MemoryBlock
	{
	public:
		MemoryBlockGP(UINT level);
		~MemoryBlockGP();
	private:
		MemoryRecord* _FirstRecord;
	public:
		UINT GetUsedSize();
		UINT GetFreeSize();
		UINT GetObjectCount(LPVOID data, UINT size);
		LPVOID Alloc(UINT len);
		bool Free(LPVOID data, bool clear = false);
		void Optimize();
	private:
		void ClearRecord();
	};
}