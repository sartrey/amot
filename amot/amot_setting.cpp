#include "amot_setting.h"

namespace amot
{
	Setting::Setting()
	{
		_BlockType = AMOT_BLOCK_GP;
		_MinBlockLevel = 1;
		_MaxBlockLevel = 6;
		_MaxPoolVolume = GetBlockVolume(4);
	}

	Setting::~Setting()
	{
	}

	//----- ----- ----- ----- ----- -----

	uint8 Setting::BlockType()
	{
		return _BlockType;
	}

	uint8 Setting::MinBlockLevel()
	{
		return _MinBlockLevel;
	}

	uint8 Setting::MaxBlockLevel()
	{
		return _MaxBlockLevel;
	}

	uint32 Setting::MaxPoolVolume()
	{
		return _MaxPoolVolume;
	}

	//----- ----- ----- ----- ----- -----

	void Setting::SetBlockType(uint8 value)
	{
		_BlockType = value;
	}

	void Setting::SetMinBlockLevel(uint8 value)
	{
		_MinBlockLevel = value;
	}

	void Setting::SetMaxBlockLevel(uint8 value)
	{
		_MaxBlockLevel = value;
	}

	void Setting::SetMaxPoolVolume(uint32 value)
	{
		_MaxPoolVolume = value;
	}

	//----- ----- ----- ----- ----- -----

	uint32 Setting::MaxBlockCount()
	{
		return _MaxPoolVolume / GetBlockVolume(_MinBlockLevel);
	}

	uint32 Setting::MaxBlockSize()
	{
		return GetBlockVolume(_MaxBlockLevel);
	}
}