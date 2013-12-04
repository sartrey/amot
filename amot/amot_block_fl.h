#pragma once

#include "amot_block.h"

namespace amot
{
	//memory block fixed length
	class BlockFL : public Block
	{
	public:
		BlockFL(uint8 level, uint32 unit);
		~BlockFL();
	private:
		uint32 _Unit;
		uint32 _TotalRec;
		byte* _Record;
	public:
		uint32 UsedSize();
		uint32 FreeSize();
		uint32 Count(object data, uint32 size);
		object Alloc(uint32 len = 1);
		void Free(object data, bool clear);
		void Optimize();
	public:
		inline uint32 Unit() { return _Unit; }
	};
}