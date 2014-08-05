#pragma once

#include "amot_block.h"
#include "amot_record_gp.h"

namespace amot
{
	//block GP : linked list
	class BlockGP : public Block
	{
	private:
		PRecordGP _FirstRecord;

	public:
		BlockGP(uint8 level);
		~BlockGP();

	private:
		void ClearRecord();

	public:
		uint32 UsedSize();
		uint32 FreeSize();
		uint32 Count(raw data, uint32 unit);

		raw Allocate(uint32 size);
		void Free(raw data, bool clear = false);
		raw Resize(raw data, uint32 size);

		void Reset();
		void Optimize();
	};
}