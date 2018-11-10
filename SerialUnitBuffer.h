#ifndef SERIALUNITBUFFER_H
#define SERIALUNITBUFFER_H

#include <string.h>

class SerialUnitBuffer
{
public:
	SerialUnitBuffer(size_t maxSize = 1024,
					 const char * unitStart = ">>>",
					 const char * unitEnd = "<<<");
	virtual ~SerialUnitBuffer();


	size_t maxSize() const { return _maxSize; }
	size_t size() const { return _size; }
	const char * buffer() const { return _buffer; }

	bool append(char c);
	bool append(const char * str);


private:
	size_t _maxSize;
	size_t _size;
	char * _buffer;

	const char * _unitStart;
	const char * _unitEnd;
};

#endif // SERIALUNITBUFFER_H
