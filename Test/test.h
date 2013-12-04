#include "amot_pool.h"
#include <vector>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::exception;

class Tester
{
public:
	Tester();
	~Tester();
private:
	amot::Pool* _MemPool;
public:
	vector<LPVOID> _Funcs;
	vector<string> _Names;
	typedef void (*PFUNC)(amot::Pool*);
public:
	void Add(string name, PFUNC func);
	void Run();
};

class A : public amot::IDisposable
{
public:
	int _a;
	float _b;
public:
	A()
	{
		_a = 12;
		_b = 24.4;
	}
	bool Dispose()
	{
		_a = 0;
		_b = 0;
		return false;
	}
};

void Test_Optimize(amot::Pool* mp);
void Test_1_1(amot::Pool* mp);
void Test_1_2(amot::Pool* mp);
void Test_1_3(amot::Pool* mp);
void Test_1_4(amot::Pool* mp);
void Test_2_Expand(amot::Pool* mp);
void Test_2_Sign(amot::Pool* mp);
void Test_2_Unsign(amot::Pool* mp);
void Test_2_1(amot::Pool* mp);
void Test_2_2(amot::Pool* mp);
void Test_2_3(amot::Pool* mp);
void Test_3_1(amot::Pool* mp);
void Test_3_2(amot::Pool* mp);