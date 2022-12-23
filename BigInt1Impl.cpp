#define _CRT_SECURE_NO_WARNINGS

#include "BigInt1Impl.h"

short BigInt1Impl::getSign() {
	return sign;
}

void BigInt1Impl::setSign(short newSign) {
	if (newSign < -1 || newSign == 0 || newSign > 1)
		throw std::invalid_argument("Exception: invalid sign");
	sign = newSign;
}

Array<long long>* BigInt1Impl::getArray() {
	return &this->array;
}

int BigInt1Impl::countDigits(long long value) {
	int digits = 0;
	if (value == 0 || value < 0) digits++;
	while (value != 0) {
		digits++;
		value /= 10;
	}
	return digits;
}