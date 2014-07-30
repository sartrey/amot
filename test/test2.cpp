#include "test2.h"

void Test_2_1()
{
	amot::Pool* pool = new amot::Pool();
	
	amot::Factory* factory = pool->Factory();
	amot::Block* block = factory->CreateBlock(amot::AMOT_BLOCK_FL, 4);
	amot::IBlockFL* block_prop = dynamic_cast<amot::IBlockFL*>(block);
	block_prop->SetUnit(300);
	block->Reset();

	pool->Mount(block);
	
	for (int i = 0; i < 50000; i++)
	{
		byte** pp = pool->New<byte*>(75);
		for (int i = 0; i < 75; i++)
			pp[i] = pool->New<byte>(300);
		for (int i = 0; i < 75; i++)
			pool->Free(pp[i]);
		pool->Free(pp);
	}
}

void Test_2_2()
{
	for (int i = 0; i < 50000; i++)
	{
		byte** pp = new byte*[75];
		for (int i = 0; i < 75; i++)
			pp[i] = new byte[300];
		for (int i = 0; i < 75; i++)
			delete[] pp[i];
		delete[] pp;
	}
}
