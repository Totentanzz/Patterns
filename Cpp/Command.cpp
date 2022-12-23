#include "Command.h"

Command::Command(BigInt* receiver,Action action) {
	this->listSize = 10;
	this->commandList = new Command*[this->listSize];
	this->mementoList = new Memento * [this->listSize];
	this->receiver = receiver;
	this->action = action;
}

void Command::execute(void* obj) {
	if (numCommand + 1 == listSize) resizeLists();
	mementoList[numCommand] = this->receiver->createMemento();
	commandList[numCommand] = this;
	upBound = numCommand > upBound ? numCommand : upBound;
	numCommand++;
	(this->receiver->*action)(obj);
}

void Command::undo() {
	if (numCommand == 0) {
		cout << "Numbers of command is 0" << endl;
		return;
	}
	commandList[numCommand - 1]->receiver->reinstate(mementoList[numCommand - 1]);
	numCommand--;
}

void Command::redo(void* obj) {
	if (numCommand + 1 == listSize) resizeLists();
	if (numCommand > upBound)
	{
		cout << "The number of command is too big" << endl;
		return;
	}
	(commandList[numCommand]->receiver->*(commandList[numCommand]->action))(obj);
	numCommand++;
}

void Command::resizeLists() {
	int newSize = listSize * 2;
	Command** newCommandList = new Command*[newSize];
	Memento** newMementoList = new Memento*[newSize];
	memcpy(newCommandList, commandList, listSize * sizeof(Command*));
	memcpy(newMementoList, mementoList, listSize * sizeof(Memento*));
	delete[] commandList;
	delete[] mementoList;
	commandList = newCommandList;
	mementoList = newMementoList;
	listSize = newSize;
}