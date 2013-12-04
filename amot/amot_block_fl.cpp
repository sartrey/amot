#include "amot_block_fl.h"

namespace amot
{
	BlockFL::BlockFL(uint8 level, uint32 unit)
			: Block(level, AMOT_BLOCK_TYPE_FL)
	{
		_Unit = unit;
		uint32 total_var = GetBlockVol(level, unit);
		_TotalRec = total_var / 8;
		_Size = total_var * unit;

		_Data = new byte[_Size];
		_Record = new byte[_TotalRec];
		memset(_Data, 0, _Size);
		memset(_Record, 0, _TotalRec);
	}

	BlockFL::~BlockFL()
	{
		if(_Record != null)
			delete [] _Record;
	}

	uint32 BlockFL::UsedSize()
	{
		uint32 uc = 0;
		for(uint32 i=0; i<_TotalRec; i++)
		{
			byte tmp = _Record[i];
			for(int j=0; j<8; j++)
			{
				uc += (tmp & 0x01);
				tmp >>= 1;
			}
		}
		uint32 us = uc * _Unit;
		return us;
	}

	uint32 BlockFL::FreeSize()
	{
		return _Size - UsedSize();
	}

	uint32 BlockFL::Count(object data, uint32 size)
	{
		uint32 offset = (uint32)data - (uint32)_Data;
		if(offset % _Unit != 0) return 0;
		uint32 count = _Unit / size;
		return count;
	}

	object BlockFL::Alloc(uint32 len)
	{
		if(len != _Unit) return null;
		uint32 offset = 0;
		for(uint32 i=0; i<_TotalRec; i++)
		{
			byte tmp = _Record[i];
			if(tmp == 0xFF)
			{
				offset += 8;
				continue;
			}
			for(byte j=7; j>=0; j--)
			{
				if((tmp >> j) & 0x01) ++offset;
				else
				{
					_Record[i] = tmp | (0x01 << j);
					return (object)((uint32)_Data + offset * _Unit);
				}
			}
		}
		return null;
	}

	void BlockFL::Free(object data, bool clear)
	{
		uint32 offset = (uint32)data - (uint32)_Data;
		if(offset % _Unit == 0)
		{
			offset = offset / _Unit;
			if(clear) 
				memset(data, 0, _Unit);
			byte tmp = 0xFF ^ (0x01 << (7 - offset % 8));
			_Record[offset/8] &= tmp;
		}
	}

	void BlockFL::Optimize()
	{
	}
}