#pragma once

#include "amot_block.h"

namespace amot
{
	//block FL
	class BlockFL : public Block
	{
	private:
		uint32 _Unit;
		byte* _Record;
		uint32 _Total;

	public:
		BlockFL(uint8 level, uint32 unit);
		~BlockFL();

	public:
		uint32 UsedSize();
		uint32 FreeSize();
		uint32 Count(raw data, uint32 unit);

		raw Allocate(uint32 size);
		void Free(raw data, bool clear = false);
		//void Resize(raw data, uint32 size);
		//void Trim(raw data);

		void Optimize();
	};
}