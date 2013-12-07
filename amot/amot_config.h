#pragma once
 
#include "amot_base.h"

namespace amot
{
	class Config
	{
	public:
		Config();
		~Config();
	public:
		//max GP block count
		uint32 GP_BLOCK_COUNT_MAX;

		//max FL block count
		uint32 FL_BLOCK_COUNT_MAX;

		//max block count
		uint32 BLOCK_COUNT_MAX;

		//block level range
		uint8 USER_BLOCK_LEVEL_MIN;
		uint8 USER_BLOCK_LEVEL_MAX;
	public:
		void Update();
	};

	typedef Config* PtrConfig;
}