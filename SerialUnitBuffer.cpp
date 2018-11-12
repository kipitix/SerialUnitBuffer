#include "SerialUnitBuffer.h"

SerialUnitBuffer::SerialUnitBuffer(size_t size,
								   char * buffer,
								   char * unit,
								   const char * unitStart,
								   const char * unitEnd,
								   bool deleteBuffers)
	: _size(size - 1)
	, _buffer(buffer)
	, _unit(unit)
	, _unitStart(unitStart)
	, _unitEnd(unitEnd)
	, _deleteBuffers(deleteBuffers)
{
	if (_buffer != NULL)
	{
		_buffer[0] = 0;
	}

	if (_unit != NULL)
	{
		_unit[0] = 0;
	}
}


SerialUnitBuffer::~SerialUnitBuffer()
{
	if (_deleteBuffers)
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
		memcpy(_buffer, _buffer + shift, _size - shift + 1);
	}

	curSize = strlen(_buffer);
	memcpy(_buffer + curSize, str, strSize);
	_buffer[curSize + strSize] = 0;
}


void SerialUnitBuffer::append(char c)
{
	_tmp[0] = c;
	_tmp[1] = 0;
	append(_tmp);
}


char * SerialUnitBuffer::goToNextUnit()
{
	if (_buffer == NULL
		|| _unit == NULL
		|| _unitStart == NULL
		|| _unitEnd == NULL)
	{
		return NULL;
	}

	_unit[0] = 0;

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
	memcpy(_unit, start + startSize, unitSize);
	_unit[unitSize] = 0;

	memcpy(_buffer, end + endSize, strlen(end + endSize) + 1);

	return _unit;
}
