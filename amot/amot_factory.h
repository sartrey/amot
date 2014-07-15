#pragma once

#include "amot_base.h"

namespace amot
{
	class Block;

	class AMOT_API Factory
	{
	private:
		static Factory* _Instance;
	public:
		static Factory* Instance();

	private:
		Factory();
	public:
		~Factory();

	public:
		Block* CreateBlock(uint8 type, uint32 level);
	};
}