#define _CRT_SECURE_NO_WARNINGS

#include "BigInt1.h"

BigInt1::BigInt1() : Number1(new BigInt1Impl) {
	this->pimpl->sign = 1;
}

BigInt1::BigInt1(long long value) : Number1(new BigInt1Impl) {
	this->pimpl->sign = 1;
	if (value < 0) {
		this->pimpl->sign = -1;
		value *= this->pimpl->sign;
	}
	if (value == 0) {
		this->pimpl->array.addToEnd(0);
	}
	else {
		long long digits = this->pimpl->countDigits(value);
		long long cells = (digits % 9) == 0 ? (digits / 9) : (digits / 9 + 1);
		this->pimpl->array.makeEqualSize(this->pimpl->array.getSize(), cells);
		for (int i = cells - 1; i >= 0; i--) {
			this->pimpl->array.insertByIndex(value % this->pimpl->BASE, i);
			value /= this->pimpl->BASE;
		}
	}
}

BigInt1::BigInt1(char* valStr) : Number1(new BigInt1Impl) {
	long long len = 0, cells, totalDig;
	if (valStr[0] == '-') {
		this->pimpl->sign = -1;
		valStr++;
		len++;
	}
	else  this->pimpl->sign = 1;
	for (; valStr[len] != '\0' && valStr[len] != '\n'; len++) {
		if (valStr[len] < 48 || valStr[len]>57)
			throw std::invalid_argument("BigInt1 constuctor: invalid string");
	}
	cells = ((len % 9) == 0) ? (len / 9) : (len / 9 + 1);
	totalDig = len;
	this->pimpl->array.makeEqualSize(this->pimpl->array.getSize(), cells);
	for (int i = 0, j = 0; i < len; j++) {
		char digStr[10] = { 0 };
		int digAmount = ((totalDig % 9) == 0) ? 9 : (totalDig % 9);
		memcpy(digStr, valStr + i, digAmount);
		this->pimpl->array.insertByIndex(_atoi64(digStr), j);
		i += digAmount;
		totalDig -= digAmount;
	}
}

BigInt1::BigInt1(const char* valStr) : BigInt1((char*)valStr) {
}

BigInt1::BigInt1(const BigInt1& object) : Number1(new BigInt1Impl) {
	this->pimpl->array = object.pimpl->array;
	this->pimpl->sign = object.pimpl->sign;
}

BigInt1::~BigInt1() {
}

char* BigInt1::cStr() {
	int arrSize = this->pimpl->array.getSize();
	int cStrSize = arrSize * 9 + 2;
	char* cStr = new char[cStrSize];
	cStr[0] = this->pimpl->sign == -1 ? '-' : '+';
	int digits, nulAmount;
	size_t i = 1, j = 0;
	for (; i < cStrSize && j < arrSize; i++, j++) {
		long long curNum = this->pimpl->array.getByIndex(j);
		digits = this->pimpl->countDigits(curNum);
		nulAmount = (j > 0) ? (9 - digits) : 0;
		_i64toa(curNum, cStr + i + nulAmount, 10);
		memset(cStr + i, '0', nulAmount);
		i += (j > 0) ? 8 : (digits - 1);
	}
	return cStr;
}

short BigInt1::compare(void* second) {
	short state;
	BigInt1* secondBI = (BigInt1*)second;
	if (this->pimpl->array.getElmNum() > secondBI->pimpl->array.getElmNum())
		state = 1;
	else if (this->pimpl->array.getElmNum() == secondBI->pimpl->array.getElmNum()) {
		state = 0;
		int size1 = this->pimpl->array.getSize();
		int size2 = secondBI->pimpl->array.getSize();
		for (int i = 0; i < size1 && (state != 2 && state != -2); i++) {
			long long curElem = this->pimpl->array.getByIndex(i);
			long long secondElem = i < size2 ? secondBI->pimpl->array.getByIndex(i) : 0;
			if (curElem > secondElem)
				state = 2;
			else if (curElem < secondElem)
				state = -2;
		}
	}
	else state = -1;
	return state;
}

