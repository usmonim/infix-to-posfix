#include "Calculator.h"
#include "StackItem.h"

Calculator::Calculator(string infix) {
	this->infixExpression = infix;
	this->postfixExpression = "";
	this->stack = new Stack();
	string token;
	istringstream iss(infixExpression);
	iss >> token;

	while (token.compare(";") != 0) {
		StackItem* item = new StackItem(token);

		if (item->isOperator) {

			if (stack->isEmpty() || item->op == OPERATOR_LEFTPAR) {
				stack->push(item);
			}
			else if (item->op == OPERATOR_RIGHTPAR) {
				while (stack->top()->op != OPERATOR_LEFTPAR) {
					postfixExpression += stack->top()->toString() + " ";
					delete stack->pop();
				}
				if (stack->top()->op == OPERATOR_LEFTPAR) {
					delete stack->pop(); 
				}
			}
			else {
				if (item->op == OPERATOR_MULTIPLICATION || item->op == OPERATOR_DIVISION) {
					if (stack->top()->op == OPERATOR_MINUS || stack->top()->op == OPERATOR_PLUS) {////top element has lower precendence
						stack->push(item);
					}
					else {
						if (stack->top()->op == OPERATOR_MULTIPLICATION || stack->top()->op == OPERATOR_DIVISION) {/////top element is equal 
							while (stack->top()->op == OPERATOR_MULTIPLICATION || stack->top()->op == OPERATOR_DIVISION) {
								postfixExpression += stack->top()->toString() + " ";
								delete stack->pop();
							}
						}
						stack->push(item);
					}
				}
				if (item->op == OPERATOR_MINUS || item->op == OPERATOR_PLUS) {
					if (stack->top()->op == OPERATOR_MULTIPLICATION || stack->top()->op == OPERATOR_DIVISION) {////top element with higher precendence 
						while ((!stack->isEmpty()) && (stack->top()->op == OPERATOR_MULTIPLICATION || stack->top()->op == OPERATOR_DIVISION)) {
							postfixExpression += stack->top()->toString() + " ";
							delete stack->pop();
						}
					}
					if ((!stack->isEmpty()) && (stack->top()->op == OPERATOR_MINUS || stack->top()->op == OPERATOR_PLUS)) {/////top element is equal
						while ((!stack->isEmpty()) && (stack->top()->op == OPERATOR_MINUS || stack->top()->op == OPERATOR_PLUS)) {
							postfixExpression += stack->top()->toString() + " ";
							delete stack->pop();
						}
					}
					stack->push(item);
				}
			}
		}
		else {
			postfixExpression += item->toString() + " ";
		}
		iss >> token;
		
	}
	while (!stack->isEmpty()) {
		postfixExpression += stack->top()->toString() + " ";
		delete stack->pop();
	}
	
	postfixExpression += ";";
	
}
		
Calculator::~Calculator() {
	delete stack;
}

string Calculator::getPostfix() {
	return postfixExpression;

}

int Calculator::calculate() {
	int result = 0;

	string token;
	istringstream iss(postfixExpression);
	iss >> token;

	while (token.compare(";") != 0) {
		StackItem* item = new StackItem(token);
		if (!item->isOperator) {
			stack->push(item);
		}
		else if (item->isOperator) {
			int firstNumber;
			firstNumber = stack->top()->n;
			delete stack->pop();
			int secondNumber;
			secondNumber = stack->top()->n;
			delete stack->pop();
			
			if (item->op == OPERATOR_MINUS) {
				StackItem* finalResult = new StackItem(to_string(secondNumber - firstNumber));
				stack->push(finalResult);
			}
			if (item->op == OPERATOR_PLUS) {
				StackItem* finalResult = new StackItem(to_string(secondNumber + firstNumber));
				stack->push(finalResult);
			}
			if (item->op == OPERATOR_DIVISION) {
				StackItem* finalResult = new StackItem(to_string(secondNumber / firstNumber));
				stack->push(finalResult);
			}
			if (item->op == OPERATOR_MULTIPLICATION) {
				StackItem* finalResult = new StackItem(to_string(secondNumber * firstNumber));
				stack->push(finalResult);
			}
		}
		iss >> token;
	}
	return stack->top()->n;
	
}





















//int presedence(StackItem * check) {
//	if (check->op == OPERATOR_MINUS || check->op == OPERATOR_PLUS) {
//		return 1;
//	}
//	else if (check->op == OPERATOR_DIVISION || check->op == OPERATOR_MULTIPLICATION) {
//		return 2;
//	}
//}