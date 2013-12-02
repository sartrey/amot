#include "stdafx.h"
#include "amot_record.h"

namespace amot
{
	Record::Record()
	{
		_Offset = 0;
		_Length = 0;
		_Next = null;
	}

	Record::Record(uint32 offset, uint32 length, Record* next)
	{
		_Offset = offset;
		_Length = length;
		_Next = next;
	}

	Record::~Record() { }

	Record* Record::NextZero(uint32 offset_max)
	{
		Record* rec = this;
		while(rec != null) 
		{
			if(rec->_Length == 0)
			{
				if(offset_max == 0 || rec->_Offset < offset_max)
					return rec;
				return null;
			}
			rec = rec->_Next;
		}
		return null;
	}

	Record* Record::NextNonzero(uint32 offset_max)
	{
		Record* rec = this;
		while(rec != null) 
		{
			if(rec->_Length > 0)
			{
				if(offset_max == 0 || rec->_Offset < offset_max)
					return rec;
				return null;
			}
			rec = rec->_Next;
		}
		return rec;
	}
}