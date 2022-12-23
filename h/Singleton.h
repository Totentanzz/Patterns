#pragma once
#include "Array.h"

class Singleton
{
public:

	static Singleton* instanceT();

	Array<long long> getArr();

	int getSize();

	int getElemNum();

	void addToEnd(long long value);

	void insertByIndex(long long value, int index);

	void deleteByIndex(int index);

	long long& getByIndex(int index);

	const char* cStr();

	~Singleton();

protected:

	Singleton();

private:
	static Singleton* instance;
	Array<long long>* arr;
};

