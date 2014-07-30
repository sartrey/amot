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