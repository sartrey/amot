#pragma once

#include "amot_base.h"

namespace amot
{
	//{base} memory block
	class AMOT_API Block
	{
	protected:
		uint32 _Support;
		uint8 _Level;
		uint32 _Size;
		raw _Data;

	public:
		Block(uint8 level, uint32 support);
		virtual ~Block();

	public:
		//test if address in block
		bool Enclose(raw data);

		//get pointer by offset from head
		raw Offset(uint32 offset);

		//test if action supported
		bool Support(uint32 action);

	public:
		//get used size of block
		virtual uint32 UsedSize() = 0;

		//get free size of block
		virtual uint32 FreeSize() = 0;

		//get object(s) count at address
		virtual uint32 Count(raw data, uint32 unit) = 0;

	public:
		//allocate space in size
		virtual raw Allocate(uint32 size);

		//free space
		virtual void Free(raw data, bool clear = false);

		//resize space
		virtual void Resize(raw data, uint32 size);

	public:
		//reset block
		virtual void Reset() = 0;

		//optimize block storage
		virtual void Optimize() = 0;
	};
}