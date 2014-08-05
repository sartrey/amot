#include "test4.h"

void Test_4_1()
{
	amot::Pool* pool = new amot::Pool();
	int* data1 = pool->New<int>(4);
	int* data2 = pool->New<int>(3);
	int* data3 = pool->New<int>(2);
	for (int i = 0; i < 4; i++)
		data1[i] = 1;
	for (int i = 0; i < 3; i++)
		data2[i] = 2;
	for (int i = 0; i < 2; i++)
		data3[i] = 3;
	int* data11 = (int*)pool->Resize(data1, 2 * sizeof(int));
	int* data33 = (int*)pool->Resize(data3, 4 * sizeof(int));
	int* data22 = (int*)pool->Resize(data2, 4 * sizeof(int));
	delete pool;
}

void Test_4_2()
{
	amot::Pool* pool = new amot::Pool();
	for (int i = 0; i < 50000; i++)
	{
		int* data1 = pool->New<int>(4);
		int* data2 = pool->New<int>(3);
		int* data3 = pool->New<int>(2);
		data1 = (int*)pool->Resize(data1, 2 * sizeof(int));
		data2 = (int*)pool->Resize(data2, 4 * sizeof(int));
		data3 = (int*)pool->Resize(data3, 4 * sizeof(int));
		pool->Free(data1);
		pool->Free(data2);
		pool->Free(data3);
	}
	delete pool;
}

void Test_4_3()
{
	for (int i = 0; i < 50000; i++)
	{
		int* data1 = new int[4];
		int* data2 = new int[3];
		int* data3 = new int[2];

		int* data11 = new int[2];
		int* data22 = new int[4];
		int* data33 = new int[4];

		memcpy(data11, data1, 2 * sizeof(int));
		memcpy(data22, data2, 3 * sizeof(int));
		memcpy(data33, data3, 2 * sizeof(int));

		delete data1;
		delete data2;
		delete data3;

		delete data11;
		delete data22;
		delete data33;
	}
}