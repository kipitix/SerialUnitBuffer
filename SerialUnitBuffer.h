#ifndef SERIALUNITBUFFER_H
#define SERIALUNITBUFFER_H

#include <string.h>

class SerialUnitBuffer
{
public:
	SerialUnitBuffer(size_t size = 1024,
					 char * buffer = NULL,
					 char * unit = NULL,
					 const char * unitStart = ">>>",
					 const char * unitEnd = "<<<",
				 	 bool deleteBuffers = false);
	virtual ~SerialUnitBuffer();


	size_t size() const { return _size; }
	char * buffer() const { return _buffer; }

	void append(const char * str);
	void append(char c);

	char * goToNextUnit();
	char * nextUnit() const { return (strlen(_unit) > 0 ? _unit : NULL); }

private:
	size_t _size;
	char * _buffer;
	char * _unit;

	const char * _unitStart;
	const char * _unitEnd;

	bool _deleteBuffers;

	char _tmp[2];
};

#endif // SERIALUNITBUFFER_H
