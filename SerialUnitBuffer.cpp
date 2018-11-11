#include "SerialUnitBuffer.h"


SerialUnitBuffer::SerialUnitBuffer(size_t size,
								   const char * unitStart,
								   const char * unitEnd)
	: _size(size)
	, _buffer(0)
	, _unit(0)
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
	if (_buffer != 0)
	{
		delete [] _buffer;
	}

	if (_unit != 0)
	{
		delete [] _unit;
	}
}


void SerialUnitBuffer::append(char c)
{
	char * tmp = new char[2]; // char and zero end
	tmp[0] = c;
	tmp[1] = 0;
	append(tmp);
	delete [] tmp;
}


void SerialUnitBuffer::append(const char * str)
{
	if (_buffer == 0)
	{
		return;
	}

	size_t currentSize = strlen(_buffer);
	size_t strSize = strlen(str);
	if (strSize > _size)
	{
		strSize = _size;
	}

	if (currentSize >= _size)
	{
		memmove(_buffer, _buffer + strSize, _size - strSize + 1);
	}

	if (_size < _maxSize)
	{
		_buffer[_size] = c;
		_size ++;
		_buffer[_size] = 0;
	}

	size_t appSize = strlen(str);
	if (_size + appSize <= _maxSize)
	{
		strcat(_buffer, str);
		_size = strlen(_buffer);
		return true;
	}

	return false;
}

