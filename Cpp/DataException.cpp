#define _CRT_SECURE_NO_WARNINGS

#include "DataException.h"
#include <iostream>
#include <string>

#define DigitMaxSize 20

using namespace std;

DataException::DataException(const char* arg, long long errorData)
	: exception(arg) {
	size = 1;
	data = new long long[size];
	data[0] = errorData;
}

DataException::DataException(const char* arg, int amount, long long errorData1, ...)
	: exception(arg) {
	size = amount;
	data = new long long[size];
	long long* p = &errorData1;
	for (size_t i=0; amount > 0; i++, p++, amount--) {
		data[i] = *p;
	}
}

DataException::DataException(const DataException& other)
	: exception(other) {
	size = other.size;
	data = new long long[size];
	memcpy(data, other.data, size*sizeof(long long));
}

DataException::~DataException() {
	delete[] data;
}

const char* DataException::whatData() const {
	string dataStr;
	for (size_t i = 0; i < this->size;++i) {
		dataStr.append(to_string(this->data[i]));
		if (i + 1 != this->size) dataStr.append(", ");
	}
	int cStrSize = dataStr.size() + 1;
	char* cStr = new char[cStrSize * sizeof(char)];
	memcpy(cStr, dataStr.c_str(), cStrSize * sizeof(char));
	return const_cast<const char*>(cStr);
}