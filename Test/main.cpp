#include "test.h"

int main()
{
	Tester* tester = new Tester();

	tester->Add("GP_MB alloc/free 1st", Test_1_1);
	tester->Add("GP_MB alloc/free 2st", Test_1_2);
	tester->Add("CRT alloc/free 1st", Test_1_3);
	tester->Add("CRT alloc/free 2st", Test_1_4);

	tester->Add("MP optimize", Test_Optimize);
	
	tester->Add("GP_MB alloc/free 1st", Test_1_1);
	tester->Add("MP optimize", Test_Optimize);
	tester->Add("GP_MB alloc/free 2st", Test_1_2);
	tester->Add("CRT alloc/free 1st", Test_1_3);
	tester->Add("CRT alloc/free 2st", Test_1_4);

	tester->Add("MP optimize", Test_Optimize);

	tester->Add("MP Expand", Test_2_Expand);
	tester->Add("GP_MB alloc/free", Test_2_1);
	tester->Add("CRT alloc/free", Test_2_2);
	tester->Add("MP Sign [320]", Test_2_Sign);
	tester->Add("FL_MB alloc/free", Test_2_1);
	tester->Add("CRT alloc/free", Test_2_2);
	tester->Add("MP Unsign [320]", Test_2_Unsign);

	tester->Add("MP optimize", Test_Optimize);
	tester->Add("MP ctor/dtor", Test_3_1);
	tester->Add("CRT ctor/dtor", Test_3_2);

	tester->Run();
	delete tester;

	system("pause");
	return 0;
}