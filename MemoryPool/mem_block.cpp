#include "stdafx.h"
#include "mem_block.h"

namespace mempool
{
	MemoryBlock::MemoryBlock(UINT level,UINT type)
	{
		_Type = type;
		_Level = level;
	}

	MemoryBlock::~MemoryBlock()
	{
		if(_Data != NULL) delete [] _Data;
	}

	bool MemoryBlock::CanContain(LPVOID data)
	{
		UINT d1 = (UINT)_Data;
		UINT d2 = (UINT)data;
		if(d2 < d1) return false;
		if(d2 >= d1 + _Size) return false;
		return true;
	}
}