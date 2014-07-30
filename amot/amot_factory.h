#pragma once

#include "amot_base.h"

namespace amot
{
	class Block;
	typedef Block* PBlock;

	class AMOT_API Factory
	{
	public:
		Factory();
		~Factory();

	public:
		PBlock CreateBlock(int type, uint8 level);
	};
}