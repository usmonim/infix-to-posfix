#include "Stack.h"

Stack::Stack() {
	this->head = NULL;
}
Stack::~Stack(){
	
}
void Stack::push(StackItem* item) {
	item->next = head;
	this->head = item;

	/*if (this->head == NULL) {
		head = item;
	}
	else {
		StackItem* temp = head;
		head = item;
		item->next = temp;
	}*/
}
StackItem* Stack::pop() {
	StackItem* temp = head;
	head = head->next;
	return temp;
	
}
StackItem* Stack::top() {
	return head;
	
}
bool Stack::isEmpty() {
	if (this->head == NULL) {
		return true;
	}
	else {
		return false;
	}
	
}