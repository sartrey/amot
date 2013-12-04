#include "amot_config.h"

namespace amot
{
	Config::Config()
	{
		_GP_BLOCK_COUNT_MAX = 200;
		_FL_BLOCK_COUNT_MAX = 20;
		_USER_BLOCK_LEVEL_MIN = 1;
		_USER_BLOCK_LEVEL_MAX = 11;
	}

	Config::~Config()
	{
	}
}