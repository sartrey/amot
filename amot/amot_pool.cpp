#include "amot_pool.h"
#include "amot_setting.h"
#include "amot_factory.h"
#include "amot_block.h"

namespace amot
{
	Pool::Pool(Setting* setting)
	{
		_Setting = (setting == null ? new Setting() : setting);
		_MaxBlockCount = _Setting->MaxBlockCount();
		_MaxBlockSize = _Setting->MaxBlockSize();

		_Factory = new amot::Factory();

		_Blocks = new PBlock[_MaxBlockCount];
		for (uint32 i = 0; i < _MaxBlockCount; i++)
			_Blocks[i] = null;
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
		if (_Factory != null)
			delete _Factory;
		if(_Setting != null)
			delete _Setting;
	}

	//----- ----- ----- ----- ----- -----

	PBlock Pool::Search(raw data)
	{
		for (uint32 i = 0; i < _MaxBlockCount; i++)
		{
			PBlock block = _Blocks[i];
			if (block == null || !block->Enclose(data))
				continue;
			return block;
		}
		return null;
	}

	PBlock Pool::Expand(uint32 size)
	{
		for (uint32 i = 0; i<_MaxBlockCount; i++)
		{
			if (_Blocks[i] == null)
			{
				PBlock block = _Factory->CreateBlock(
					_Setting->BlockType(), size);
				_Blocks[i] = block;
				return block;
			}
		}
		return null;
	}

	PBlock Pool::Rebuild()
	{
		PBlock block = _Factory->CreateBlock(
			_Setting->BlockType(), 0);
		_Blocks[0] = block;
		return block;
	}

	//----- ----- ----- ----- ----- -----

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
		PBlock block = Search(data);
		if (block != null)
			block->Free(data, clear);
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

	//----- ----- ----- ----- ----- -----

	Factory* Pool::Factory()
	{
		return _Factory;
	}

	void Pool::Mount(PBlock block)
	{
		for (uint32 i = 0; i<_MaxBlockCount; i++)
		{
			if (_Blocks[i] == null)
			{
				_Blocks[i] = block;
				return;
			}
		}
	}

	void Pool::Optimize()
	{
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
		}
	}
}