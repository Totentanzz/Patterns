#pragma once
#include "Number1Impl.h"
#include "Array.h"

class BigInt1Impl : public Number1Impl
{
public:

	short getSign();

	void setSign(short newSign);

	Array<long long>* getArray();

protected:

	int countDigits(long long value);
};

