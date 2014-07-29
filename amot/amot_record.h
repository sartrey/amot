#pragma once

#include "amot_base.h"

namespace amot
{
	//memory record
	class Record
	{
	public:
		uint32 Offset;
		uint32 Size;
		Record* Next;

	public:
		Record();
		Record(uint32 offset, uint32 size, Record* next = null);
		~Record();

	public:
		//return first non-zero rec from self
		//offset will less than offset_max if offset_max > 0
		Record* NextNonzero(uint32 offset_max = 0);

		//return first zero rec from self
		//offset will less than offset_max if offset_max > 0
		Record* NextZero(uint32 offset_max = 0);
	};

	typedef Record* PRecord;
}