#pragma once

#include "amot_base.h"

namespace amot
{
	class Block;
	class Setting;
	class Factory;

	typedef Block* PBlock;

	//{base} memory pool
	class AMOT_API Pool
	{
	private:
		Setting* _Setting;
		Factory* _Factory;
		Lock* _Lock;
		PBlock* _Blocks;

	private:
		uint32 _BlockTotal;

	public:
		Pool(Setting* setting = null);
		~Pool();

	private:
		raw _Allocate(uint32 size);
		void _Dispose(raw data, uint32 size);
		Block* _Expand(uint32 len);
		Block* _Rebuild();

	public:
		//allocate memory
		template<typename T>
		T* Alloc(uint32 count = 1, bool ctor = false)
		{
			uint32 size = sizeof(T);
			raw data = _Alloc(size, count);
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

		//expand memory
		bool Expand(raw data, uint32 size);

		//dispose object
		template<typename T>
		void Dispose(T* data)
		{
			uint32 size = sizeof(T);
			_Dispose(data, size);
		}

		//free memory
		void Free(raw data, bool clear = false);

		//free all memory
		void FreeAll();

		//optimize pool
		void Optimize();
	};
}