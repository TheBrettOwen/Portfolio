//File Name: Stack.h
//
//Author: Brett Owen
//Date: 4/22/19
//Assignment Number: 6
//CS 2308.255 Spring 2019
//Instructor: Jill Seaman

#include <cassert>
#include <string>
using namespace std;

class Stack {
private:
  // define a Node to store strings and the head or top variable here
	struct StackNode {
		string data;
		StackNode *next; 
	};
	StackNode *head; 

public:
    	//*****************************
	// Stack(): Constructor for the Stack
	//*****************************
	Stack() { head = NULL;}
	
	//*****************************
	// push(string x): push the passed string to the top of the stack.
	//*****************************
    	void push(string x) {
		StackNode *n = new StackNode;
		n->data = x;
		if (head) {
			n->next = head->next;
		} 
		head = n; 
	return; 
	}
	
	//*****************************
	// pop(): removes the first item in the stack and returns the data of that node
	//*****************************
    	string pop() {
		StackNode *p = new StackNode;
		p = head; 
		if (p){
			head = head->next;
			string returnString = p->data;
			delete p;
			return returnString;
		}
	}
	
	//*****************************
	// isEmpty(): checks if the stack is empty
	//*****************************
    	bool isEmpty() {
		if (head){
			return false;
		} 
		else {
			return true;
		}
	}
};