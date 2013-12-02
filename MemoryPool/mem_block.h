#pragma once

#include "base.h"

namespace mempool
{
	//Memory block base class
	class MemoryBlock
	{
	public:
		MemoryBlock(UINT level,UINT type);
		virtual ~MemoryBlock();
	protected:
		UINT _Type;
		UINT _Level;
		LPVOID _Data;
		UINT _Size;
	public:
		//Test if MPB contains data address
		bool CanContain(LPVOID data);

		LPVOID GetOffsetData(UINT offset)
		{
			return (LPVOID)((UINT)_Data + offset);
		}

		//Get count of object(s) from MPB
		//return 0 if NOT existed in MPB
		virtual UINT GetObjectCount(LPVOID data, UINT size) = 0;

		//Get MPB used size
		virtual UINT GetUsedSize() = 0;

		//Get MPB free size
		virtual UINT GetFreeSize() = 0;

		//Allocate mem by specific len
		virtual LPVOID Alloc(UINT len) = 0;

		//Free specific object
		virtual bool Free(LPVOID data, bool clear = false) = 0;

		//Optimize MPB storage
		virtual void Optimize() = 0;
	};
}