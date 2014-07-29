#pragma once

#include "amot_base.h"

namespace amot
{
	class Setting;
	class Block;
	typedef Block* PBlock;

	//memory pool
	class AMOT_API Pool
	{
	private:
		Setting* _Setting;
		Lock* _Lock;
		PBlock* _Blocks;

	private:
		uint32 _MaxBlockCount;
		uint32 _MaxBlockSize;

	public:
		Pool(Setting* setting = null);
		~Pool();

	private:
		PBlock Expand(uint32 size);
		PBlock Rebuild();
		void ToDispose(raw data, uint32 unit);

	public:
		//allocate space
		raw Allocate(uint32 size);

		//free space
		void Free(raw data, bool clear = false);

		//free all space
		void FreeAll();

		//resize space
		void Resize(raw data, uint32 size);

		//trim space by data
		void Trim(raw data);

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
					new((raw)addr) T();
					addr += size;
				}
			}
			return (T*)data;
		}

		//dispose object
		template<typename T>
		void Dispose(T* data)
		{
			uint32 unit = sizeof(T);
			ToDispose(data, unit);
		}

	public:
		//mount user block
		void Mount(PBlock block);

		//optimize pool
		void Optimize();
	};
}