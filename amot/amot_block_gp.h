#pragma once

#include "amot_block.h"
#include "amot_record.h"

namespace amot
{
	//memory block for general purpose
	class BlockGP : public Block
	{
	public:
		BlockGP(uint8 level);
		~BlockGP();
	private:
		PtrRecord _FirstRecord;
	public:
		uint32 GetUsedSize();
		uint32 GetFreeSize();
		uint32 Count(object data, uint32 size);
		object Alloc(uint32 len);
		bool Free(object data, bool clear = false);
		void Optimize();
	private:
		void ClearRecord();
	};
}