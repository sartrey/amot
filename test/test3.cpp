#include "test3.h"

void Test_3_1()
{
	amot::Pool* pool = new amot::Pool();
	A* obj = NULL;
	for (int i = 0; i < 10000; i++)
	{
		obj = pool->New<A>(100, true);
		pool->Dispose(obj);
	}
}

void Test_3_2()
{
	for (int i = 0; i < 10000; i++)
	{
		A* obj = new A[100];
		delete[] obj;
	}
}