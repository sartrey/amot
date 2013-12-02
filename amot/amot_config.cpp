#include "stdafx.h"
#include "amot_config.h"

namespace amot
{
	Config::Config()
	{
		BLOCK_MAX_COUNT = 256;
		FL_MAX_COUNT = 16;
		BLOCK_LEVEL_DEFAULTMIN = 1;
		BLOCK_LEVEL_DEFAULTMAX = 11;
	}

	Config::~Config()
	{
	}
}