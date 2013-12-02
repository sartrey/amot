#include "stdafx.h"
#include "amot_base.h"

namespace amot
{
	uint32 GetMaxBlockVol(uint8 level)
	{
		if(level < 1 || level > AMOT_BLOCK_LEVEL_MAX)
		{
			throw new invalid_argument("invalid memory block level");
		}
		uint32 result = (uint32)(pow(4.0f, level - 1)) * 1024;
		return result;
	}

	uint32 GetMaxBlockVol(uint8 level, uint32 unit)
	{
		if(level < 1 || level > AMOT_BLOCK_LEVEL_MAX)
		{
			throw new invalid_argument("invalid memory block level");
		}
		uint32 size = (uint32)(pow(4.0f, level - 1)) * 1024;
		uint32 count = size / unit;
		count = count - count % 8;
		return count;
	}

	uint8 GetMinBlockLevel(uint32 size)
	{
		uint32 lvl = 1;
		uint32 size_max = 1024;
		while(size_max < size)
		{
			size_max *= 4;
			++lvl;
		}
		if(lvl > AMOT_BLOCK_LEVEL_MAX) return 0;
		return lvl;
	}
}