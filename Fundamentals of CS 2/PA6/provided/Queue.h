//put your header here

#include <string>
using namespace std;

class Queue {
private:
    // define a Node to store strings and any other memeber variables here


public:
    Queue();
    void enqueue(string);
    string dequeue();
    bool isEmpty();
    int size();  //returns the number of elements in the queue
};
