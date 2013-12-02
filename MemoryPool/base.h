#pragma once

#include <Windows.h>

namespace mempool
{
	//Memory Block Max Size 1GB
	#define MP_BCK_SIZE_MAX 1073741824

	//Memory Block Max Level 11
	#define MP_BCK_LEVEL_MAX 11

	//Memory Block Type
	#define MP_BCK_TYPE_GP 0 //General Purpose
	#define MP_BCK_TYPE_FL 1 //Fixed Length

	//Get Memory Block Max Size
	UINT GetMPBVol(UINT level);

	//Get Memory Block Max Unit Count
	UINT GetMPBVol(UINT level, UINT unit);

	//Get Memory Block Min Level
	UINT GetMPBLevel(UINT size);

	//Disposable object interface
	class IDisposable
	{
	public:
		//Default <Destroy>
		virtual bool Dispose() = 0;
	};
}