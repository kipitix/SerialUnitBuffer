#include "SerialUnitBuffer.h"


SerialUnitBuffer::SerialUnitBuffer(size_t maxSize)
	: _maxSize(maxSize)
	, _size(0)
	, _buffer(0)
{
	if (_maxSize > 0)
	{
		_buffer = new char[_maxSize + 1]; // +1 for zero char
		_buffer[0] = 0;
	}
}


SerialUnitBuffer::~SerialUnitBuffer()
{
	if (_maxSize > 0)
	{
		delete [] _buffer;
	}
}


bool SerialUnitBuffer::append(char c)
{
	if (_size < _maxSize)
	{
		_buffer[_size] = c;
		_size ++;
		_buffer[_size] = 0;
		return true;
	}

	return false;
}


bool SerialUnitBuffer::append(const char * str)
{
	size_t appSize = strlen(str);
	if (_size + appSize <= _maxSize)
	{
		strcat(_buffer, str);
		_size = strlen(_buffer);
		return true;
	}

	return false;
}

