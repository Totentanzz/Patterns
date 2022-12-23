#pragma once
#include "DataException.h"
#include "Command.h"
#include "Singleton.h"
#include "BigInt1.h"

using namespace std;

template<typename type>
void test1() {
	Array<type> a(-1);
}

template<typename type>
void test2() {
	Array<type> a(3);
	a.reduceCap(3);
}

template<typename type>
void test3() {
	Array<type> a(4);
	a.makeEqualSize(1, 2);
}

template<typename type>
void test4() {
	Array<type> a(5);
	a.insertByIndex(2, 6);
}

template<typename type>
void test5() {
	Array<type> a(6);
	a.deleteByIndex(-2);
}

template<typename type>
void test6() {
	Array<type> a(7);
	a.getByIndex(8);
}

template<typename type>
void test7() {
	Array<type> a(7);
	a.getSlice(5, 4);
}

template<typename type>
void test8() {
	Array<type> a(7);
	a.shiftSliceR(8);
}

template<typename type>
void test9() {
	Array<type> a(7);
	a.shiftSliceL(9);
}

void test10() {
	BigInt a("1324ab15.");
}

void test11() {
	BigInt a(1515);
	a.setSign(20);
}

void test12() {
	BigInt a(15213);
	BigInt b("0");
	a.divide(&b);
}

//void test13() {
//	BigDecimal a("1b32a.12c44");
//}
//
//void test14() {
//	BigDecimal a("1321244");
//}
//
//void test15() {
//	BigDecimal b("1234.1325");
//	b.setSign(20);
//}
//
//template<typename type>
//void test16() {
//	Queue<type> a;
//	a.peek();
//}
//
//template<typename type>
//void test17() {
//	Queue<type> a;
//	a.pop();
//}
//
//template<typename type>
//void test18() {
//	Stack<type> a;
//	a.peek();
//}
//
//template<typename type>
//void test19() {
//	Stack<type> a;
//	a.pop();
//}

//void test20() {
//	BigInt abc("9998765351108765351108701440036931448099000"), abc1;
//	abc.writeToBinFile("1.txt");
//	abc1.readFromBinFile("1.txt");
//	cout << abc << abc1;
//}
//
//void test21() {
//	BigInt first("9998765351108765351108701440036931448099000");
//	BigInt second("9998765351108765351108701440036931448099000");
//	for (int i = 0; i < 200; i++) {
//		cout << first << i << endl;
//		first = first * second;
//	}
//	cout << first;
//	for (int i = 0; i < 200; i++) {
//		cout << first << i << endl;
//		first = first / second;
//	}
//	cout << first;
//}
//
//void test22() {
//	BigInt first(8446744073709551617);
//	BigInt second(8446744073709551618);
//	for (int i = 0; i < 1000; i++) {
//		cout << first << i << endl;
//		first = first + second;
//	}
//	cout << first;
//	for (int i = 0; i < 1000; i++) {
//		cout << first << i << endl;
//		first = first - second;
//	}
//	cout << first;
//}

//void test23() {
//	BigDecimal bd1("8446744073709551618.8446744073709551618");
//	BigDecimal bd2("999876535110876535110870144.0036931448099000");
//	for (int i = 0; i < 1000; i++) {
//		cout << bd1.cStr() << "    " << bd2.cStr() << endl;
//		bd1.add(&bd2);
//	}
//	cout << bd1.cStr() << "    " << bd2.cStr() << endl;
//	for (int i = 0; i < 1000; i++) {
//		cout << bd1.cStr() << "    " << bd2.cStr() << endl;
//		bd1.subtract(&bd2);
//	}
//	cout << bd1.cStr() << "    " << bd2.cStr() << endl;
//}

template<typename T>
void test24() {
	Array<T> tmp(10);
	for (int i = 0; i < 10; ++i) {
		tmp + (i+1);
	}
	cout << tmp;
	-tmp;
	cout << tmp;
	cout << tmp[5] << endl;
	cout << (tmp << 0);
	cout << (tmp >> 3);
}

template<>
void test24<char>() {
	Array<char> tmp(10);
	for (int i = 0; i < 10; ++i) {
		tmp + ('0' + (i+1));
	}
	cout << tmp;
	-tmp;
	cout << tmp;
	cout << tmp[5] << endl;
	cout << (tmp << 0);
	cout << (tmp >> 3);
}

void test25() {
	BigInt num1;
	BigInt num2("666666666666666666666666666666666666");
	Command* commands[4];
	commands[0] = new Command(&num1, &BigInt::add);
	commands[1] = new Command(&num2, &BigInt::subtract);
	commands[2] = new Command(&num1, &BigInt::multiply);
	commands[3] = new Command(&num1, &BigInt::divide);
	cout << "Изначальный объект: " << num1;
	commands[0]->execute(&num2);
	cout << "Комманда add была вызвана, объект: "<< num1;
	commands[0]->undo();
	cout << "Откат последней команды, объект: " << num1;
	commands[0]->redo(&num2);
	cout << "Повторный вызво последней команды, объект: "<< num1;
	commands[2]->execute(&num2);
	cout << "Комманда multiply была вызвана, объект: " << num1;
	commands[1]->execute(&num2);
	cout << "Команда subtract была вызвана, объект: " << num1;
	commands[1]->undo();
	cout << "Откат последней команды: объект: " << num1;
}

void test26() {
	Singleton* singleArr = Singleton::instanceT();
	if (singleArr != nullptr) {
		cout << "Singleton was created, object: " << singleArr->cStr() << endl;
	}
	cout << "Calling addToEnd method" << endl;
	for (size_t i = 0; i < 12; ++i) {
		singleArr->addToEnd(i);
	}
	cout << "result: " << singleArr->cStr() << endl;
	singleArr->deleteByIndex(0);
	cout << "calling deleteByIndex, object: " << singleArr->cStr() << endl;
	singleArr->insertByIndex(2324, 0);
	cout << "calling insertByIndex, object: " << singleArr->cStr() << endl;
	cout << "trying to create singleArr2: ";
	Singleton* singleArr2 = Singleton::instanceT();
	if (singleArr2 != nullptr) {
		cout << "sucessful, object: " << singleArr2->cStr();
	}
	else cout << "not established" << endl;
}

void test27() {
	BigInt1 first("9998765351108765351108701440036931448099000");
	BigInt1 second("9998765351108765351108701440036931448099000");
	for (int i = 0; i < 200; i++) {
		cout << first.cStr() << endl << i << endl;
		first.multiply(&second);
	}
	cout << first.cStr() << endl;
	for (int i = 0; i < 200; i++) {
		cout << first.cStr() << endl << i << endl;
		first.divide( &second);
	}
	cout << first.cStr() << endl;
}

void runTest(void(*func)(void)) {
	try
	{
		func();
	}
	catch (const DataException& ex)
	{
		cout << ex.what() << '\t' << ex.whatData() << endl;
	}
	catch (const iostream::failure& ex1) {
		cout << ex1.what() << "\nerror code: " << ex1.code() << endl;
	}
	catch (const exception& ex2)
	{
		cout << ex2.what() << endl;
	}
}