#include <iostream>

#include <assert.h>

#include "SerialUnitBuffer.h"


using namespace std;

int main()
{
	{
		SerialUnitBuffer sub(0);
		assert(sub.size() == 0);
		assert(sub.maxSize() == 0);
		assert(sub.buffer() == 0);
	}

	{
		SerialUnitBuffer sub(10);
		assert(sub.size() == 0);
		assert(sub.maxSize() == 10);
		assert(sub.buffer() != 0);
		assert(*sub.buffer() == 0);
	}

	{
		SerialUnitBuffer sub(2);
		assert(sub.append('x') == true);
		assert(sub.append('y') == true);
		assert(sub.append('z') == false);
	}

	{
		SerialUnitBuffer sub(10);
		assert(sub.append("xxxxx") == true);
		assert(sub.append("yyyyy") == true);
		assert(sub.append("z") == false);
	}


	cout << "OK!" << endl;
	return 0;
}
