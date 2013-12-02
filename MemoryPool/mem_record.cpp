#include "stdafx.h"
#include "mem_record.h"

MemoryRecord::MemoryRecord(UINT offset,UINT length,MemoryRecord* next)
{
	_Offset = offset;
	_Length = length;
	_Next = next;
}

MemoryRecord::~MemoryRecord() { }

PMemRec MemoryRecord::FirstZero(PMemRec start, UINT offset_max)
{
	PMemRec rec = start;
	while(rec != NULL) 
	{
		if(rec->_Length == 0)
		{
			if(offset_max == 0 || rec->_Offset < offset_max) return rec;
			return NULL;
		}
		rec = rec->_Next;
	}
	return NULL;
}

PMemRec MemoryRecord::FirstNonzero(PMemRec start, UINT offset_max)
{
	PMemRec rec = start;
	while(rec != NULL) 
	{
		if(rec->_Length > 0)
		{
			if(offset_max == 0 || rec->_Offset < offset_max) return rec;
			return NULL;
		}
		rec = rec->_Next;
	}
	return rec;
}