#pragma once
#include "BigInt.h"
class Command
{
	typedef void (BigInt::* Action) (void*);
public:
	Command(BigInt* receiver,Action action);

	virtual void execute(void* obj);

	static void undo();

	static void redo(void* obj);

protected:

	BigInt* receiver;
	Action action;
	static int listSize;
	static Command** commandList;
	static Memento** mementoList;
	static int numCommand;
	static int upBound;

private:

	static void resizeLists();
};

