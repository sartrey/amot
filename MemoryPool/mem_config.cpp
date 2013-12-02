#include "stdafx.h"
#include "mem_config.h"

MemoryConfig::MemoryConfig()
{
	MP_BCK_COUNT_MAX = 256;
	MP_FL_COUNT_MAX = 16;
	MP_BCK_LEVEL_DEFAULTMIN = 1;
	MP_BCK_LEVEL_DEFAULTMAX = 11;
}

MemoryConfig::~MemoryConfig(){}