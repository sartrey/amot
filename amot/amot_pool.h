#pragma once

#include "amot_base.h"
#include "amot_object.h"

namespace amot
{
	class Setting;
	class Factory;
	class Block;
	typedef Block* PBlock;

	//memory pool
	class AMOT_API Pool
	{
	private:
		Setting* _Setting;
		Factory* _Factory;
		PBlock* _Blocks;

	private:
		uint32 _MaxBlockCount;
		uint32 _MaxBlockSize;

	public:
		Pool(Setting* setting = null);
		~Pool();

	private:
		PBlock Rebuild();
		PBlock Expand(uint32 size);

	public:
		//allocate space
		raw Allocate(uint32 size);

		//free space
		void Free(raw data, bool clear = false);

		//free all space
		void FreeAll();

		//resize space
		raw Resize(raw data, uint32 size);

	public:
		//new object
		template<typename T>
		T* New(uint32 count = 1, bool ctor = false)
		{
			uint32 unit = sizeof(T);
			uint32 size = unit * count;
			raw data = Allocate(size);
			if(ctor)
			{
				uint32 addr = (uint32)data;
				for(uint32 i = 0; i < count; i++)
				{
					new((raw)addr) T(); //unsafe
					((IObject*)addr)->New();
					addr += unit;
				}
			}
			return (T*)data;
		}

		//dispose object
		template<typename T>
		void Dispose(T* data, bool clear = false)
		{
			uint32 unit = sizeof(T);
			PBlock block = Search(data);
			if (block != null)
			{
				uint32 count = block->Count(data, unit);
				uint32 addr = (uint32)data;
				for (uint32 i = 0; i < count; i++)
				{
					((IObject*)addr)->Dispose();
					addr += unit;
				}
				block->Free(data, clear);
			}
		}

	public:
		//get factory
		Factory* Factory();

		//mount block
		void Mount(PBlock block);

		//search block by data
		PBlock Search(raw data);

		//optimize pool
		void Optimize();
	};
}