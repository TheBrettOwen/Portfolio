// File Name StringList.cpp
//
// Brett Owen ( I worked on this with Alex Gerodimos, NetID a_g1401)
// 4/10/2019
// CS 2308.255 Spring 2019
// Assignment 6
// Instructor: Jill Seaman
//
// CPP file for the header class to manipulate a linked lists of strings. 

#include <iostream>
#include "StringList.h"

//***********************************************************
// StringList(): Constructor
//***********************************************************

StringList::StringList() {
	head = NULL; // pointer for the first list, currently empty
}

//***********************************************************
// ~StringList(): Deconstructor 
//***********************************************************

StringList::~StringList() {
	StringNode *p; // pointer for the current node
	StringNode *n; // pointer for the next node
	p = head;
	while (p != NULL) {
		n = p->next;
		delete p;
		p = n;
	}
	delete n; 
}

//***********************************************************
// count(): counts the number of nodes in the linked list
//***********************************************************

int StringList::count(){
	int nCount = 0; 
	StringNode *p; 
	p = head; 
	while (p != NULL) {
		p = p->next;
		nCount++; 
	}
	delete p; 
	return nCount;
}

//***********************************************************
// push_front(string toFront): places a new node inbetween
// the head pointer and the first node of the list
// string toFront: the data for the node to hold, in this 
// case a string containing a movie title
//***********************************************************

void StringList::push_front(string toFront){
	StringNode *p = new StringNode; // declares an anonymous array to be the next node in the list
	StringNode *n; // declares a pointer to contain the original pointer for the head
	n = head; 
	head = p;
	p->data = toFront; 
	p->next = n; 
	return; 
}

//***********************************************************
// push_back(string toBack): places a new node at the back
// of the linked list
// string toBack: the data to put inside the last node
//***********************************************************

void StringList::push_back(string toBack){
	StringNode *p; // pointer used to traverse the array
	StringNode *n = new StringNode; // node used to hold the new data
	p = head;
	n->data = toBack;   
	while (p->next != NULL) { 
		p = p->next; 
	}
	p->next = n; 
	return; 
}

//***********************************************************
// pop_front(): deletes the first node of the linked list 
// and replaces it with the next node, if there is any.
// If I knew how to code sound effects, you'd hear an 
// audible "POP!" when the function is called.
//***********************************************************

void StringList::pop_front() {
	StringNode *p = head; // pointer used to hold the data of the first node
	if (head != NULL) {
		head = head->next;
		delete p;
	}
	return; 
}

//***********************************************************
// display(): displays the data within the linked list
//***********************************************************

void StringList::display() {
	StringNode *p; //pointer used to traverse the list
	p = head; 
	while (p != NULL) {
		cout << p->data << endl; 
		p = p->next; //makes p point to the next node
	}
	return; 
}

//***********************************************************
// sort(): uses all of the other functions to make a new list
// and sort them alphabetically. 
//***********************************************************

void StringList::sort() {
	StringNode *sortedHead = NULL; // pointer to be the head of the new linked list
	while (head) {
		StringNode *n = new StringNode; // new node for the next set of data
		StringNode *p; // used to store the head pointer and the data it points to
		p = sortedHead;
		sortedHead = n;
		n->data = maximum()->data; 
		n->next = p; 
		remove(maximum());
	}  
	head = sortedHead;
return;
}

//***********************************************************
// remove(StringNode *m): searches for a node that matches 
// the pointer and deletes without breaking the whole list
// StringNode *m: pointer for the function to look for
//***********************************************************

void StringList::remove(StringNode *m){
		StringNode *p = new StringNode; // traverses the list
		StringNode *n = new StringNode; // holds the previous node traversed
		p = head; 
		while (p->next && p != m){
			n = p;
			p = p->next;
		}
		if (p) {
			if (p == head) {
				head = p->next;
				delete p; 
			}
			else {
				n->next = p->next; 
				delete p; 
			}
		}
	return;
}

//***********************************************************
// maximum(): returns the pointer for the alphabetically 
// greatest string in the linked list
//***********************************************************

StringList:: StringNode * StringList::maximum(){
	StringNode *p; // traverses the list and is the is used to hold the current thing to be compared to 
	StringNode *n; // holds the max value
	p = head; 
	n = head;
	while (p) {
		if ((p->data).at(0) > (n->data).at(0)) {
			 n = p; 
		}
		p = p->next;
	}
return n;
}

