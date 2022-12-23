#pragma once

//јбстрактный класс List, который наследуетс€ классом Array
template<typename type>
class List
{
public:
	
	virtual int getSize() = 0;

	virtual int getElmNum() = 0;

	virtual type* getArr() = 0;

	virtual const char* cStr() = 0;

	virtual void addToEnd(type value) = 0;

	virtual void insertByIndex(type value, int index) = 0;

	virtual void deleteByIndex(int index) = 0;

	virtual type& getByIndex(int index) = 0;

	virtual type* getSlice(int from, int to) = 0;

	virtual void shiftSliceR(int index) = 0;

	virtual void shiftSliceL(int index) = 0;

	virtual bool isEmpty() = 0;

	virtual bool isElem(type value) = 0;

protected:
private:
};

