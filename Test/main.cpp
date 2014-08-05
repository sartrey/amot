#include "tester.h"
#include "test1.h"
#include "test2.h"

int main()
{
	Tester* tester = new Tester();

	//tester->Add("Pool_GP1 alloc/free", Test_1_1);
	//tester->Add("CRT alloc/free", Test_1_2);

	tester->Add("Pool_FL1 alloc/free", Test_2_1);
	//tester->Add("CRT alloc/free", Test_2_2);
	
	/*
	tester->Add("MP optimize", Test_Optimize);
	tester->Add("MP ctor/dtor", Test_3_1);
	tester->Add("CRT ctor/dtor", Test_3_2);
	*/

	tester->Run();
	delete tester;

	system("pause");
	return 0;
}