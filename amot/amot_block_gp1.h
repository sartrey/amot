#pragma once

#include "amot_block.h"
#include "amot_record.h"

namespace amot
{
	//block GP1 : chain table
	class BlockGP1 : public Block
	{
	private:
		PRecord _FirstRecord;

	public:
		BlockGP1(uint8 level);
		~BlockGP1();

	private:
		void ClearRecord();
	};
}