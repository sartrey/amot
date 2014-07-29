#include "amot_block_gp1.h"

namespace amot
{
	BlockGP1::BlockGP1(uint8 level)
		: Block(level, 
		AMOT_ACTION_ALLOC | 
		AMOT_ACTION_FREE |
		AMOT_ACTION_RESIZE | 
		AMOT_ACTION_TRIM)
	{
		_Size = GetBlockVolume(level);
		_Data = new byte[_Size];
		memset(_Data, 0, _Size);
		_FirstRecord = null;
	}

	BlockGP1::~BlockGP1()
	{
		ClearRecord();
	}

	uint32 BlockGP1::UsedSize()
	{
		uint32 result = 0;
		PRecord rec = _FirstRecord;
		while(rec != null)
		{
			result += rec->Size;
			rec = rec->Next;
		}
		return result;
	}

	uint32 BlockGP1::FreeSize()
	{
		return _Size - UsedSize();
	}

	uint32 BlockGP1::Count(raw data, uint32 unit)
	{
		uint32 offset = (uint32)data - (uint32)_Data;
		PRecord rec = _FirstRecord;
		while (rec != null)
		{
			if (rec->Offset != offset)
				rec = rec->Next;
			else
			{
				uint32 count = rec->Size / unit;
				return count;
			}
		}
		return 0;
	}


	raw BlockGP1::Allocate(uint32 size)
	{
		if(size > _Size) 
			return null;
		PRecord rec;
		PRecord rec_zero;
		rec = _FirstRecord->NextNonzero();
		if(rec == null) //empty block
		{
			rec_zero = _FirstRecord->NextZero();
			if(rec_zero != null)
			{
				rec_zero->Offset = 0;
				rec_zero->Size = size;
				return _Data;
			}
			else
			{
				PRecord rec_new = new Record(0, size);
				_FirstRecord = rec_new;
				return _Data;
			}
		}
		else if(rec->Offset > 0 && size <= rec->Offset) //left space
		{
			rec_zero = _FirstRecord->NextZero(rec->Offset);
			if(rec_zero != null)
			{
				rec_zero->Offset = 0;
				rec_zero->Size = size;
				return _Data;
			}
			else
			{
				PRecord rec_new = new Record(0, size, rec);
				_FirstRecord = rec_new;
				return _Data;
			}
		}
		//gap space
		uint32 offset_end = rec->Offset + rec->Size;
		PRecord rec_next = rec->Next->NextNonzero();
		while(rec_next != null)
		{
			if(rec_next->Offset - offset_end >= size)
			{
				rec_zero = rec->Next->NextZero(rec_next->Offset);
				if(rec_zero != null)
				{
					rec_zero->Offset = offset_end;
					rec_zero->Size = size;
					return Offset(offset_end);
				}
				else
				{
					PRecord rec_new = new Record(offset_end, size, rec_next);
					rec->Next = rec_new;
					return Offset(offset_end);
				}
			}
			rec = rec_next;
			rec_next = rec->Next->NextNonzero();
			offset_end = rec->Offset + rec->Size;
		}
		//right space
		if(_Size - offset_end >= size)
		{
			rec_zero = rec->Next;
			if(rec_zero != null) //must be zero rec
			{
				rec_zero->Offset = offset_end;
				rec_zero->Size = size;
				return Offset(offset_end);
			}
			else
			{
				PRecord rec_new = new Record(offset_end, size);
				rec->Next = rec_new;
				return Offset(offset_end);
			}
		}
		return null;
	}

	void BlockGP1::Free(raw data, bool clear)
	{
		uint32 offset = (uint32)data - (uint32)_Data;
		PRecord rec = _FirstRecord;
		while(rec != null)
		{
			if(rec->Offset != offset) 
				rec = rec->Next;
			else
			{
				if(clear) 
					memset(data, 0, rec->Size);
				rec->Size = 0;
				break;
			}
		}
	}

	void BlockGP1::Optimize()
	{
		PRecord rec = _FirstRecord;
		PRecord rec_tmp = null;
		PRecord rec_last = null;
		_FirstRecord = _FirstRecord->NextNonzero();
		while(rec != null)
		{
			if(rec->Size == 0)
			{
				rec_tmp = rec->Next;
				if(rec_last != null)
					rec_last->Next = rec_tmp;
				delete rec;
				rec = rec_tmp;
			}
			else 
			{
				rec_last = rec;
				rec = rec->Next;
			}
		}
	}

	void BlockGP1::ClearRecord()
	{
		PRecord rec = _FirstRecord;
		while(rec != null)
		{
			PRecord next = rec->Next;
			delete rec;
			rec = next;
		}
	}
}