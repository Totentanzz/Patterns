#include <iostream>
#include "Test.h"

Command** Command::commandList;
Memento** Command::mementoList;
int Command::numCommand = 0;
int Command::upBound = 0;
int Command::listSize;

Singleton* Singleton::instance = nullptr;

void main() {
	system("chcp 1251");
	runTest(test27);   //Bridge tester
	runTest(test26); //Singleton tester
	runTest(test25); //Memento+command tester
}