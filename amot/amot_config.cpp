#include "amot_config.h"

namespace amot
{
	Config::Config()
	{
		GP_BLOCK_COUNT_MAX = 200;
		FL_BLOCK_COUNT_MAX = 20;
		BLOCK_COUNT_MAX = GP_BLOCK_COUNT_MAX + FL_BLOCK_COUNT_MAX;
		USER_BLOCK_LEVEL_MIN = 1;
		USER_BLOCK_LEVEL_MAX = 11;
	}

	Config::~Config()
	{
	}

	void Config::Update()
	{
		BLOCK_COUNT_MAX = GP_BLOCK_COUNT_MAX + FL_BLOCK_COUNT_MAX;
		if(BLOCK_COUNT_MAX > AMOT_BLOCK_COUNT_MAX)
			throw new invalid_argument(AMOT_ERR_1);
	}
}