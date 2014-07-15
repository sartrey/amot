#pragma once

#include "amot_base.h"

namespace amot
{
	//memory block
	class Block
	{
	protected:
		uint32 _Size;
		raw _Data;

	public:
		Block(uint8 level);
		virtual ~Block();

	public:
		//test if address can be included in block
		bool Enclose(raw data);

		//get pointer at specific offset from head
		raw Offset(uint32 offset);

		//get count of object(s) at specific address in block
		//return 0 if object NOT existed in block
		virtual uint32 Count(raw data, uint32 size) = 0;

		//get used size of block
		virtual uint32 UsedSize() = 0;

		//get free size of block
		virtual uint32 FreeSize() = 0;

		//allocate memory as specific length
		virtual raw Alloc(uint32 len) = 0;

		//free specific object
		virtual void Free(raw data, bool clear = false) = 0;

		//optimize block storage
		virtual void Optimize() = 0;
	};
}