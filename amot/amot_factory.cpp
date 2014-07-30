#include "amot_factory.h"
#include "amot_block_gp1.h"
#include "amot_block_fl1.h"

namespace amot
{
	Factory::Factory()
	{
	}

	Factory::~Factory()
	{
	}

	PBlock Factory::CreateBlock(int type, uint8 level)
	{
		Block* block = null;
		if (type == AMOT_BLOCK_GP1)
			block = new BlockGP1(level);
		else if (type == AMOT_BLOCK_FL)
			block = new BlockFL1(level);
		return block;
	}
}