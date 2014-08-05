#pragma once
 
#include "amot_base.h"

namespace amot
{
	class AMOT_API Setting
	{
	private:
		uint8 _BlockType;
		uint8 _MinBlockLevel;
		uint8 _MaxBlockLevel;
		uint32 _MaxPoolVolume;

	public:
		Setting();
		~Setting();

	public:
		//get block type
		uint8 BlockType();

		//get min block level
		uint8 MinBlockLevel();

		//get max block level
		uint8 MaxBlockLevel();
		
		//get max pool volume
		uint32 MaxPoolVolume();

	public:
		//set block type
		void SetBlockType(uint8 value);

		//set min block level
		void SetMinBlockLevel(uint8 value);

		//set max block level
		void SetMaxBlockLevel(uint8 value);

		//set max pool volume
		void SetMaxPoolVolume(uint32 value);

	public:
		//get max block count
		uint32 MaxBlockCount();

		//get max block size
		uint32 MaxBlockSize();
	};
}