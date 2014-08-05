#include "amot.h"

class A : public amot::IObject
{
public:
	int _a;
	float _b;

public:
	void New()
	{
		_a = 12;
		_b = 24.4f;
	}

	bool Dispose()
	{
		_a = 0;
		_b = 0;
		return false;
	}
};

void Test_3_1();
void Test_3_2();