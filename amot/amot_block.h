#pragma once

#include "amot_base.h"

namespace amot
{
	//memory block
	class Block
	{
	public:
		Block(uint8 level, uint8 type);
		virtual ~Block();
	protected:
		uint8 _Type;
		uint8 _Level;
		object _Data;
		uint32 _Size;
	public:
		//test if address can be included in block
		bool Enclose(object data);

		//get pointer at specific offset from head
		object Offset(uint32 offset);

		//get count of object(s) at specific address in block
		//return 0 if object NOT existed in block
		virtual uint32 Count(object data, uint32 size) = 0;

		//get used size of block
		virtual uint32 UsedSize() = 0;

		//get free size of block
		virtual uint32 FreeSize() = 0;

		//allocate memory as specific length
		virtual object Alloc(uint32 len) = 0;

		//free specific object
		virtual void Free(object data, bool clear = false) = 0;

		//optimize block storage
		virtual void Optimize() = 0;
	};

	typedef Block* PtrBlock;
}