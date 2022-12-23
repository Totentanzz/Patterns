#pragma once
#include "Number1.h"
#include "Array.h"
#include "BigInt1Impl.h"

class BigInt1 : public Number1
{
public:
	BigInt1();

	virtual ~BigInt1();

	BigInt1(long long value);

	BigInt1(const BigInt1& object);

	BigInt1(char* valStr);

	BigInt1(const char* valStr);

	char* cStr();

	short compare(void* second);

	void equalize(void* second);

	void add(void* added);

	void subtract(void* subtracted);

	void multiply(void* facotr);

	void divide(void* divider);

	void swap(void* second);

private:
};

