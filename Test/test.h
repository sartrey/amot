#include "amot.h"
#include <vector>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::exception;

typedef void(*Action)();

class Tester
{
public:
	Tester();
	~Tester();

public:
	vector<void*> _Tests;
	vector<string> _Names;

public:
	void Add(string name, Action action);
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

void Test_1_1();
void Test_1_2();
void Test_1_3();
void Test_1_4();
void Test_2_1();
void Test_2_2();
void Test_2_3();
void Test_3_1();
void Test_3_2();