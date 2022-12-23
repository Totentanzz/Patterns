#pragma once
#include "Array.h"

class Number1Impl
{
public:

	virtual ~Number1Impl();

	virtual short getSign() = 0;

	virtual void setSign(short newSign) = 0;

	virtual Array<long long>* getArray() = 0;

protected:

	friend class BigInt1;

	Array<long long> array;
	short sign;
	const static int BASE = 1000000000;

	virtual int countDigits(long long value) = 0;

};

