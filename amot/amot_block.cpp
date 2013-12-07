#include "amot_block.h"

namespace amot
{
	Block::Block(uint8 level, uint8 type)
	{
		_Type = type;
		_Level = level;
	}

	Block::~Block()
	{
		if(_Data != null)
			delete [] _Data;
	}

	bool Block::Enclose(object data)
	{
		uint32 d1 = (uint32)_Data;
		uint32 d2 = (uint32)data;
		return (d2 >= d1 && d2 < d1 + _Size);
	}

	object Block::Offset(uint32 offset)
	{
		return (object)((uint32)_Data + offset);
	}
}