#ifndef SERIALUNITBUFFER_H
#define SERIALUNITBUFFER_H

#include <string.h>

class SerialUnitBuffer
{
public:
	SerialUnitBuffer(size_t size = 1024,
					 const char * unitStart = ">>>",
					 const char * unitEnd = "<<<");
	virtual ~SerialUnitBuffer();


	size_t size() const { return _size; }
	char * buffer() const { return _buffer; }

	void append(char c);
	void append(const char * str);

	bool nextUnitExist() const;
	char * goToNextUnit();

	char * nextUnit() const { return _unit; }

private:
	size_t _size;
	char * _buffer;
	char * _unit;

	const char * _unitStart;
	const char * _unitEnd;
};

#endif // SERIALUNITBUFFER_H
