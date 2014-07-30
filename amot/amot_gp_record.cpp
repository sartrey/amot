#include "amot_gp_record.h"

namespace amot
{
	Record::Record()
	{
		Offset = 0;
		Size = 0;
		Next = null;
	}

	Record::Record(uint32 offset, uint32 size, Record* next)
	{
		Offset = offset;
		Size = size;
		Next = next;
	}

	Record::~Record() { }

	Record* Record::NextZero(uint32 offset_max)
	{
		Record* rec = this;
		while(rec != null) 
		{
			if(rec->Size == 0)
			{
				if(offset_max == 0 || rec->Offset < offset_max)
					return rec;
				return null;
			}
			rec = rec->Next;
		}
		return null;
	}

	Record* Record::NextNonzero()
	{
		Record* rec = this;
		while(rec != null) 
		{
			if(rec->Size > 0)
				return rec;
			rec = rec->Next;
		}
		return null;
	}
}