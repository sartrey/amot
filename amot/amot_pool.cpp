#include "amot_pool.h"
#include "amot_block_gp.h"
#include "amot_block_fl.h"

namespace amot
{
	Pool::Pool(PtrConfig config)
	{
		_Config = (config == null ? new Config() : config);
		uint32 block_total = _Config->BLOCK_COUNT_MAX();

		_Blocks = new PtrBlock[block_total];
		for(uint32 i=0; i<block_total; i++) 
			_Blocks[i] = null;

		//GP | FL | ...
		//e.g. GP:2|FL:4| => {2,6}
		_BlockOffsets = new uint32[2];
		_BlockOffsets[0] = _Config->GP_BLOCK_COUNT_MAX();
		_BlockOffsets[1] = _BlockOffsets[0] + _Config->FL_BLOCK_COUNT_MAX();
		//more block type ...

		PtrBlock bck = new BlockGP(_Config->USER_BLOCK_LEVEL_MIN());
		_Blocks[0] = bck;
	}

	Pool::~Pool()
	{
		if(_Blocks != null) 
		{
			for(uint32 i=0;i<_Config->BLOCK_COUNT_MAX();i++)
				if(_Blocks[i] != null)
					delete _Blocks[i];
			delete [] _Blocks;
		}
		if(_Config != null)
			delete _Config;
	}

	object Pool::_Alloc(uint32 size, uint32 count)
	{
		uint32 len = size * count;
		if(len == 0 || len > AMOT_BLOCK_SIZE_MAX)
			return null;

		//1st try: fixed length
		for(uint32 i=_BlockOffsets[0]; i<_BlockOffsets[1]; i++)
		{
			if(_Blocks[i] == null) 
				continue;
			object data = _Blocks[i]->Alloc(len);
			if(data != null) 
				return data;
		}

		//2nd try: general purpose
		for(uint32 i=0; i<_BlockOffsets[0]; i++)
		{
			if(_Blocks[i] == null)
				continue;
			object data = _Blocks[i]->Alloc(len);
			if(data != null) 
				return data;
		}

		//expand block
		PtrBlock bck = _Expand(len);
		if(bck != null)
		{
			object data = bck->Alloc(len);
			if(data == null) 
				throw new bad_exception(AMOT_ERR_2);
			else return data;
		}
		return null;
	}

	void Pool::_Dispose(object data, uint32 size)
	{
		for(uint32 i=0; i<_Config->BLOCK_COUNT_MAX(); i++)
		{
			PtrBlock bck = _Blocks[i];
			if(bck == null || !bck->Enclose(data)) 
				continue;
			uint32 count = bck->Count(data, size);
			uint32 addr = (uint32)data;
			for(uint32 i = 0; i<count; i++)
			{
				((IDisposable*)addr)->Dispose();
				addr += size;
			}
		}
	}

	PtrBlock Pool::_Expand(uint32 len)
	{
		uint8 lvl = GetMinBlockLevel(len);
		//GP block
		for(uint32 i=0; i<_BlockOffsets[0]; i++)
		{
			if(_Blocks[i] == null)
			{
				_Blocks[i] = new BlockGP(lvl);
				return _Blocks[i];
			}
		}
		return null;
	}

	PtrBlock Pool::_Rebuild()
	{
		PtrBlock bck = new BlockGP(_Config->USER_BLOCK_LEVEL_MIN());
		_Blocks[0] = bck;
		return bck;
	}

	bool Pool::Expand(uint32 len)
	{
		PtrBlock bck = _Expand(len);
		return (bck != null);
	}

	void Pool::Free(object data, bool clear)
	{
		for(uint32 i=0; i<_Config->BLOCK_COUNT_MAX(); i++)
		{
			Block* bck = _Blocks[i];
			if(bck == null || !bck->Enclose(data)) 
				continue;
			bck->Free(data, clear);
		}
	}

	void Pool::FreeAll()
	{
		for(uint32 i=0; i<_Config->BLOCK_COUNT_MAX(); i++)
		{
			PtrBlock bck = _Blocks[i];
			if(bck == null) 
				continue;
			delete bck;
			_Blocks[i] = null;
		}
		_Rebuild();
	}

	void Pool::Optimize()
	{
		for(uint32 i=0; i<_Config->BLOCK_COUNT_MAX(); i++)
		{
			PtrBlock bck = _Blocks[i];
			if(bck == null)
				continue;
			if(bck->UsedSize() == 0)
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
		for(uint32 i=0; i<_Config->GP_BLOCK_COUNT_MAX(); i++)
			if(_Blocks[i] != null)
				++gp_count;
		if(gp_count == 0)
			_Rebuild();
	}

	void Pool::Sign(uint32 size, uint32 count)
	{
		bool has_null = false;
		uint32 idx = 0;
		//FL block
		for(uint32 i=_BlockOffsets[0]; i<_BlockOffsets[1]; i++)
		{
			if(_Blocks[i] != null)
			{
				BlockFL* bck = dynamic_cast<BlockFL*>(_Blocks[i]);
				if(size == bck->Unit()) 
					return;
			}
			else 
			{
				idx = i;
				has_null = true;
			}
		}
		if(has_null) 
		{
			uint8 lvl = GetMinBlockLevel(size * count);
			BlockFL* bck = new BlockFL(lvl, size);
			_Blocks[idx] = bck;
		}
	}

	void Pool::Unsign(uint32 size)
	{
		for(uint32 i=_BlockOffsets[0]; i<_BlockOffsets[1]; i++)
		{
			if(_Blocks[i] != null)
			{
				BlockFL* bck = dynamic_cast<BlockFL*>(_Blocks[i]);
				if(size == bck->Unit()) 
				{
					if(bck->UsedSize() == 0)
					{
						delete bck;
						_Blocks[i] = null;
					}
				}
			}
		}
	}
}