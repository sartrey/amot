#include "amot_block_fl.h"

namespace amot
{
	BlockFL::BlockFL(uint8 level, uint32 unit)
		: Block(level,
		AMOT_ACTION_ALLOC |
		AMOT_ACTION_FREE |
		AMOT_ACTION_RESIZE |
		AMOT_ACTION_TRIM)
	{
		uint32 max_vol = GetBlockVolume(level);
		uint32 max_unit = max_vol / unit;
		_Total = max_unit / 8;
		_Size = max_unit * unit; //real size
		_Unit = unit;

		_Data = new byte[_Size];
		_Record = new byte[_Total];
		memset(_Data, 0, _Size);
		memset(_Record, 0, _Total);
	}

	BlockFL::~BlockFL()
	{
		if (_Record != null)
			delete _Record;
	}

	uint32 BlockFL::UsedSize()
	{
		uint32 count = 0;
		for (uint32 i = 0; i < _Total; i++)
		{
			byte tmp = _Record[i];
			for (byte j = 0; j < 8; j++)
			{
				count += (tmp & 0x1);
				tmp >>= 1;
			}
		}
		uint32 size = count * _Unit;
		return size;
	}

	uint32 BlockFL::FreeSize()
	{
		return _Size - UsedSize();
	}

	uint32 BlockFL::Count(raw data, uint32 unit)
	{
		uint32 offset = (uint32)data - (uint32)_Data;
		if(offset % _Unit != 0) 
			return 0;
		uint32 count = _Unit / unit;
		return count;
	}

	raw BlockFL::Allocate(uint32 size)
	{
		if (size != _Unit)
			return null;
		uint32 offset = 0;
		for (uint32 i = 0; i < _Total; i++)
		{
			byte tmp = _Record[i];
			if (tmp == 0xFF)
			{
				offset += 8;
				continue;
			}
			for (byte j = 7; j >= 0; j--)
			{
				if ((tmp >> j) & 0x01) ++offset;
				else
				{
					_Record[i] = tmp | (0x01 << j);
					return (raw)((uint32)_Data + offset * _Unit);
				}
			}
		}
		return null;
	}

	void BlockFL::Free(raw data, bool clear)
	{
		uint32 offset = (uint32)data - (uint32)_Data;
		if (offset % _Unit == 0)
		{
			offset = offset / _Unit;
			if (clear)
				memset(data, 0, _Unit);
			byte tmp = 0xFF ^ (0x01 << (7 - offset % 8));
			_Record[offset / 8] &= tmp;
		}
	}

	void BlockFL::Optimize()
	{
	}
}