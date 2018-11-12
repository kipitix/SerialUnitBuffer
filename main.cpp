#include <iostream>

#include <assert.h>

#include "SerialUnitBuffer.h"


using namespace std;

int main()
{
	char buffer[1024];
	char unit[1024];

	{
		SerialUnitBuffer sub(1, buffer, unit);
		assert(sub.size() == 0);
		assert(sub.buffer() == buffer);
	}

	{
		SerialUnitBuffer sub(10, buffer, unit);
		assert(sub.size() == 9);
		assert(sub.buffer() == buffer);
		assert(*sub.buffer() == 0);
	}

	{
		SerialUnitBuffer sub(3, buffer, unit);
		sub.append('x');
		assert(strcmp(sub.buffer(), "x") == 0);
		sub.append('y');
		assert(strcmp(sub.buffer(), "xy") == 0);
		sub.append('z');
		assert(strcmp(sub.buffer(), "yz") == 0);
	}

	{
		SerialUnitBuffer sub(11, buffer, unit);
		sub.append("xxxxx");
		assert(strcmp(sub.buffer(), "xxxxx") == 0);
		sub.append("yyyyyy");
		assert(strcmp(sub.buffer(), "xxxxyyyyyy") == 0);
		sub.append("zzz");
		assert(strcmp(sub.buffer(), "xyyyyyyzzz") == 0);
		sub.append("abcdefghijklmnopqrstuvwxyz");
		assert(strcmp(sub.buffer(), "abcdefghij") == 0);
	}

	{
		SerialUnitBuffer sub(1024, buffer, unit, ">>>", "<<<");

		sub.append(">>>x<<<");
		assert(strcmp(sub.goToNextUnit(), "x") == 0);
		assert(strcmp(sub.nextUnit(), "x") == 0);
		assert(strcmp(sub.buffer(), "") == 0);

		sub.append(">>>x");
		assert(sub.goToNextUnit() == NULL);
		assert(sub.nextUnit() == NULL);
		assert(strcmp(sub.buffer(), ">>>x") == 0);

		sub.append("<<<");
		assert(strcmp(sub.goToNextUnit(), "x") == 0);
		assert(strcmp(sub.nextUnit(), "x") == 0);
		assert(strcmp(sub.buffer(), "") == 0);

		sub.append(">>>x<<<>>>y<<<");
		assert(strcmp(sub.goToNextUnit(), "x") == 0);
		assert(strcmp(sub.nextUnit(), "x") == 0);

		assert(strcmp(sub.buffer(), ">>>y<<<") == 0);
		assert(strcmp(sub.goToNextUnit(), "y") == 0);
		assert(strcmp(sub.nextUnit(), "y") == 0);
		assert(strcmp(sub.buffer(), "") == 0);
	}


	cout << "OK!" << endl;
	return 0;
}
