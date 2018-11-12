#include <iostream>

#include <assert.h>

#include "SerialUnitBuffer.h"


using namespace std;

int main()
{
	{
		SerialUnitBuffer sub(0);
		assert(sub.size() == 0);
		assert(sub.buffer() == NULL);
	}

	{
		SerialUnitBuffer sub(10);
		assert(sub.size() == 10);
		assert(sub.buffer() != NULL);
		assert(*sub.buffer() == 0);
	}

	{
		SerialUnitBuffer sub(2);
		sub.append('x');
		assert(strcmp(sub.buffer(), "x") == 0);
		sub.append('y');
		assert(strcmp(sub.buffer(), "xy") == 0);
		sub.append('z');
		assert(strcmp(sub.buffer(), "yz") == 0);
	}

	{
		SerialUnitBuffer sub(10);
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
		SerialUnitBuffer sub(1024, ">>>", "<<<");

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
