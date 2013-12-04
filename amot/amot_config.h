#pragma once
 
#include "amot_base.h"

namespace amot
{
	class Config
	{
	public:
		Config();
		~Config();
	private:
		//max GP block count
		uint32 _GP_BLOCK_COUNT_MAX;

		//max FL block count
		uint32 _FL_BLOCK_COUNT_MAX;

		//block level range
		uint8 _USER_BLOCK_LEVEL_MIN;
		uint8 _USER_BLOCK_LEVEL_MAX;
	public:
		inline uint32 Config::BLOCK_COUNT_MAX()
		{
			return _GP_BLOCK_COUNT_MAX + _FL_BLOCK_COUNT_MAX;
		}

		inline uint32 GP_BLOCK_COUNT_MAX() { return _GP_BLOCK_COUNT_MAX; };
		inline void GP_BLOCK_COUNT_MAX(uint32 value) 
		{
			_GP_BLOCK_COUNT_MAX = value;
			if(BLOCK_COUNT_MAX() > AMOT_BLOCK_COUNT_MAX)
				throw new invalid_argument(AMOT_ERR_1);
		};

		inline uint32 FL_BLOCK_COUNT_MAX() { return _FL_BLOCK_COUNT_MAX; };
		inline void FL_BLOCK_COUNT_MAX(uint32 value) 
		{
			_FL_BLOCK_COUNT_MAX = value;
			if(BLOCK_COUNT_MAX() > AMOT_BLOCK_COUNT_MAX)
				throw new invalid_argument(AMOT_ERR_1);
		};

		inline uint8 USER_BLOCK_LEVEL_MAX() { return _USER_BLOCK_LEVEL_MAX; };
		inline void USER_BLOCK_LEVEL_MAX(uint8 value) 
		{
			_USER_BLOCK_LEVEL_MAX = value;
		};

		inline uint8 USER_BLOCK_LEVEL_MIN() { return _USER_BLOCK_LEVEL_MIN; };
		inline void USER_BLOCK_LEVEL_MIN(uint8 value) 
		{
			_USER_BLOCK_LEVEL_MIN = value;
		};
	};

	typedef Config* PtrConfig;
}