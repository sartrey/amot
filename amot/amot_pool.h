#pragma once

#include "amot_config.h"
#include "amot_block.h"

namespace amot
{
	class AMOT_API Pool
	{
	public:
		Pool(PtrConfig config = null);
		~Pool();
	private:
		PtrConfig _Config;
		PtrBlock* _Blocks;
		uint32* _BlockOffsets;
	public:
		//allocate memory
		template<typename T>
		T* Alloc(uint32 count = 1, bool ctor = false)
		{
			uint32 size = sizeof(T);
			object data = _Alloc(size, count);
			if(ctor)
			{
				uint32 addr = (uint32)data;
				for(uint32 i = 0; i < count; i++)
				{
					new((object)addr) T();
					addr += size;
				}
			}
			return (T*)data;
		}

		//dispose object
		//type sensitive
		template<typename T>
		void Dispose(T* data)
		{
			//TODO: log the dispose procedure
			uint32 size = sizeof(T);
			_Dispose(data, size);
		}

		//free memory
		void Free(object data, bool clear = false);

		//free all memory
		void FreeAll();

		//sign length
		void Sign(uint32 size, uint32 count = 1000);

		//unsign length
		void Unsign(uint32 size);

		//optimize pool
		void Optimize();

		//expand
		bool Expand(uint32 len);
	private:
		object _Alloc(uint32 size, uint32 count);
		void _Dispose(object data, uint32 size);
		PtrBlock _Expand(uint32 len);
		PtrBlock _Rebuild();
	};
}