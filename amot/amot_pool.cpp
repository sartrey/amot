#include "amot_pool.h"
#include "amot_setting.h"
#include "amot_factory.h"
#include "amot_block_gp.h"
#include "amot_block_fl.h"

namespace amot
{
	Pool::Pool(Setting* setting)
	{
		_Setting = (setting == null ? new Setting() : setting);
		_BlockTotal = _Setting->MaxBlockCount();

		_Blocks = new PBlock[_BlockTotal];
		for (uint32 i = 0; i < _BlockTotal; i++)
			_Blocks[i] = null;

		_Rebuild();
	}

	Pool::~Pool()
	{
		if(_Blocks != null) 
		{
			for (uint32 i = 0; i<_Setting->MaxBlockCount(); i++)
				if(_Blocks[i] != null)
					delete _Blocks[i];
			delete _Blocks;
		}
		if(_Setting != null)
			delete _Setting;
	}

	raw Pool::_Allocate(uint32 size)
	{
		if (size == 0 || size > AMOT_BLOCK_SIZE_MAX)
			return null;

		//1st : try to allocate memory
		for (uint32 i = 0; i<_BlockTotal; i++)
		{
			PBlock block = _Blocks[i];
			if(block == null)
				continue;
			raw data = block->Alloc(size);
			if(data != null) 
				return data;
		}

		//2nd : try to create block
		PBlock block = _Expand(size);
		if(block != null)
		{
			raw data = block->Alloc(size);
			if(data == null) 
				throw AMOT_ERROR_BLOCK;
			else return data;
		}
		return null;
	}

	void Pool::_Dispose(raw data, uint32 size)
	{
		for (uint32 i = 0; i < _BlockTotal; i++)
		{
			PBlock block = _Blocks[i];
			if (block == null || !block->Enclose(data))
				continue;
			uint32 count = block->Count(data, size);
			uint32 addr = (uint32)data;
			for (uint32 i = 0; i < count; i++)
			{
				((IDisposable*)addr)->Dispose();
				addr += size;
			}
		}
	}

	PBlock Pool::_Expand(uint32 size)
	{
		uint8 lvl = GetMinBlockLevel(size);
		Factory* factory = Factory::Instance();
		for (uint32 i = 0; i<_BlockTotal; i++)
		{
			if(_Blocks[i] == null)
			{
				_Blocks[i] = factory->CreateBlock(
					_Setting->BlockType(), lvl);
				return _Blocks[i];
			}
		}
		return null;
	}

	PBlock Pool::_Rebuild()
	{
		Factory* factory = Factory::Instance();
		PBlock block = factory->CreateBlock(
			_Setting->BlockType(), _Setting->MinBlockLevel());
		_Blocks[0] = block;
		return block;
	}

	bool Pool::Expand(raw data, uint32 size)
	{
		return false;
	}

	void Pool::Free(raw data, bool clear)
	{
		for (uint32 i = 0; i < _BlockTotal; i++)
		{
			Block* block = _Blocks[i];
			if (block != null && block->Enclose(data))
				block->Free(data, clear);
		}
	}

	void Pool::FreeAll()
	{
		for (uint32 i = 0; i < _BlockTotal; i++)
		{
			PBlock block = _Blocks[i];
			if (block == null)
				continue;
			delete block;
			_Blocks[i] = null;
		}
		_Rebuild();
	}

	void Pool::Optimize()
	{
		int block_count = 0;
		for (uint32 i = 0; i < _BlockTotal; i++)
		{
			PBlock block = _Blocks[i];
			if (block == null)
				continue;
			if (block->UsedSize() == 0)
			{
				delete block;
				_Blocks[i] = null;
			}
			else
			{
				block->Optimize();
			}
			if (block != null)
				block_count++;
		}
		if (block_count == 0)
			_Rebuild();
	}
}