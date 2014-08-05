#include "amot_block.h"

namespace amot
{
	Block::Block(uint8 level, uint32 support)
	{
		_Level = level;
		_Support = support;
		_Data = null;
	}

	Block::~Block()
	{
		if(_Data != null)
			delete _Data;
	}

	bool Block::Enclose(raw data)
	{
		uint32 d1 = (uint32)_Data;
		uint32 d2 = (uint32)data;
		return (d2 >= d1 && d2 < d1 + _Size);
	}

	raw Block::Offset(uint32 offset)
	{
		return (raw)((uint32)_Data + offset);
	}

	raw Block::Allocate(uint32)
	{
		throw amot_err2;
	}

	void Block::Free(raw, bool)
	{
		throw amot_err2;
	}

	void Block::Resize(raw, uint32)
	{
		throw amot_err2;
	}
}