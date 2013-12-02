#include "stdafx.h"

#include "mem_block_gp.h"
#include "mem_record.h"

#include <iostream>

namespace mempool
{
	using std::cout;
	using std::endl;

	MemoryBlockGP::MemoryBlockGP(UINT level)
		: MemoryBlock(level, MP_BCK_TYPE_GP)
	{
		_Size = GetMPBVol(level);
		_Data = new BYTE[_Size];
		memset(_Data, 0, _Size);
		_FirstRecord = NULL;
	}

	MemoryBlockGP::~MemoryBlockGP()
	{
		ClearRecord();
	}

	UINT MemoryBlockGP::GetUsedSize()
	{
		UINT result = 0;
		PMemRec rec = _FirstRecord;
		while(rec != NULL)
		{
			result += rec->_Length;
			rec = rec->_Next;
		}
		return result;
	}

	UINT MemoryBlockGP::GetFreeSize()
	{
		return _Size - GetUsedSize();
	}

	UINT MemoryBlockGP::GetObjectCount(LPVOID data, UINT size)
	{
		UINT offset = (UINT)data - (UINT)_Data;
		PMemRec rec = _FirstRecord;
		while(rec != NULL)
		{
			if(rec->_Offset != offset) rec = rec->_Next;
			else
			{
				UINT count = rec->_Length / size;
				return count;
			}
		}
		return 0;
	}

	LPVOID MemoryBlockGP::Alloc(UINT len)
	{
		if(len > _Size) return NULL;
		PMemRec rec;
		PMemRec rec_zero;
		rec = MemoryRecord::FirstNonzero(_FirstRecord);
		if(rec == NULL) //empty block
		{
			rec_zero = MemoryRecord::FirstZero(_FirstRecord);
			if(rec_zero != NULL)
			{
				rec_zero->_Offset = 0;
				rec_zero->_Length = len;
				return _Data;
			}
			else
			{
				PMemRec nrec = new MemoryRecord(0, len);
				_FirstRecord = nrec;
				return _Data;
			}
		}
		else if(rec->_Offset > 0 && len <= rec->_Offset) //left space
		{
			rec_zero = MemoryRecord::FirstZero(_FirstRecord, rec->_Offset);
			if(rec_zero != NULL)
			{
				rec_zero->_Offset = 0;
				rec_zero->_Length = len;
				return _Data;
			}
			else
			{
				PMemRec nrec = new MemoryRecord(0, len, rec);
				_FirstRecord = nrec;
				return _Data;
			}
		}
		//gap space
		UINT offset_end = rec->_Offset + rec->_Length;
		PMemRec rec_next = MemoryRecord::FirstNonzero(rec->_Next);
		while(rec_next != NULL)
		{
			if(rec_next->_Offset - offset_end >= len)
			{
				rec_zero = MemoryRecord::FirstZero(rec->_Next, rec_next->_Offset);
				if(rec_zero != NULL)
				{
					rec_zero->_Offset = offset_end;
					rec_zero->_Length = len;
					return GetOffsetData(offset_end);
				}
				else
				{
					PMemRec nrec = new MemoryRecord(offset_end, len, rec_next);
					rec->_Next = nrec;
					return GetOffsetData(offset_end);
				}
			}
			rec = rec_next;
			rec_next = MemoryRecord::FirstNonzero(rec->_Next);
			offset_end = rec->_Offset + rec->_Length;
		}
		//right space
		if(_Size - offset_end >= len)
		{
			rec_zero = rec->_Next;
			if(rec_zero != NULL) //must be zero rec
			{
				rec_zero->_Offset = offset_end;
				rec_zero->_Length = len;
				return GetOffsetData(offset_end);
			}
			else
			{
				PMemRec nrec = new MemoryRecord(offset_end, len);
				rec->_Next = nrec;
				return GetOffsetData(offset_end);
			}
		}
		return NULL;
	}

	bool MemoryBlockGP::Free(LPVOID data, bool clear)
	{
		UINT offset = (UINT)data - (UINT)_Data;
		PMemRec rec = _FirstRecord;
		while(rec != NULL)
		{
			if(rec->_Offset != offset) rec = rec->_Next;
			else
			{
				if(clear) memset(data, 0, rec->_Length);
				rec->_Length = 0;
				return true;
			}
		}
		return false;
	}

	void MemoryBlockGP::Optimize()
	{
		PMemRec rec = _FirstRecord;
		PMemRec rec_tmp = NULL;
		PMemRec rec_last = NULL;
		_FirstRecord = MemoryRecord::FirstNonzero(_FirstRecord);
		while(rec != NULL)
		{
			if(rec->_Length == 0)
			{
				rec_tmp = rec->_Next;
				if(rec_last != NULL) rec_last->_Next = rec_tmp;
				delete rec;
				rec = rec_tmp;
			}
			else 
			{
				rec_last = rec;
				rec = rec->_Next;
			}
		}
	}

	void MemoryBlockGP::ClearRecord()
	{
		PMemRec rec = _FirstRecord;
		while(rec != NULL)
		{
			PMemRec next = rec->_Next;
			delete rec;
			rec = next;
		}
	}
}