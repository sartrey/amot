#pragma once

#include "amot_block.h"

namespace amot
{
	//block FL
	class BlockFL : public Block
	{
	private:
		uint32 _Unit;
		uint8* _Record;
		uint32 _RecordTotal;

	public:
		BlockFL(uint8 level);
		~BlockFL();

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