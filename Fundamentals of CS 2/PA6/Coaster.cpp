//File Name: Coaster.cpp
//
//Author: Brett Owen
//Date: 4/22/19
//Assignment Number: 6
//CS 2308.255 Spring 2019
//Instructor: Jill Seaman
//
//Driver for the Coaster program
//Rest in Peace, Shadow the one-eyed cat

#include "Queue.h"
#include <iostream>
#include <fstream>
using namespace std; 

int main() {
	

	Queue line; 
	ifstream inFile;
	inFile.open("riders.txt");

	int tp = 0; //total passengers passed through
	int tt = 0; // total train runs
	int seats = 0; //seats on the train
	int seatsLeft = 0; // seats remaining
	inFile >> seats;


	string name; // temp var to store the inFile name Data
	int passengers; // temp var to store the inFile passengers Data
	for (int i = 0; i < seats; i++) {
		inFile >> name;
		inFile >> passengers; 
		
		string passToQueue = name + to_string(passengers);
		
		
		if (seatsLeft - passengers >= 0) {
			for (int i = 0; i < passengers; i++) {
				line.enqueue(name + " " + to_string(i));
				tp++; 
				seatsLeft -= passengers;
			}
		}
		else {
			seatsLeft = seats; 
			cout << "Train #" << tt << endl << "=================" << endl;
				while(!line.isEmpty()){
					cout << line.dequeue() << endl;
					tp++; 
				}
			for ( int i = 0; i < size; i++){
				line.enqueue(name + " " + to_string(i)
				tp++
				seatsLeft -= passengers; 
			}
			tt++;	

		}

		
	}	
	if (!line.isEmpty()) {	
		cout << "Train #" << tt << endl << "=================" << endl;		
		while(!line.isEmpty()){
			cout << line.dequeue() << endl;
			tp++; 
		}
		tt++;	
	}
	cout << "Total Passengers: " <<  tp << endl;
	cout << "Total Trains: " << tt << endl;	
	
	inFile.close();
	
return 0; 
}