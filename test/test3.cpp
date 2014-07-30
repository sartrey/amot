/*
void Test_3_1(amot::Pool* mp)
{
	A* obj = NULL;
	for (int i = 0; i<10000; i++)
	{
		obj = mp->Alloc<A>(100, true);
		mp->Dispose(obj);
		mp->Free(obj);
	}
}

void Test_3_2(amot::Pool* mp)
{
	for (int i = 0; i<10000; i++)
	{
		A* obj = new A[100];
		delete[] obj;
	}
}
*/