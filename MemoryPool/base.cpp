#include "stdafx.h"
#include "base.h"
#include <cmath>
#include <stdexcept>

namespace mempool
{
	using std::exception;

	UINT GetMPBVol(UINT level)
	{
		if(level < 1 || level > MP_BCK_LEVEL_MAX)
		{
			throw new exception("invalid MPB level");
		}
		UINT result = (UINT)(pow(4,level-1)) * 1024;
		return result;
	}

	UINT GetMPBVol(UINT level, UINT unit)
	{
		if(level < 1 || level > MP_BCK_LEVEL_MAX)
		{
			throw new exception("invalid MPB level");
		}
		UINT size = (UINT)(pow(4,level-1)) * 1024;
		UINT count = size / unit;
		count = count - count % 8;
		return count;
	}

	UINT GetMPBLevel(UINT size)
	{
		UINT lvl = 1;
		UINT size_max = 1024;
		while(size_max < size)
		{
			size_max *= 4;
			++lvl;
		}
		if(lvl > MP_BCK_LEVEL_MAX) return 0;
		return lvl;
	}
}