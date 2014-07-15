#include "amot_setting.h"

namespace amot
{
	Setting::Setting()
	{
		_HasLock = false;
		_BlockType = AMOT_BLOCK_TYPE_GP1;
		_MinBlockLevel = 1;
		_MaxBlockLevel = 11;
		_MaxPoolVolume = GetBlockVolume(2);
	}

	Setting::~Setting()
	{
	}

	bool Setting::HasLock()
	{
		return _HasLock;
	}

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


	void Setting::SetHasLock(bool value)
	{
		_HasLock = value;
	}

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


	uint32 Setting::MaxBlockCount()
	{
		return _MaxPoolVolume / GetBlockVolume(_MinBlockLevel);
	}
}