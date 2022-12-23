#pragma once
#include "List.h"
#include "DataException.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Класс Array (массив), который является наследником класса List и наследуется классами
//Stack и Queue
template<typename type>
class Array : public List<type> {
public:

	Array() {
		size = 1;
		elemNum = 0;
		arr = new type[size];
		init(elemNum);
	}

	Array(int N) {
		if (N < 0)
			throw length_error("Array constructor: size N is negative");
		size = N;
		elemNum = 0;
		arr = size > 0 ? new type[size] : nullptr;
		init(elemNum);
	}

	Array(const Array& object) {
		size = object.size;
		elemNum = object.elemNum;
		arr = size > 0 ? new type[size] : nullptr;
		memcpy(arr, object.arr, size * sizeof(type));
	}

	virtual ~Array() {
		delete[] arr;
	}

	int getSize() override {
		return size;
	}

	int getElmNum() override {
		return elemNum;
	}
	
	type* getArr() override {
		type* arrCpy = size > 0 ? new type[size] : nullptr;
		memcpy(arrCpy, arr, size * sizeof(type));
		return arrCpy;
	}

	void reduceCap(int amount) {
		if (amount < 0 || amount >= size)
			throw length_error("reduceCap: amount is negative");
		int newSize = size - amount;
		type* arrCpy = newSize > 0 ? new type[newSize] : nullptr;
		memcpy(arrCpy, arr, newSize * sizeof(type));
		delete[] arr;
		arr = arrCpy;
		size = newSize;
		elemNum = size < elemNum ? size : elemNum;
	}

	void makeEqualSize(int size1, int size2) {
		int maxSize = size1 < size2 ? size2 : size1;
		int oldSize = size;
		if (maxSize < oldSize)
			throw DataException("makeEqualSize: maxSize is less than oldSize", maxSize);
		type* arrCpy = new type[maxSize];
		memcpy(arrCpy, arr, oldSize * sizeof(type));
		delete[] arr;
		arr = arrCpy;
		size = maxSize;
		init(oldSize);
	}

	const char* cStr() override {
		string arrStr;
		if ((size > 0) && (sizeof(*arr) != sizeof(char))) {
			arrStr.push_back('[');
			for (size_t i = 0; i < size; ++i) {
				arrStr.append(to_string(arr[i]));
				if (i + 1 != size) arrStr.push_back(',');
			}
			arrStr.push_back(']');
		}
		else if ((size > 0) && (sizeof(*arr) == sizeof(char)))
			arrStr.append((char*)arr, size);
		else
			arrStr.append("nullptr");
		int arrStrSize = arrStr.size() + 1;
		char* cStr = new char[arrStrSize * sizeof(char)];
		memcpy(cStr, arrStr.c_str(), arrStrSize * sizeof(char));
		return const_cast<const char*>(cStr);
	}

	void addToEnd(type value) override {
		if (elemNum == size)
			expand();
		arr[elemNum++] = value;
	}
	
	void insertByIndex(type value, int index) override {
		if (index < 0 || index > size)
			throw DataException("insertByIndex: index is out of array bounds", index);
		if ((arr[index] == 0) && (elemNum < size)) arr[index] = value;
		else if (index == size) addToEnd(value);
		else {
			if ((elemNum - index) > (size - elemNum)) expand();
			type* pos = arr + index;
			size_t numOfElm = elemNum - index;
			memmove(pos + 1, pos, numOfElm * sizeof(type));
			arr[index] = value;
		}
		elemNum++;
	}
	
	void deleteByIndex(int index) override {
		if (index < 0 || index >= size)
			throw DataException("deleteByIndex: index is out of array bounds", index);
		int elem = 0, digit = arr[index];
		for (size_t i = 0; i < size; i++) elem += (arr[i] != 0) ? 1 : 0;
		arr[index] = 0;
		if ((digit == 0 && elem != elemNum) || digit != 0) elemNum--;
	}

	type& getByIndex(int index) override {
		if (index < 0 || index >= size)
			throw DataException("getByIndex: index is out of array bounds", index);
		return arr[index];
	}

	type* getSlice(int from, int to) override {
		if (from < 0 || from > to || to >= size)
			throw DataException("getSlice: index is out of bounds", 2, from, to);
		int sliceSize = to - from + 1;
		type* arrSlice = new type[sliceSize];
		memcpy(arrSlice, arr + from, sliceSize * sizeof(type));
		return arrSlice;
	}

	void shiftSliceR(int index) override {
		if (index < 0 || index >= size)
			throw DataException("shiftSliceR: index is out of array bounds", index);
		size_t numOfElm = (arr[size - 1] == 0) ? size - index - 1 : size - index;
		if (arr[size - 1] != 0) makeEqualSize(size, size + 1);
		type* pos = arr + index;
		memmove(pos + 1, pos, numOfElm * sizeof(type));
		arr[index] = 0;
	}

