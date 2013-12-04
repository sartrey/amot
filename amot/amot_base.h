#pragma once

#include "amot_const.h"

namespace amot
{
	//block count max
	#define AMOT_BLOCK_COUNT_MAX 1048576

	//block size = [1K,1G]BYTES
	#define AMOT_BLOCK_SIZE_MIN 1024
	#define AMOT_BLOCK_SIZE_MAX 1073741824

	//block level = [1,11]
	#define AMOT_BLOCK_LEVEL_MIN 1
	#define AMOT_BLOCK_LEVEL_MAX 11

	//block type
	#define AMOT_BLOCK_TYPE_GP 0 //General Purpose
	#define AMOT_BLOCK_TYPE_FL 1 //Fixed Length

	const cstr AMOT_ERR_0 = "invalid memory block level";
	const cstr AMOT_ERR_1 = "too many memory blocks";
	const cstr AMOT_ERR_2 = "incredible error"; //just a joke

	AMOT_API void AssertBlockLevel(uint8 level);

	//get block size at specific level
	AMOT_API uint32 GetBlockVol(uint8 level);

	//get block count for unit at specific level
	AMOT_API uint32 GetBlockVol(uint8 level, uint32 unit);

	//get min block level for size
	AMOT_API uint8 GetMinBlockLevel(uint32 size);

	//interface: disposable object
	class AMOT_API IDisposable
	{
	public:
		//default <destructor>
		virtual bool Dispose() = 0;
	};
}