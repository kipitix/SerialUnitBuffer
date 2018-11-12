#include "SerialUnitBuffer.h"


SerialUnitBuffer::SerialUnitBuffer(size_t size,
								   const char * unitStart,
								   const char * unitEnd)
	: _size(size)
	, _buffer(NULL)
	, _unit(NULL)
	, _unitStart(unitStart)
	, _unitEnd(unitEnd)
{
	if (_size > 0)
	{
		_buffer = new char[_size + 1]; // +1 for zero char
		_buffer[0] = 0; // End of string
	}
}


SerialUnitBuffer::~SerialUnitBuffer()
{
	if (_buffer != NULL)
	{
		delete [] _buffer;
	}

	if (_unit != NULL)
	{
		delete [] _unit;
	}
}


void SerialUnitBuffer::append(const char * str)
{
	if (_buffer == NULL)
	{
		return;
	}

	size_t curSize = strlen(_buffer);
	size_t strSize = strlen(str);

	if (strSize == 0)
	{
		return;
	}

	if (strSize > _size)
	{
		strSize = _size;
	}

	if (curSize + strSize >= _size)
	{
		size_t shift = curSize + strSize - _size;
		memmove(_buffer, _buffer + shift, _size - shift + 1);
	}

	strncat(_buffer, str, strSize);
}


void SerialUnitBuffer::append(char c)
{
	char * tmp = new char[2]; // char and zero end
	tmp[0] = c;
	tmp[1] = 0;
	append(tmp);
	delete [] tmp;
}


char * SerialUnitBuffer::goToNextUnit()
{
	if (_buffer == NULL
			|| _unitStart == NULL
			|| _unitEnd == NULL)
	{
		return NULL;
	}

	if (_unit != NULL)
	{
		delete [] _unit;
		_unit = NULL;
	}

	char * start = strstr(_buffer, _unitStart);
	char * end = strstr(_buffer, _unitEnd);
	size_t startSize = strlen(_unitStart);
	size_t endSize = strlen(_unitEnd);

	if (start == NULL
			|| end == NULL
			|| end < start)
	{
		return NULL;
	}

	size_t unitSize = end - start - startSize;

	_unit = new char[unitSize + 1];
	_unit[unitSize] = 0;

	strncpy(_unit, start + startSize, unitSize);

	memmove(_buffer, end + endSize, strlen(end + endSize) + 1);

	return _unit;
}