	void shiftSliceL(int index) override {
		if (index < 0 || index >= size)
			throw DataException("shiftSliceL: index is out of array bounds", index);
		type* pos = arr + index;
		size_t numOfElm = size - index - 1;
		if (arr[index] != 0) elemNum--;
		memmove(pos, pos + 1, numOfElm * sizeof(type));
		arr[size - 1] = 0;
	}

	bool isEmpty() override {
		bool state = true;
		for (int i = 0; i < elemNum; i++) {
			if (arr[i] != 0) {
				state = false;
				break;
			}
		}
		return state;
	}

	bool isElem(type value) override {
		bool state = false;
		type* end = arr + size;
		type* pos = find(arr, end, value);
		if (pos != end) state = true;
		return state;
	}

	static void swapArray(Array& first, Array& second) {
		int tmpSize = first.size;
		int tmpElemNum = first.elemNum;
		type* tmpArr = first.arr;
		first.size = second.size;
		second.size = tmpSize;
		first.elemNum = second.elemNum;
		second.elemNum = tmpElemNum;
		first.arr = second.arr;
		second.arr = tmpArr;
	}

	static Array empty() {
		Array emptyArr(0);
		return emptyArr;
	}

	void writeToBinFile(const char* file, int startPos) {
		ofstream ofstrm(file, ios::binary | ios::out | ios::_Nocreate);
		if (!ofstrm)
			throw ofstream::failure("Can't open file");
		ofstrm.seekp(startPos);
		ofstrm.write((char*)&size, sizeof(size));
		ofstrm.write((char*)&elemNum, sizeof(elemNum));
		for (size_t i = 0; i < size; i++) {
			ofstrm.write((char*)(arr + i), sizeof(arr[i]));
		}
		ofstrm.close();
	}

	void readFromBinFile(const char* file, int startPos) {
		ifstream ifstrm(file, ios::binary | ios::in);
		if (!ifstrm)
			throw ifstream::failure("Can't open file");
		ifstrm.seekg(startPos);
		if (size > 0) delete[] arr;
		ifstrm.read((char*)&size, sizeof(int));
		ifstrm.read((char*)&elemNum, sizeof(int));
		arr = new type[size];
		for (size_t i = 0; i < size; i++) {
			type num;
			ifstrm.read((char*)&num, sizeof(type));
			arr[i] = num;
		}
		ifstrm.close();
	}

	Array& operator+ (type num) {
		addToEnd(num);
		return *this;
	}

	Array& operator- () {
		deleteByIndex(elemNum - 1);
		return *this;
	}

	type& operator[] (int index) {
		return getByIndex(index);
	}

	Array& operator= (const Array& object) {
		this->size = object.size;
		this->elemNum = object.elemNum;
		delete[] this->arr;
		this->arr = new type[this->size];
		memcpy(this->arr, object.arr, object.size * sizeof(type));
		return *this;
	}

	Array& operator<< (int index) {
		shiftSliceL(index);
		return *this;
	}

	Array& operator>> (int index) {
		shiftSliceR(index);
		return *this;
	}

	operator long long* () {
		return (long long*)arr;
	}

	operator char* () {
		return (char*)arr;
	}

	friend ostream& operator<< (ostream& ostrm, Array& object) {
		ostrm << object.cStr() << endl;
		return ostrm;
	}

	friend istream& operator>> (istream& istrm, Array& object) {
		for (size_t i = object.elemNum; i < object.size; i++) {
			istrm >> object[i];
			object.elemNum++;
		}
		return istrm;
	}

	friend ofstream& operator<< (ofstream& ofstrm, Array& object) {
		ofstrm << object.size << ' ' << object.elemNum;
		for (size_t i = 0; i < object.size; i++) {
			ofstrm << ' ';
			ofstrm << object.arr[i];
		}
		ofstrm << endl;
		return ofstrm;
	}

	friend ifstream& operator>> (ifstream& ifstrm, Array& object) {
		if (object.size > 0) delete[] object.arr;
		ifstrm >> object.size >> object.elemNum;
		object.arr = new type[object.size];
		for (size_t i = 0; i < object.size; i++) {
			type num;
			ifstrm >> num;
			object.arr[i] = num;
		}
		return ifstrm;
	}

private:
	int size;
	int elemNum;
	type* arr;
	static const int expCoef = 2;

	void init(int from) {
		if (from < 0)
			throw out_of_range("init: index is negative");
		for (size_t i = from; i < size; i++) {
			arr[i] = 0;
		}
	}

	void expand() {
		int newSize = size * expCoef;
		type* newArr = nullptr;
		int lstElem = 0;
		for (size_t i = 0; i < size; i++)
			if (arr[i] != 0) lstElem = i;
		newArr = (size > 0) ? new type[newSize] : new type[1];
		memcpy(newArr, arr, size * sizeof(type));
		delete[] arr;
		arr = newArr;
		size = (size != 0) ? newSize : 1;
		init(++lstElem);
	}

};