void BigInt1::equalize(void* second) {
	short state = compare(second);
	BigInt1* secondBI = (BigInt1*)second;
	int elemNum1 = this->pimpl->array.getElmNum();
	int elemNum2 = secondBI->pimpl->array.getElmNum();
	if (state == 1) {
		while (elemNum2 < elemNum1) {
			this->pimpl->array.makeEqualSize(this->pimpl->array.getSize(), secondBI->pimpl->array.getSize()); //
			secondBI->pimpl->array.shiftSliceR(0);
			secondBI->pimpl->array.insertByIndex(0, 0);
			elemNum2++;
		}
	}
	else if (state == -1) {
		while (elemNum1 < elemNum2) {
			this->pimpl->array.makeEqualSize(this->pimpl->array.getSize(), secondBI->pimpl->array.getSize()); //
			this->pimpl->array.shiftSliceR(0);
			this->pimpl->array.insertByIndex(0, 0);
			elemNum1++;
		}
	}
}

void BigInt1::add(void* added) {
	BigInt1* secondBi = (BigInt1*)added;
	long long rest = 0, result = 0;
	if (this->pimpl->sign == 1 && secondBi->pimpl->sign == -1) {
		this->pimpl->sign *= -1;
		subtract(added);
		this->pimpl->sign *= -1;
	}
	else if (this->pimpl->sign == -1 && secondBi->pimpl->sign == 1) {
		this->pimpl->sign *= -1;
		subtract(added);
		this->pimpl->sign *= -1;
	}
	else {
		this->equalize(added);
		for (int i = this->pimpl->array.getElmNum() - 1, j = i; i >= 0; i--, j--) {
			long long curElem = this->pimpl->array.getByIndex(i);
			long long addedElem = j >= 0 ? secondBi->pimpl->array.getByIndex(i) : 0;
			result = curElem + addedElem + rest;
			rest = result >= this->pimpl->BASE ? 1 : 0;
			result -= rest > 0 ? this->pimpl->BASE : 0;
			this->pimpl->array.deleteByIndex(i);
			this->pimpl->array.insertByIndex(result, i);
			if (rest && this->pimpl->array.getElmNum() == this->pimpl->array.getSize() && i == 0) {
				this->pimpl->array.shiftSliceR(i++);
				this->pimpl->array.insertByIndex(0, 0);
			}
		}
	}
}

void BigInt1::subtract(void* subtracted) {
	BigInt1* secondBi = (BigInt1*)subtracted;
	long long rest = 0, result = 0;
	if (this->pimpl->sign == -1 && secondBi->pimpl->sign == 1) {
		this->pimpl->sign *= -1;
		add(subtracted);
		this->pimpl->sign *= -1;
	}
	else if (this->pimpl->sign == 1 && secondBi->pimpl->sign == -1) {
		this->pimpl->sign *= -1;
		add(subtracted);
		this->pimpl->sign *= -1;
	}
	else {
		this->equalize(subtracted);
		if (this->compare(subtracted) == -2) {
			this->swap(subtracted);
			this->pimpl->sign = -1;
		}
		for (int i = this->pimpl->array.getElmNum() - 1; i >= 0; i--) {
			long long curElem = this->pimpl->array.getByIndex(i);
			long long subElem = secondBi->pimpl->array.getByIndex(i);
			result = curElem - subElem - rest;
			rest = result < 0 ? 1 : 0;
			result += rest > 0 ? this->pimpl->BASE : 0;
			this->pimpl->array.deleteByIndex(i);
			this->pimpl->array.insertByIndex(result, i);
		}
	}
}

