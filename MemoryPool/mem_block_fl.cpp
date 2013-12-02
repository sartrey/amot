#include "stdafx.h"
#include "mem_block_fl.h"

namespace mempool
{
	MemoryBlockFL::MemoryBlockFL(UINT level, UINT unit)
			: MemoryBlock(level, MP_BCK_TYPE_FL)
	{
		_Unit = unit;
		UINT total_var = GetMPBVol(level, unit);
		_TotalRec = total_var / 8;
		_Size = total_var * unit;

		_Data = new BYTE[_Size];
		_Record = new BYTE[_TotalRec];
		memset(_Data, 0, _Size);
		memset(_Record, 0, _TotalRec);
	}

	MemoryBlockFL::~MemoryBlockFL()
	{
		if(_Record != NULL) delete [] _Record;
	}

	UINT MemoryBlockFL::GetUsedSize()
	{
		UINT uc = 0;
		for(UINT i=0;i<_TotalRec;i++)
		{
			BYTE tmp = _Record[i];
			for(int j=0;j<8;j++)
			{
				uc += (tmp & 0x01);
				tmp >>= 1;
			}
		}
		UINT us = uc * _Unit;
		return us;
	}

	UINT MemoryBlockFL::GetFreeSize()
	{
		return _Size - GetUsedSize();
	}

	UINT MemoryBlockFL::GetObjectCount(LPVOID data, UINT size)
	{
		UINT offset = (UINT)data - (UINT)_Data;
		if(offset % _Unit != 0) return 0;
		UINT count = _Unit / size;
		return count;
	}

	LPVOID MemoryBlockFL::Alloc(UINT len)
	{
		if(len != _Unit) return NULL;
		UINT offset = 0;
		for(UINT i=0;i<_TotalRec;i++)
		{
			BYTE tmp = _Record[i];
			if(tmp == 0xFF)
			{
				offset += 8;
				continue;
			}
			for(BYTE j=7;j>=0;j--)
			{
				if((tmp >> j) & 0x01) ++offset;
				else
				{
					_Record[i] = tmp | (0x01 << j);
					return (LPVOID)((UINT)_Data + offset*_Unit);
				}
			}
		}
		return NULL;
	}

	bool MemoryBlockFL::Free(LPVOID data, bool clear)
	{
		UINT offset = (UINT)data - (UINT)_Data;
		if(offset % _Unit != 0) return false;
		offset = offset / _Unit;
		if(clear) memset(data, 0, _Unit);
		BYTE tmp = 0xFF ^ (0x01 << (7 - offset % 8));
		_Record[offset/8] &= tmp;
		return true;
	}

	void MemoryBlockFL::Optimize()
	{
	}

	UINT MemoryBlockFL::GetUnit()
	{
		return _Unit;
	}
}