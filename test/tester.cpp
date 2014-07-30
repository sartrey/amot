#include "tester.h"

Tester::Tester()
{
}

Tester::~Tester()
{
	_Names.clear();
	_Tests.clear();
}

void Tester::Run()
{
	LARGE_INTEGER freq,t1,t2;
	QueryPerformanceFrequency(&freq);

	for(int i=0; i != _Tests.size(); i++)
	{
		QueryPerformanceCounter(&t1);
		(*((Action)(_Tests[i])))();
		QueryPerformanceCounter(&t2);
		cout<<"[Test: "<<_Names[i].c_str()<<"] ";
		cout<<(t2.QuadPart-t1.QuadPart) * 1000.0 / freq.QuadPart<<"(ms)"<<endl;
	}
}

void Tester::Add(string name, Action action)
{
	_Names.push_back(name);
	_Tests.push_back(action);
}