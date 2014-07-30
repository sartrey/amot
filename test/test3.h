#include "amot.h"

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