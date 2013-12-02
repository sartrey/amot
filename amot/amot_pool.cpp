#include "stdafx.h"

#include "amot_pool.h"
#include "amot_block_gp.h"
#include "amot_block_fl.h"

namespace amot
{
	Pool::Pool(PtrConfig config)
	{
		_Config = (config == null ? new Config() : config);

		_Blocks = new PtrBlock[_Config->BLOCK_MAX_COUNT];
		for(uint32 i=0; i<_Config->BLOCK_MAX_COUNT; i++) 
			_Blocks[i] = null;

		//0 - GP=FL , 1 - ...
		_BlockEdges = new uint32[1];
		_BlockEdges[0] = _Config->BLOCK_MAX_COUNT - _Config->FL_MAX_COUNT;

		PtrBlock bck = new BlockGP(_Config->BLOCK_LEVEL_DEFAULTMIN);
		_Blocks[0] = bck;
	}

	Pool::~Pool()
	{
		if(_Blocks != null) 
		{
			for(uint32 i=0;i<_Config->BLOCK_MAX_COUNT;i++)
				if(_Blocks[i] != null)
					delete _Blocks[i];
			delete [] _Blocks;
		}
		delete [] _BlockEdges;
		if(_Config != null)
		{
			delete _Config;
			_Config = null;
		}
	}

	object Pool::_Alloc(uint32 size, uint32 count)
	{
		uint32 len = size * count;
		if(len == 0 && len > AMOT_BLOCK_SIZE_MAX) return null;

		//fixed length block
		for(uint32 i=_BlockEdges[0];i<_Config->BLOCK_MAX_COUNT;i++)
		{
			if(_Blocks[i] == null) continue;
			object data = _Blocks[i]->Alloc(len);
			if(data != null) return data;
		}

		//general purpose block
		for(uint32 i=0;i<_BlockEdges[0];i++)
		{
			if(_Blocks[i] == null)
				continue;
			object data = _Blocks[i]->Alloc(len);
			if(data != null) return data;
		}
		PtrBlock bck = _Expand(len);
		if(bck != null)
		{
			object data = bck->Alloc(len);
			if(data != null) return data;
		}
		return null;
	}

	void Pool::_Dispose(object data, uint32 size)
	{
		for(uint32 i=0;i<_Config->BLOCK_MAX_COUNT;i++)
		{
			PtrBlock bck = _Blocks[i];
			if(bck == NULL) continue;
			if(!bck->Enclose(data)) continue;
			uint32 count = bck->Count(data, size);
			for(uint32 i = 0; i<count; i++)
				((IDisposable*)((UINT)data+i*size))->Dispose();
		}
	}

	PtrBlock Pool::_Expand(uint32 len)
	{
		uint32 lvl = GetMaxBlockVol(len);
		uint32 idx = 0;
		bool has_null = false;
		for(uint32 i=0; i<_BlockEdges[0]; i++)
		{
			if(_Blocks[i] == null)
			{
				idx = i;
				has_null = true;
				break;
			}
		}
		if(!has_null) return null;
		BlockGP* bck = new BlockGP(lvl);
		_Blocks[idx] = bck;
		return bck;
	}

	bool Pool::Expand(uint32 len)
	{
		PtrBlock bck = _Expand(len);
		return (bck != null);
	}

	bool Pool::Free(object data, bool clear)
	{
		for(uint32 i=0; i<_Config->BLOCK_MAX_COUNT; i++)
		{
			Block* bck = _Blocks[i];
			if(bck == null) continue;
			if(!bck->Enclose(data)) continue;
			if(bck->Free(data, clear)) return true;
		}
		return false;
	}

	void Pool::FreeAll(bool clear)
	{
		for(uint32 i=0; i<_Config->BLOCK_MAX_COUNT; i++)
		{
			PtrBlock bck = _Blocks[i];
			if(bck == null) continue;
			delete bck;
			_Blocks[i] = null;
		}
		//Rebuild first block
		PtrBlock bck = new BlockGP(_Config->BLOCK_LEVEL_DEFAULTMIN);
		_Blocks[0] = bck;
	}

	void Pool::Optimize()
	{
		for(uint32 i=0; i<_Config->BLOCK_MAX_COUNT; i++)
		{
			PtrBlock bck = _Blocks[i];
			if(bck == null)
				continue;
			if(bck->GetUsedSize() == 0)
			{
				delete bck;
				_Blocks[i] = null;
			}
			else
			{
				bck->Optimize();
			}
		}
		uint32 gp_count = 0;
		for(uint32 i=0; i<_BlockEdges[0]; i++)
			if(_Blocks[i] != null)
				++gp_count;
		if(gp_count == 0)
		{
			//Rebuild first block
			PtrBlock bck = new BlockGP(_Config->BLOCK_LEVEL_DEFAULTMIN);
			_Blocks[0] = bck;
		}
	}

	bool Pool::Sign(uint32 size, uint32 count)
	{
		uint32 idx = 0;
		bool has_null = false;
		for(uint32 i=_BlockEdges[0]; i<_Config->BLOCK_MAX_COUNT; i++)
		{
			if(_Blocks[i] != null)
			{
				BlockFL* bck = dynamic_cast<BlockFL*>(_Blocks[i]);
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
		uint8 lvl = GetMinBlockLevel(size * count);
		BlockFL* bck = new BlockFL(lvl, size);
		_Blocks[idx] = bck;
		return true;
	}

	bool Pool::Unsign(uint32 size)
	{
		for(uint32 i=_BlockEdges[0]; i<_Config->BLOCK_MAX_COUNT; i++)
		{
			if(_Blocks[i] != null)
			{
				BlockFL* bck = dynamic_cast<BlockFL*>(_Blocks[i]);
				if(size == bck->GetUnit()) 
				{
					if(bck->GetUsedSize() != 0) return false;
					delete bck;
					_Blocks[i] = null;
					return true;
				}
			}
		}
		return false;
	}
}