#include "Number1.h"

Number1::Number1(Number1Impl* p) : pimpl(p) {
}

Number1::~Number1() {
	delete this->pimpl;
}