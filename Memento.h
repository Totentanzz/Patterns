#pragma once
#include "Array.h"

class Memento
{
public:

	Memento(Array<long long> arr, short sign);
private:
	friend class BigInt;
	Array<long long> ar;
	short si;
};

