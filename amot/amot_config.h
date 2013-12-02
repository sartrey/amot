#pragma once
 
#include "amot_const.h"

namespace amot
{
	class Config
	{
	public:
		Config();
		~Config();
	public:
		//memory block max count
		uint32 BLOCK_MAX_COUNT;

		//fix length max count
		//Must < MP_BCK_COUNT_MAX
		uint32 FL_MAX_COUNT;

		//Memory Block Level Range
		byte BLOCK_LEVEL_DEFAULTMIN;
		byte BLOCK_LEVEL_DEFAULTMAX;
	};

	typedef Config* PtrConfig;
}
