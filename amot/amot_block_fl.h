#pragma once

#include "amot_block.h"

namespace amot
{
	//memory block fixed length
	class BlockFL : public Block
	{
	private:
		uint32 _Unit;
		uint32 _TotalRec;
		byte* _Record;

	public:
		BlockFL(uint8 level, uint32 unit);
		~BlockFL();

	public:
		inline uint32 Unit() { return _Unit; }
	};
}