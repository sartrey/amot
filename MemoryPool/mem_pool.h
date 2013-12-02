#pragma once

#include "base.h"
#include "mem_config.h"

namespace mempool
{
	class MemoryBlock;
	typedef MemoryBlock* PMemBck;

	class MemoryPool
	{
	public:
		MemoryPool(PMemCfg config = NULL);
		~MemoryPool();
	private:
		PMemCfg _Config;
		PMemBck* _Blocks;
		UINT* _BlockEdges;
	public:
		//Alloc memory
		template<typename T>
		T* Alloc(UINT count = 1, bool ctor = false)
		{
			LPVOID data = _Alloc(sizeof(T), count);
			if(ctor)
				for(UINT i=0;i<count;i++)
					new((LPVOID)(((UINT)data+i*sizeof(T)))) T();
			return (T*)data;
		}

		//Dispose object
		//Type sensitive
		template<typename T>
		void Dispose(T* data)
		{
			//TODO: log the dispose procedure
			UINT size = sizeof(T);
			_Dispose(data, size);
		}

		//Free memory
		bool Free(LPVOID data, bool clear = false);

		//Free all memory
		void FreeAll(bool clear = false);

		//Sign length
		bool Sign(UINT size, UINT count = 1000);

		//Unsign length
		bool Unsign(UINT size);

		//Optimize pool
		void Optimize();

		//Expand
		bool Expand(UINT len);
	private:
		LPVOID _Alloc(UINT size, UINT count);
		void _Dispose(LPVOID data, UINT size);
		PMemBck _Expand(UINT len);
	};
}