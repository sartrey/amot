#include "amot_factory.h"
#include "amot_block_gp.h"
#include "amot_block_fl.h"

namespace amot
{
	Factory::Factory()
	{
	}

	Factory::~Factory()
	{
	}

	PBlock Factory::CreateBlock(int type, uint32 size)
	{
		PBlock block = null;
		if (type == AMOT_BLOCK_GP)
		{
			uint8 level = GetMinBlockLevel(size);
			block = new BlockGP(level);
		}
		else if (type == AMOT_BLOCK_FL)
		{
			uint8 level = GetMinBlockLevel(size * 1024);
			BlockFL* block_fl = new BlockFL(level);
			block_fl->SetUnit(size);
			block = block_fl;
		}
		block->Reset();
		return block;
	}
}