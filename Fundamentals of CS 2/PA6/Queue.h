//File Name: Queue.h
//
//Author: Brett Owen (collaborating with Alex Gerodimos, NET ID A_G1401)
//Date: 4/22/19
//Assignment Number: 6
//CS 2308.255 Spring 2019
//Instructor: Jill Seaman 

#include <string>
using namespace std;

class Queue {
private:
	// define a Node to store strings and any other memeber variables here
	struct QueueNode{
		string name;
		QueueNode *next;
	}; 
	QueueNode *head; // the person in the back of the line
	QueueNode *back; 
public:
	//**********************
	//queue(): constructor
	//**********************
    	Queue() {
		head == NULL;
		back == NULL;
	}
	
	//**********************
	//enqueue(string x): adds a member to the queue
	//string x: name of the group and how many people are in that group
	//**********************
    	void enqueue(string x){
		QueueNode *n = new QueueNode;
		n->name = x;
		n->next = NULL; 
		if(head) {
			head = n; 
			back = n; 
		}
		else {
			back->next = n;
			back = n;
		}
		return;
				
	}
	//**********************
	//dequeue(): removes the last node in the linked list (the front of the line.
	//**********************
    	string dequeue() {
		QueueNode *p = new QueueNode;
		QueueNode *n = new QueueNode;
		while (p->next) {
			p = p->next; 
		} 
		string returnString = p->name; 
		delete p; 
		return returnString;
		
	}
	//**********************
	//isEmpty():returns if there are any nodes in the queue
	//**********************
    	bool isEmpty(){
		if (head){return false;}
		else {return true;}
	};
	
	//**********************
	//size(): number of elements in the queue
	//**********************
    	int size(){
		QueueNode *p = new QueueNode;
		p = head;
		int i = 0;
		if (p){
			p = p->next;
			i++;
		}
		return i; 
	};
};