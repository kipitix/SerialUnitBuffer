#ifndef SERIALUNITBUFFER_H
#define SERIALUNITBUFFER_H

#include <cstring>

class SerialUnitBuffer
{
public:
	SerialUnitBuffer(size_t size = 1024,
					 const char * unitStart = ">>>",
					 const char * unitEnd = "<<<");
	virtual ~SerialUnitBuffer();


	size_t size() const { return _size; }
	char * buffer() const { return _buffer; }

	void append(const char * str);
	void append(char c);

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
