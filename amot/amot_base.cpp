#include "amot_base.h"

namespace amot
{
	void ValidBlockLevel(uint8 level)
	{
		if(level < AMOT_BLOCK_LEVEL_MIN 
		|| level > AMOT_BLOCK_LEVEL_MAX)
		{
			throw AMOT_ERROR_LEVEL;
		}
	}

	uint32 GetBlockVolume(uint8 level)
	{
		ValidBlockLevel(level);
		uint32 result = (uint32)(pow(4.0f, level - 1)) * 1024;
		return result;
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
		if(lvl > AMOT_BLOCK_LEVEL_MAX) 
			return 0;
		return lvl;
	}

	Lock::Lock()
	{
		_Core = (uint64*)_aligned_malloc(1, sizeof(uint64));
		InterlockedExchange(_Core, FALSE);
	}

	Lock::~Lock()
	{
		InterlockedExchange(_Core, FALSE);
		_aligned_free(_Core);
	}

	void Lock::Enter()
	{
		while (InterlockedExchange(_Core, TRUE) == TRUE)
			Sleep(0);
	}

	void Lock::Leave()
	{
		InterlockedExchange(_Core, FALSE);
	}
}