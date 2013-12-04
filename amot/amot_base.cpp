#include "amot_base.h"

namespace amot
{
	void AssertBlockLevel(uint8 level)
	{
		if(level < AMOT_BLOCK_LEVEL_MIN 
		|| level > AMOT_BLOCK_LEVEL_MAX)
		{
			throw new invalid_argument(AMOT_ERR_0);
		}
	}

	uint32 GetBlockVol(uint8 level)
	{
		AssertBlockLevel(level);
		uint32 result = (uint32)(pow(4.0f, level - 1)) * 1024;
		return result;
	}

	uint32 GetBlockVol(uint8 level, uint32 unit)
	{
		AssertBlockLevel(level);
		uint32 size = (uint32)(pow(4.0f, level - 1)) * 1024;
		uint32 count = size / unit;
		count = count - count % 8;
		return count;
	}

	uint8 GetMinBlockLevel(uint32 size)
	{
		uint8 lvl = AMOT_BLOCK_LEVEL_MIN;
		uint32 real_size = AMOT_BLOCK_SIZE_MIN;
		while(real_size < size)
		{
			real_size *= 4;
			++lvl;
		}
		if(lvl > AMOT_BLOCK_LEVEL_MAX) return 0;
		return lvl;
	}
}