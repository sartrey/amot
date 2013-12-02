#pragma once
 
class MemoryConfig
{
public:
	MemoryConfig();
	~MemoryConfig();
public:
	//Memory Block Max Count
	UINT MP_BCK_COUNT_MAX;

	//Fix Length Max Count
	//Must < MP_BCK_COUNT_MAX
	UINT MP_FL_COUNT_MAX;

	//Memory Block Level Range
	BYTE MP_BCK_LEVEL_DEFAULTMIN;
	BYTE MP_BCK_LEVEL_DEFAULTMAX;
};

typedef MemoryConfig* PMemCfg;