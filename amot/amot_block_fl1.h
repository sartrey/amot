#pragma once

#include "amot_block.h"
#include "amot_prop_fl.h"

namespace amot
{
	//block FL
	class BlockFL1 : public Block, public IBlockFL
	{
	private:
		uint32 _Unit;
		uint8* _Record;
		uint32 _RecordTotal;

	public:
		BlockFL1(uint8 level);
		~BlockFL1();

	public:
		void SetUnit(uint32 unit);

	public:
		uint32 UsedSize();
		uint32 FreeSize();
		uint32 Count(raw data, uint32 unit);

		raw Allocate(uint32 size);
		void Free(raw data, bool clear = false);
		//void Resize(raw data, uint32 size);
		//void Trim(raw data);

		void Reset();
		void Optimize();
	};
}