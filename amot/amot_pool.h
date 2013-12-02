#pragma once

#include "amot_base.h"
#include "amot_config.h"
#include "amot_block.h"

namespace amot
{
	class Pool
	{
	public:
		Pool(PtrConfig config = null);
		~Pool();
	private:
		PtrConfig _Config;
		PtrBlock* _Blocks;
		uint32* _BlockEdges;
	public:
		//allocate memory
		template<typename T>
		T* Alloc(uint32 count = 1, bool ctor = false)
		{
			object data = _Alloc(sizeof(T), count);
			if(ctor)
				for(uint32 i = 0; i < count; i++)
					new((object)(((uint32)data + i * sizeof(T)))) T();
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
		bool Free(object data, bool clear = false);

		//free all memory
		void FreeAll(bool clear = false);

		//sign length
		bool Sign(uint32 size, uint32 count = 1000);

		//unsign length
		bool Unsign(uint32 size);

		//optimize pool
		void Optimize();

		//expand
		bool Expand(uint32 len);
	private:
		object _Alloc(uint32 size, uint32 count);
		void _Dispose(object data, uint32 size);
		PtrBlock _Expand(uint32 len);
	};
}