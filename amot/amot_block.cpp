#include "stdafx.h"
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
		if(_Data != NULL) delete [] _Data;
	}

	bool Block::Enclose(object data)
	{
		uint32 d1 = (uint32)_Data;
		uint32 d2 = (uint32)data;
		if(d2 < d1) return false;
		if(d2 >= d1 + _Size) return false;
		return true;
	}

	object Block::Offset(uint32 offset)
	{
		return (object)((uint32)_Data + offset);
	}
}