// Brett Owen
#include <iostream>
using namespace std;

int minimum(int array[], int SIZE) {
int min = 0;
int *ptr = array;
    for (int i = 0; i < SIZE; i++) {
        if (*(ptr + i) < min) {
            min = *(ptr + i);
        }
    }
    delete ptr;
return min;
}

int swapTimesTen(int &x, int &y) {
    int *xptr;
    int *yptr;
    int *temp;
    xptr = &x;
    yptr = &y;
    temp = &x;
    int total = 0;
    total = (*yptr * 10) + (*xptr * 10);

    delete xptr;
    delete yptr;
    delete temp;

    return total;
}

void doubleArray(int array[], int SIZE) {
    int dArray[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int *aptr = array;
    int *dptr = dArray;
    for (int i = 0; i < SIZE; i++) {
        *(dptr + i) = *(aptr + i);
        cout << *(dptr + i) << " ";
    }
    for (int i = 0; i < (SIZE); i++){
        *(dptr+(SIZE+i)) = ((*(aptr + i))+ (*(aptr + i)));
        cout << *(dptr+SIZE+ i) << " ";
    }
    delete aptr;
    delete dptr;
return ;
}

void subArray(int oldArray[], int startIndex, int sub) {
    int newArray[4] = {0};
    int *optr = oldArray;
    int *nptr = newArray;
    for (int i = 0; i < sub; i++) {
        *(nptr + i) = *(optr + (startIndex + i));
    }
    for (int i = 0; i < sub; i++) {
        cout << *(nptr + i) << " ";
    }
    delete optr;
    delete nptr;
return;
}

int *duplicateArray (int *arr, int size) {
     int *newArray;
     if (size <= 0) //size must be positive
        return NULL; //NULL is 0, an invalid address
     newArray = new int [size]; //allocate new array
     for (int index = 0; index < size; index++)
        newArray[index] = arr[index]; //copy to new array
 return newArray;
}

int *subArray2 (int *array, int start, int length) {
    int *result = duplicateArray(array, length);
    for (int i = 0; i < length; i++)
        cout << *(result + i)+ start << " ";
 return result;
}

int main() {
    const int arraySize = 10;
    int minTestArray[arraySize] = {1,2,3,4,5,6,7,-8,9,0};
    cout << "Testing Minimum" << endl;
    cout << "Array Values: ";
    for (int i = 0; i < arraySize; i++) {
        cout << minTestArray[i] << " ";
    }
    cout << endl;
    cout << "Expected Minimum: -8" << endl;
    cout << "Actual Minimum: " << minimum(minTestArray, arraySize) << endl;
    cout << endl << endl;


    int a = 3;
    int b = 5;
    int testArray[9];
    for (int i = 0; i < 9; i++)
        testArray[i] = (i+1);
    cout << "Testing swapTimesTen" << endl;
    cout << "Expected result: 80, when a is " << a << " and b is "<< b << endl;
    cout << "Actual result: " << swapTimesTen(a, b) << ", when a is " << a << " and b is " << b << endl;
    cout << endl << endl;


    cout << "Testing doubleArray" << endl;
    cout << "Expected Result: 1 2 3 4 5 6 7 8 9 2 4 6 8 10 12 14 16 18" << endl;
    cout << "Actual Result:   ";
    doubleArray(testArray, 9);
    cout << endl << endl;


    cout << "Testing Sub Array" << endl;
    cout << "Expected result: 6 7 8 9" << endl;
    cout << "Actual Result:   ";
    subArray(testArray, 5, 4);
    cout << endl << endl;

    cout << "Testing Sub Array 2" << endl;
    cout << "Expected result: 6 7 8 9" << endl;
    cout << "Actual Result:   ";
    subArray2(testArray, 5,4);
return 0;
}
