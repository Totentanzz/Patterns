#include "Singleton.h"

Singleton::Singleton() {
	this->arr = new Array<long long>;
}

Singleton::~Singleton() {
	delete this->arr;
}

Singleton* Singleton::instanceT() {
	Singleton* p = nullptr;
	if (instance == nullptr) {
		p = new Singleton();
		instance = p;
	}
	return p;
}

Array<long long> Singleton::getArr() {
	return *(this->arr);
}

int Singleton::getSize() {
	return this->arr->getSize();
}

int Singleton::getElemNum() {
	return this->arr->getElmNum();
}

void Singleton::addToEnd(long long value) {
	this->arr->addToEnd(value);
}

void Singleton::insertByIndex(long long value, int index) {
	this->arr->insertByIndex(value, index);
}

void Singleton::deleteByIndex(int index) {
	this->arr->deleteByIndex(index);
}

long long& Singleton::getByIndex(int index) {
	return this->arr->getByIndex(index);
}

const char* Singleton::cStr() {
	return this->arr->cStr();
}