#pragma once

//Memory Block Fixed Length

#include "mem_block.h"

namespace mempool
{
	class MemoryBlockFL : public MemoryBlock
	{
	public:
		MemoryBlockFL(UINT level = 1, UINT unit = 1);
		~MemoryBlockFL();
	private:
		UINT _Unit;
		UINT _TotalRec;
		BYTE* _Record;
	public:
		UINT GetUsedSize();
		UINT GetFreeSize();
		UINT GetObjectCount(LPVOID data, UINT size);
		LPVOID Alloc(UINT len = 1);
		bool Free(LPVOID data, bool clear = false);
		void Optimize();
	public:
		UINT GetUnit();
	};
}