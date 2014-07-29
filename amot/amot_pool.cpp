#include "amot_pool.h"
#include "amot_block.h"
#include "amot_factory.h"
#include "amot_setting.h"

namespace amot
{
	Pool::Pool(Setting* setting)
	{
		_Setting = (setting == null ? new Setting() : setting);
		_MaxBlockCount = _Setting->MaxBlockCount();
		_MaxBlockSize = _Setting->MaxBlockSize();

		_Blocks = new PBlock[_MaxBlockCount];
		for (uint32 i = 0; i < _MaxBlockCount; i++)
			_Blocks[i] = null;

		Rebuild();
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

	PBlock Pool::Expand(uint32 size)
	{
		uint8 lvl = GetMinBlockLevel(size);
		Factory* factory = Factory::Instance();
		for (uint32 i = 0; i<_MaxBlockCount; i++)
		{
			if (_Blocks[i] == null)
			{
				_Blocks[i] = factory->CreateBlock(
					_Setting->DefaultBlockType(), lvl);
				return _Blocks[i];
			}
		}
		return null;
	}

	PBlock Pool::Rebuild()
	{
		Factory* factory = Factory::Instance();
		PBlock block = factory->CreateBlock(
			_Setting->DefaultBlockType(), _Setting->MinBlockLevel());
		_Blocks[0] = block;
		return block;
	}

	void Pool::ToDispose(raw data, uint32 unit)
	{
		for (uint32 i = 0; i < _MaxBlockCount; i++)
		{
			PBlock block = _Blocks[i];
			if (block == null || !block->Enclose(data))
				continue;
			uint32 count = block->Count(data, unit);
			uint32 addr = (uint32)data;
			for (uint32 i = 0; i < count; i++)
			{
				((IDisposable*)addr)->Dispose();
				addr += unit;
			}
		}
	}

	raw Pool::Allocate(uint32 size)
	{
		if (size == 0 || size > _MaxBlockSize)
			return null;

		//1st : try to allocate memory
		for (uint32 i = 0; i<_MaxBlockCount; i++)
		{
			PBlock block = _Blocks[i];
			if(block == null)
				continue;
			raw data = block->Allocate(size);
			if(data != null) 
				return data;
		}

		//2nd : try to create block
		PBlock block = Expand(size);
		if(block != null)
		{
			raw data = block->Allocate(size);
			if(data == null) 
				throw amot_err4;
			else return data;
		}
		return null;
	}

	void Pool::Free(raw data, bool clear)
	{
		for (uint32 i = 0; i < _MaxBlockCount; i++)
		{
			PBlock block = _Blocks[i];
			if (block != null && block->Enclose(data))
				block->Free(data, clear);
		}
	}

	void Pool::FreeAll()
	{
		for (uint32 i = 0; i < _MaxBlockCount; i++)
		{
			PBlock block = _Blocks[i];
			if (block == null)
				continue;
			delete block;
			_Blocks[i] = null;
		}
		Rebuild();
	}

	void Pool::Optimize()
	{
		int block_count = 0;
		for (uint32 i = 0; i < _MaxBlockCount; i++)
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
			Rebuild();
	}
}