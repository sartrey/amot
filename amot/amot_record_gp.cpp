#include "amot_record_gp.h"

namespace amot
{
	RecordGP::RecordGP()
	{
		Offset = 0;
		Size = 0;
		Next = null;
	}

	RecordGP::RecordGP(uint32 offset, uint32 size, RecordGP* next)
	{
		Offset = offset;
		Size = size;
		Next = next;
	}

	RecordGP::~RecordGP() { }

	RecordGP* RecordGP::NextZero(uint32 offset_max)
	{
		RecordGP* rec = this;
		while(rec != null) 
		{
			if (rec->Size == 0)
			{
				if(offset_max == 0 || rec->Offset < offset_max)
					return rec;
				return null;
			}
			rec = rec->Next;
		}
		return null;
	}

	RecordGP* RecordGP::NextNonzero()
	{
		RecordGP* rec = this;
		while(rec != null) 
		{
			if(rec->Size > 0)
				return rec;
			rec = rec->Next;
		}
		return null;
	}
}