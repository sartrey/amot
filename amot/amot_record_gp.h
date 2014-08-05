#pragma once

#include "amot_base.h"

namespace amot
{
	//memory record GP
	class RecordGP
	{
	public:
		uint32 Offset;
		uint32 Size;
		RecordGP* Next;

	public:
		RecordGP();
		RecordGP(uint32 offset, uint32 size, RecordGP* next = null);
		~RecordGP();

	public:
		//return first non-zero record from self
		RecordGP* NextNonzero();

		//return first zero rec from self
		//offset will less than offset_max if offset_max > 0
		RecordGP* NextZero(uint32 offset_max = 0);
	};

	typedef RecordGP* PRecordGP;
}