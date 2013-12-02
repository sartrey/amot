#pragma once

#include "amot_const.h"

namespace amot
{
	//max block size = 1GB
	#define AMOT_BLOCK_SIZE_MAX 1073741824

	//max block level = 11
	#define AMOT_BLOCK_LEVEL_MAX 11

	//block type
	#define AMOT_BLOCK_TYPE_GP 0 //General Purpose
	#define AMOT_BLOCK_TYPE_FL 1 //Fixed Length

	//get specific block max size
	uint32 GetMaxBlockVol(uint8 level);

	//get specific block max count for unit
	uint32 GetMaxBlockVol(uint8 level, uint32 unit);

	//get min block level for size
	uint8 GetMinBlockLevel(uint32 size);

	//interface: disposable object
	class IDisposable
	{
	public:
		//default <destructor>
		virtual bool Dispose() = 0;
	};
}