void BigInt1::multiply(void* factor) {
	BigInt1* secondBi = (BigInt1*)factor;
	BigInt1 bigMult;
	if (secondBi->pimpl->array.isEmpty() || this->pimpl->array.isEmpty()) {
		bigMult.pimpl->array.addToEnd(0);
		this->swap(&bigMult);
	}
	else {
		int thisLen = this->pimpl->array.getSize();
		int factorLen = secondBi->pimpl->array.getSize();
		long long resLen = thisLen + factorLen + 1, resMult = 0, rest = 0;
		bigMult.pimpl->array.makeEqualSize(resLen, bigMult.pimpl->array.getSize());
		for (int i = thisLen - 1; i >= 0; i--) {
			long long curElem = this->pimpl->array.getByIndex(i);
			for (int j = factorLen - 1; j >= 0 || rest > 0; j--) {
				long long factorElem = (j >= 0) ? secondBi->pimpl->array.getByIndex(j) : 0;
				long long resElem = bigMult.pimpl->array.getByIndex(i + j + 2);
				resMult = resElem + (curElem * factorElem) + rest;
				if (resElem == 0 && resMult != 0)
					bigMult.pimpl->array.insertByIndex(resMult % this->pimpl->BASE, i + j + 2);
				else if (resElem != 0) {
					bigMult.pimpl->array.deleteByIndex(i + j + 2);
					bigMult.pimpl->array.insertByIndex(resMult % this->pimpl->BASE, i + j + 2);
				}
				rest = resMult >= this->pimpl->BASE ? resMult /= this->pimpl->BASE : 0;
			}
		}
		while (bigMult.pimpl->array.getByIndex(0) == 0) {
			bigMult.pimpl->array.shiftSliceL(0);
			bigMult.pimpl->array.reduceCap(1);
		}
		bigMult.pimpl->sign = (this->pimpl->sign == secondBi->pimpl->sign) ? 1 : -1;
		this->swap(&bigMult);
	}
}

void BigInt1::divide(void* divider) {
	BigInt1* secondBi = (BigInt1*)divider;
	BigInt1 result, curDivr(*secondBi);
	curDivr.pimpl->sign = 1;
	if (curDivr.pimpl->array.isEmpty())
		throw std::invalid_argument("divide: division by zero");
	if (this->compare(&curDivr) < 0) {
		result.pimpl->array.addToEnd(0);
		this->swap(&result);
		return;
	}
	result.pimpl->array.makeEqualSize(result.pimpl->array.getSize(), this->pimpl->array.getSize());
	BigInt1 curDividend(result);
	for (int i = 0, j = 0; i < this->pimpl->array.getSize(); i++, j++) {
		long long curElem = this->pimpl->array.getByIndex(i);
		curDividend.pimpl->array.insertByIndex(curElem, j);
		long long curFactor = 0, left = 0, right = this->pimpl->BASE;
		while (left <= right) {
			long long mid = (left + right) / 2;
			BigInt1 tmp(mid);
			tmp.multiply(&curDivr);
			if (tmp.compare(&curDividend) <= 0) {
				curFactor = mid;
				left = mid + 1;
			}
			else right = mid - 1;
		}
		result.pimpl->array.insertByIndex(curFactor, i);
		BigInt1 tmpFactor(curFactor);
		tmpFactor.multiply(&curDivr);
		curDividend.subtract(&tmpFactor);
		while (curDividend.pimpl->array.getByIndex(0) == 0) {
			if (curDividend.pimpl->array.getElmNum() == 0) break;
			curDividend.pimpl->array.deleteByIndex(0);
			curDividend.pimpl->array.shiftSliceL(0);
			j--;
		}
	}
	while (result.pimpl->array.getByIndex(0) == 0) {
		result.pimpl->array.shiftSliceL(0);
		result.pimpl->array.reduceCap(1);
	}
	result.pimpl->sign = (this->pimpl->sign == secondBi->pimpl->sign) ? 1 : -1;
	this->swap(&result);
}

void BigInt1::swap(void* second) {
	BigInt1* secondBi = (BigInt1*)second;
	Array<long long>::swapArray(this->pimpl->array, secondBi->pimpl->array);
	short tmpSign = this->pimpl->sign;
	this->pimpl->sign = secondBi->pimpl->sign;
	secondBi->pimpl->sign = tmpSign;
}