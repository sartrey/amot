#include "stdafx.h"

#include "amot_block_gp.h"
#include "amot_record.h"

namespace amot
{
	BlockGP::BlockGP(uint8 level)
		: Block(level, AMOT_BLOCK_TYPE_GP)
	{
		_Size = GetMaxBlockVol(level);
		_Data = new byte[_Size];
		memset(_Data, 0, _Size);
		_FirstRecord = null;
	}

	BlockGP::~BlockGP()
	{
		ClearRecord();
	}

	uint32 BlockGP::GetUsedSize()
	{
		uint32 result = 0;
		PtrRecord rec = _FirstRecord;
		while(rec != null)
		{
			result += rec->Length();
			rec = rec->Next();
		}
		return result;
	}

	uint32 BlockGP::GetFreeSize()
	{
		return _Size - GetUsedSize();
	}

	uint32 BlockGP::Count(object data, uint32 size)
	{
		uint32 offset = (uint32)data - (uint32)_Data;
		PtrRecord rec = _FirstRecord;
		while(rec != null)
		{
			if(rec->Offset() != offset)
				rec = rec->Next();
			else
			{
				uint32 count = rec->Length() / size;
				return count;
			}
		}
		return 0;
	}

	object BlockGP::Alloc(uint32 len)
	{
		if(len > _Size) return null;
		PtrRecord rec;
		PtrRecord rec_zero;
		rec = _FirstRecord->NextNonzero();
		if(rec == null) //empty block
		{
			rec_zero = _FirstRecord->NextZero();
			if(rec_zero != null)
			{
				rec_zero->Offset(0);
				rec_zero->Length(len);
				return _Data;
			}
			else
			{
				PtrRecord rec_new = new Record(0, len);
				_FirstRecord = rec_new;
				return _Data;
			}
		}
		else if(rec->Offset() > 0 && len <= rec->Offset()) //left space
		{
			rec_zero = _FirstRecord->NextZero(rec->Offset());
			if(rec_zero != null)
			{
				rec_zero->Offset(0);
				rec_zero->Length(len);
				return _Data;
			}
			else
			{
				PtrRecord rec_new = new Record(0, len, rec);
				_FirstRecord = rec_new;
				return _Data;
			}
		}
		//gap space
		uint32 offset_end = rec->Offset() + rec->Length();
		PtrRecord rec_next = rec->Next()->NextNonzero();
		while(rec_next != null)
		{
			if(rec_next->Offset() - offset_end >= len)
			{
				rec_zero = rec->Next()->NextZero(rec_next->Offset());
				if(rec_zero != null)
				{
					rec_zero->Offset(offset_end);
					rec_zero->Length(len);
					return Offset(offset_end);
				}
				else
				{
					PtrRecord rec_new = new Record(offset_end, len, rec_next);
					rec->Next(rec_new);
					return Offset(offset_end);
				}
			}
			rec = rec_next;
			rec_next = rec->Next()->NextNonzero();
			offset_end = rec->Offset() + rec->Length();
		}
		//right space
		if(_Size - offset_end >= len)
		{
			rec_zero = rec->Next();
			if(rec_zero != null) //must be zero rec
			{
				rec_zero->Offset(offset_end);
				rec_zero->Length(len);
				return Offset(offset_end);
			}
			else
			{
				PtrRecord rec_new = new Record(offset_end, len);
				rec->Next(rec_new);
				return Offset(offset_end);
			}
		}
		return null;
	}

	bool BlockGP::Free(object data, bool clear)
	{
		uint32 offset = (uint32)data - (uint32)_Data;
		PtrRecord rec = _FirstRecord;
		while(rec != null)
		{
			if(rec->Offset() != offset) 
				rec = rec->Next();
			else
			{
				if(clear) 
					memset(data, 0, rec->Length());
				rec->Length(0);
				return true;
			}
		}
		return false;
	}

	void BlockGP::Optimize()
	{
		PtrRecord rec = _FirstRecord;
		PtrRecord rec_tmp = null;
		PtrRecord rec_last = null;
		_FirstRecord = _FirstRecord->NextNonzero();
		while(rec != null)
		{
			if(rec->Length() == 0)
			{
				rec_tmp = rec->Next();
				if(rec_last != null)
					rec_last->Next(rec_tmp);
				delete rec;
				rec = rec_tmp;
			}
			else 
			{
				rec_last = rec;
				rec = rec->Next();
			}
		}
	}

	void BlockGP::ClearRecord()
	{
		PtrRecord rec = _FirstRecord;
		while(rec != null)
		{
			PtrRecord next = rec->Next();
			delete rec;
			rec = next;
		}
	}
}