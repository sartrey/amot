#include "test1.h"

void Test_1_1()
{
	amot::Setting* setting = new amot::Setting();
	setting->SetMinBlockLevel(4);

	amot::Pool* pool = new amot::Pool();
	for (int j = 0; j < 50; j++)
	{
		for (int i = 0; i < 10000; i++)
		{
			int* p1 = pool->New<int>(3);
			double* p2 = pool->New<double>(7);
			int* p3 = pool->New<int>(15);
			double* p4 = pool->New<double>(7);
			int* p5 = pool->New<int>(290);
			double* p6 = pool->New<double>(7);
			int* p7 = pool->New<int>(3);
			double* p8 = pool->New<double>(7);
			int* p9 = pool->New<int>(3);
			double* p10 = pool->New<double>(7);
			pool->Free(p1);
			pool->Free(p2);
			pool->Free(p3);
			pool->Free(p4);
			pool->Free(p5);
			pool->Free(p6);
			pool->Free(p7);
			pool->Free(p8);
			pool->Free(p9);
			pool->Free(p10);
		}
		pool->Optimize();
	}
	/*
	for (int i = 0; i<3; i++)
		p1[i] = i;
	for (int i = 0; i<7; i++)
		p2[i] = i;
	for (int i = 0; i<15; i++)
		p3[i] = i;
	for (int i = 0; i<7; i++)
		p4[i] = i;
	for (int i = 0; i<290; i++)
		p5[i] = i;
	for (int i = 0; i<7; i++)
		p6[i] = i;
	for (int i = 0; i<3; i++)
		p7[i] = i;
	for (int i = 0; i<7; i++)
		p8[i] = i;
	for (int i = 0; i<3; i++)
		p9[i] = i;
	for (int i = 0; i<7; i++)
		p10[i] = i;
	*/
	delete pool;
}

void Test_1_2()
{
	for (int i = 0; i < 500000; i++)
	{
		int* p1 = new int[3];
		double* p2 = new double[7];
		int* p3 = new int[15];
		double* p4 = new double[7];
		int* p5 = new int[290];
		double* p6 = new double[7];
		int* p7 = new int[3];
		double* p8 = new double[7];
		int* p9 = new int[3];
		double* p10 = new double[7];
		delete[] p1;
		delete[] p2;
		delete[] p3;
		delete[] p4;
		delete[] p5;
		delete[] p6;
		delete[] p7;
		delete[] p8;
		delete[] p9;
		delete[] p10;
	}
}