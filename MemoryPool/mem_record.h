#pragma once

#include "base.h"

class MemoryRecord;
typedef MemoryRecord* PMemRec;

class MemoryRecord
{
public:
	MemoryRecord(UINT offset,UINT length,PMemRec next = NULL);
	~MemoryRecord();
public:
	MemoryRecord* _Next;
	UINT _Offset;
	UINT _Length;
public:
	//return first non-zero rec
	//offset will less than offset_max if offset_max > 0
	static PMemRec FirstNonzero(PMemRec start, UINT offset_max = 0);

	//return first zero rec
	//offset will less than offset_max if offset_max > 0
	static PMemRec FirstZero(PMemRec start, UINT offset_max = 0);
};