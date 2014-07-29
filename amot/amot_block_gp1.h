#pragma once

#include "amot_block.h"
#include "amot_record.h"

namespace amot
{
	//block GP1 : linked list
	class BlockGP1 : public Block
	{
	private:
		PRecord _FirstRecord;

	public:
		BlockGP1(uint8 level);
		~BlockGP1();

	private:
		void ClearRecord();

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