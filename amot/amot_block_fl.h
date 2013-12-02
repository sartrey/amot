#pragma once

#include "amot_block.h"

namespace amot
{
	//memory block fixed length
	class BlockFL : public Block
	{
	public:
		BlockFL(uint8 level = 1, uint32 unit = 1);
		~BlockFL();
	private:
		uint32 _Unit;
		uint32 _TotalRec;
		byte* _Record;
	public:
		uint32 GetUsedSize();
		uint32 GetFreeSize();
		uint32 Count(object data, uint32 size);
		object Alloc(uint32 len = 1);
		bool Free(object data, bool clear = false);
		void Optimize();
	public:
		uint32 GetUnit();
	};
}