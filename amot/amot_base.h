#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "windows.h" //#IFDEF

#ifdef AMOT_EXPORTS
	#define AMOT_API __declspec(dllexport)
#else
	#define AMOT_API __declspec(dllimport)
#endif

namespace amot
{
	#define null 0

	//define type
	typedef void* raw;
	typedef unsigned char byte;
	typedef char int8;
	typedef short int16;
	typedef int int32;
	typedef long long int64;
	typedef unsigned char uint8;
	typedef unsigned short uint16;
	typedef unsigned int uint32;
	typedef unsigned long long uint64;
	typedef float real32;
	typedef double real64;

	//block count max
	#define AMOT_BLOCK_COUNT_MAX 1048576

	//block size = [1K,1G]BYTES
	#define AMOT_BLOCK_SIZE_MIN 1024
	#define AMOT_BLOCK_SIZE_MAX 1073741824

	//block level = [1,11]
	#define AMOT_BLOCK_LEVEL_MIN 1
	#define AMOT_BLOCK_LEVEL_MAX 11

	enum BlockEnum
	{
		AMOT_BLOCK_GP1 = 0,
		AMOT_BLOCK_GP2 = 1,
		AMOT_BLOCK_FL = 2
	};

	enum ActionEnum
	{
		AMOT_ACTION_ALLOC = 1,
		AMOT_ACTION_FREE = 2,
		AMOT_ACTION_RESIZE = 4,
		AMOT_ACTION_TRIM = 8
	};

	const int amot_err1 = 1000; //unknown
	const int amot_err2 = 1001; //not implemented
	const int amot_err3 = 1002; //invalid level
	const int amot_err4 = 1003; //too many blocks

	//interface: disposable object
	class AMOT_API IDisposable
	{
	public:
		//default <destructor>
		virtual bool Dispose() = 0;
	};

	//valid block level
	void ValidBlockLevel(uint8 level);

	//get block size at specific level
	uint32 GetBlockVolume(uint8 level);

	//get min block level for size
	uint8 GetMinBlockLevel(uint32 size);

	//spin lock
	class Lock
	{
	private:
		//TRUE - Lock , FALSE - Unlock
		uint64* _Core;

	public:
		Lock();
		~Lock();

	public:
		//capture lock
		void Enter();

		//release lock
		void Leave();
	};
}