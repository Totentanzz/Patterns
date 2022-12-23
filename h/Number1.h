#pragma once
#include "Number1Impl.h"

class Number1 {
public:

	Number1(Number1Impl* p);

	virtual ~Number1();

	virtual char* cStr() = 0;

	virtual short compare(void* second) = 0;

	virtual void equalize(void* second) = 0;

	virtual void add(void* added) = 0;

	virtual void subtract(void* subtracted) = 0;

	virtual void multiply(void* factor) = 0;

	virtual void divide(void* divider) = 0;

	virtual void swap(void* second) = 0;


protected:
	Number1Impl* pimpl;
private:
};