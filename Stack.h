#ifndef __Stack__
#define __Stack__

#include <iostream>
#include "StackItem.h"

using namespace std;

class Stack {
public:
	Stack();
	~Stack();
	void push(StackItem* item);
	StackItem* pop();
	StackItem* top();
	bool isEmpty();

private:
	StackItem* head;
};

#endif
