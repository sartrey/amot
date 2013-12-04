#include "amot_record.h"

namespace amot
{
	Record::Record()
	{
		Offset = 0;
		Length = 0;
		Next = null;
	}

	Record::Record(uint32 offset, uint32 length, Record* next)
	{
		Offset = offset;
		Length = length;
		Next = next;
	}

	Record::~Record() { }

	Record* Record::NextZero(uint32 offset_max)
	{
		Record* rec = this;
		while(rec != null) 
		{
			if(rec->Length == 0)
			{
				if(offset_max == 0 || rec->Offset < offset_max)
					return rec;
				return null;
			}
			rec = rec->Next;
		}
		return null;
	}

	Record* Record::NextNonzero(uint32 offset_max)
	{
		Record* rec = this;
		while(rec != null) 
		{
			if(rec->Length > 0)
			{
				if(offset_max == 0 || rec->Offset < offset_max)
					return rec;
				return null;
			}
			rec = rec->Next;
		}
		return rec;
	}
}