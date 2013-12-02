#include "stdafx.h"
#include <cmath>

#include "base.h"
#include "mem_pool.h"
#include "mem_block_gp.h"
#include "mem_block_fl.h"

namespace mempool
{
	MemoryPool::MemoryPool(PMemCfg config)
	{
		_Config = (config == NULL ? new MemoryConfig() : config);

		_Blocks = new PMemBck[_Config->MP_BCK_COUNT_MAX];
		for(UINT i=0; i<_Config->MP_BCK_COUNT_MAX; i++) _Blocks[i] = NULL;

		//0 - GP=FL , 1 - ...
		_BlockEdges = new UINT[1];
		_BlockEdges[0] = _Config->MP_BCK_COUNT_MAX - _Config->MP_FL_COUNT_MAX;

		PMemBck bck = new MemoryBlockGP(_Config->MP_BCK_LEVEL_DEFAULTMIN);
		_Blocks[0] = bck;
	}

	MemoryPool::~MemoryPool()
	{
		if(_Blocks != NULL) 
		{
			for(UINT i=0;i<_Config->MP_BCK_COUNT_MAX;i++)
				if(_Blocks[i] != NULL)
					delete _Blocks[i];
			delete [] _Blocks;
		}
		delete [] _BlockEdges;
		if(_Config != NULL)
		{
			delete _Config;
			_Config = NULL;
		}
	}

	LPVOID MemoryPool::_Alloc(UINT size, UINT count)
	{
		UINT len = size * count;
		if(len == 0 && len > MP_BCK_SIZE_MAX) return NULL;

		//Fixed Length BCK
		for(UINT i=_BlockEdges[0];i<_Config->MP_BCK_COUNT_MAX;i++)
		{
			if(_Blocks[i] == NULL) continue;
			LPVOID data = _Blocks[i]->Alloc(len);
			if(data != NULL) return data;
		}

		//General Purpose BCK
		for(UINT i=0;i<_BlockEdges[0];i++)
		{
			if(_Blocks[i] == NULL) continue;
			LPVOID data = _Blocks[i]->Alloc(len);
			if(data != NULL) return data;
		}
		PMemBck bck = _Expand(len);
		if(bck != NULL)
		{
			LPVOID data = bck->Alloc(len);
			if(data != NULL) return data;
		}
		return NULL;
	}

	void MemoryPool::_Dispose(LPVOID data, UINT size)
	{
		for(UINT i=0;i<_Config->MP_BCK_COUNT_MAX;i++)
		{
			MemoryBlock* bck = _Blocks[i];
			if(bck == NULL) continue;
			if(!bck->CanContain(data)) continue;
			UINT count = bck->GetObjectCount(data, size);
			for(UINT i=0; i<count; i++)
				((IDisposable*)((UINT)data+i*size))->Dispose();
		}
	}

	PMemBck MemoryPool::_Expand(UINT len)
	{
		UINT lvl = GetMPBLevel(len);
		UINT idx = 0;
		bool has_null = false;
		for(UINT i=0; i<_BlockEdges[0]; i++)
		{
			if(_Blocks[i] == NULL)
			{
				idx = i;
				has_null = true;
				break;
			}
		}
		if(!has_null) return NULL;
		MemoryBlockGP* bck = new MemoryBlockGP(lvl);
		_Blocks[idx] = bck;
		return bck;
	}

	bool MemoryPool::Expand(UINT len)
	{
		PMemBck bck = _Expand(len);
		return (bck != NULL);
	}

	bool MemoryPool::Free(LPVOID data, bool clear)
	{
		for(UINT i=0;i<_Config->MP_BCK_COUNT_MAX;i++)
		{
			MemoryBlock* bck = _Blocks[i];
			if(bck == NULL) continue;
			if(!bck->CanContain(data)) continue;
			if(bck->Free(data, clear)) return true;
		}
		return false;
	}

	void MemoryPool::FreeAll(bool clear)
	{
		for(UINT i=0;i<_Config->MP_BCK_COUNT_MAX;i++)
		{
			MemoryBlock* bck = _Blocks[i];
			if(bck == NULL) continue;
			delete bck;
			_Blocks[i] = NULL;
		}
		//Rebuild first block
		PMemBck bck = new MemoryBlockGP(_Config->MP_BCK_LEVEL_DEFAULTMIN);
		_Blocks[0] = bck;
	}

	void MemoryPool::Optimize()
	{
		for(UINT i=0;i<_Config->MP_BCK_COUNT_MAX;i++)
		{
			MemoryBlock* bck = _Blocks[i];
			if(bck == NULL) continue;
			if(bck->GetUsedSize() == 0)
			{
				delete bck;
				_Blocks[i] = NULL;
			}
			else
			{
				bck->Optimize();
			}
		}
		UINT gp_count = 0;
		for(UINT i=0;i<_BlockEdges[0];i++)
			if(_Blocks[i] != NULL) ++gp_count;
		if(gp_count == 0)
		{
			//Rebuild first block
			PMemBck bck = new MemoryBlockGP(_Config->MP_BCK_LEVEL_DEFAULTMIN);
			_Blocks[0] = bck;
		}
	}

	bool MemoryPool::Sign(UINT size, UINT count)
	{
		UINT idx = 0;
		bool has_null = false;
		for(UINT i=_BlockEdges[0];i<_Config->MP_BCK_COUNT_MAX;i++)
		{
			if(_Blocks[i] != NULL)
			{
				MemoryBlockFL* bck = dynamic_cast<MemoryBlockFL*>(_Blocks[i]);
				if(size == bck->GetUnit()) return false;
			}
			else
			{
				idx = i;
				has_null = true;
				break;
			}
		}
		if(!has_null) return false;
		UINT lvl = GetMPBLevel(size * count);
		MemoryBlockFL* bck = new MemoryBlockFL(lvl, size);
		_Blocks[idx] = bck;
		return true;
	}

	bool MemoryPool::Unsign(UINT size)
	{
		for(UINT i=_BlockEdges[0];i<_Config->MP_BCK_COUNT_MAX;i++)
		{
			if(_Blocks[i] != NULL)
			{
				MemoryBlockFL* bck = dynamic_cast<MemoryBlockFL*>(_Blocks[i]);
				if(size == bck->GetUnit()) 
				{
					if(bck->GetUsedSize() != 0) return false;
					delete bck;
					_Blocks[i] = NULL;
					return true;
				}
			}
		}
		return false;
	}
}