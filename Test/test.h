#include "mem_pool.h"
#include <vector>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::exception;

using namespace mempool;

class Tester
{
public:
	Tester();
	~Tester();
private:
	MemoryPool* _MemPool;
public:
	vector<LPVOID> _Funcs;
	vector<string> _Names;
	typedef void (*PFUNC)(MemoryPool*);
public:
	void Add(string name, PFUNC func);
	void Run();
};

class A : public IDisposable
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

void Test_Optimize(MemoryPool* mp);
void Test_1_1(MemoryPool* mp);
void Test_1_2(MemoryPool* mp);
void Test_1_3(MemoryPool* mp);
void Test_1_4(MemoryPool* mp);
void Test_2_Expand(MemoryPool* mp);
void Test_2_Sign(MemoryPool* mp);
void Test_2_Unsign(MemoryPool* mp);
void Test_2_1(MemoryPool* mp);
void Test_2_2(MemoryPool* mp);
void Test_2_3(MemoryPool* mp);
void Test_3_1(MemoryPool* mp);
void Test_3_2(MemoryPool* mp);