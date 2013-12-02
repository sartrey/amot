#pragma once

#include "amot_base.h"

namespace amot
{
	//memory record
	class Record
	{
	public:
		Record();
		Record(uint32 offset, uint32 length, Record* next = null);
		~Record();
	private:
		Record* _Next;
		uint32 _Offset;
		uint32 _Length;
	public:
		//getter: next
		inline Record* Next() 
		{
			return _Next; 
		}

		//setter: next
		inline void Next(Record* value)
		{
			_Next = value;
		}
		
		//getter: offset
		inline uint32 Offset()
		{
			return _Offset;
		}

		//setter: offset
		inline void Offset(uint32 value)
		{
			_Offset = value;
		}

		//getter: length
		inline uint32 Length()
		{
			return _Length;
		}

		//setter: length
		inline void Length(uint32 value)
		{
			_Length = value;
		}
	public:
		//return first non-zero rec
		//offset will less than offset_max if offset_max > 0
		Record* NextNonzero(uint32 offset_max = 0);

		//return first zero rec
		//offset will less than offset_max if offset_max > 0
		Record* NextZero(uint32 offset_max = 0);
	};

	typedef Record* PtrRecord;
}