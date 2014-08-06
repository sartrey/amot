#include "amot_block_fl.h"

namespace amot
{
	BlockFL::BlockFL(uint8 level)
		: Block(level,
		AMOT_ACTION_ALLOC |
		AMOT_ACTION_FREE)
	{
		_Record = null;
	}

	BlockFL::~BlockFL()
	{
		if (_Record != null)
			delete _Record;
	}

	void BlockFL::SetUnit(uint32 unit)
	{
		_Unit = unit;
	}

	uint32 BlockFL::UsedSize()
	{
		uint32 count = 0;
		for (uint32 i = 0; i < _RecordTotal; i++)
		{
			uint8 rec = _Record[i];
			rec = (rec & 0x55) + ((rec >> 1) & 0x55555555);
			rec = (rec & 0x33) + ((rec >> 2) & 0x33333333);
			rec = (rec & 0x0F) + ((rec >> 4) & 0x0F0F0F0F);
			count += rec;
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
		if (offset % _Unit != 0)
			return 0;
		uint32 count = _Unit / unit;
		return count;
	}

	raw BlockFL::Allocate(uint32 size)
	{
		if (size != _Unit)
			return null;
		uint32 offset = 0;
		for (uint32 i = 0; i < _RecordTotal; i++)
		{
			uint8 rec = _Record[i];
			if (rec == 0xFF)
			{
				offset += 8;
				continue;
			}
			for (byte j = 7; j >= 0; j--)
			{
				if ((rec >> j) & 0x01) ++offset;
				else
				{
					_Record[i] = rec | (0x01 << j);
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

	void BlockFL::Reset()
	{
		uint32 max_vol = GetBlockVolume(_Level);
		uint32 max_unit = max_vol / _Unit;
		_RecordTotal = max_unit / 8;
		_Size = max_unit * _Unit; //real size

		_Data = new byte[_Size];
		_Record = new uint8[_RecordTotal];
		memset(_Data, 0, _Size);
		memset(_Record, 0, _RecordTotal);
	}

	void BlockFL::Optimize()
	{
	}
}