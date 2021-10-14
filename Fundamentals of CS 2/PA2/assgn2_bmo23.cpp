// Brett Owen
// CS 2308
// Assignment 2
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
struct song { // Declares the struct for all the song library info
        string ID;
        string title;
        string artist;
        float fileSize;
        int plays;
        int rating;
    };

void displayMenu() {// displays menu
    cout << "Menu:" << endl;
    cout << "1. Display Songs sorted by title" << endl;
    cout << "2. Display Songs sorted by rating" << endl;
    cout << "3. Lookup title and artist by ID" << endl;
    cout << "4. Lookup ID by title and artist" << endl;
    cout << "5. Quit the Program" << endl;
    return;
}

struct songRate { // struct used to sort songs by rating
        int index;
        int rating;
    };

void bubbleSort (songRate songs[],int count) { // sorts the songs by rating
     bool swap;
     int temp;
     int indexTemp;
     do {
         swap = false;
         for (int i = 0; i < (count-1); i++) {
             if (songs[i].rating < songs[i+1].rating) {
                    temp = songs[i].rating;
                    indexTemp = songs[i].index;

                    songs[i].rating = songs[i+1].rating;
                    songs[i].index = songs[i+1].index;
                    songs[i+1].rating = temp;
                    songs[i+i].index = indexTemp;

                    swap = true;
                 }
        }
     } while (swap);
}
void displayByRating(song lib[], int count) { //Displays sorted songs by rating
    songRate songs[count];
    for (int i = 0; i < count; i++){
        songs[i].rating = lib[i].rating;
        songs[i].index = i;
    }
    bubbleSort(songs, count);
    for (int i = 0; i < count; i++) {
        cout << lib[songs[i].index].ID <<" " << lib[songs[i].index].title << " " << lib[songs[i].index].artist << " " << lib[songs[i].index].fileSize << " " << lib[songs[i].index].plays << " " << lib[songs[i].index].rating<< endl;
    }

    return;
}

void searchID(song lib[], int count) { // Searches for the song based on ID.
    string input = " ";
    cout << "Enter ID to search for (type '0' to quit)(CASE SENSITIVE): ";
    cin >> input;
    bool found = false;
    for (int i = 0; i < count; i++ ) {
        if (input == lib[i].ID){
            found = true;
            cout << setw(30)<<  lib[i].title << setw(30)<<lib[i].artist << " " << lib[i].fileSize << setw(4) << lib[i].plays << " " << lib[i].rating<< endl;
        }
    }
    if (!found) {
        cout << "ID not found in Library." << endl;
    }
    return;
}

void searchTitle (song lib[], int count) { // Searches for ID based on Title and Author
    string title;
    string artist;

    cout << "Enter the artist of the song: ";
    getline(cin >> ws, artist);
    cout << "Enter the title of the song: ";
    getline(cin >> ws, title);

    bool found = false;
    for (int i = 0; i < count; i++){
        if (lib[i].artist == artist) {
            found = true;
            if (lib[i].title == title){
                cout << "The ID of " << lib[i].title << " by " << lib[i].artist << " is " <<  lib[i].ID << "." << endl;
            }
            else {
                cout << "This Artist's song isn't in the library." << endl;
            }
        }
    }
    if (!found) {
        cout << artist <<" isn't featured in this library." << endl;
    }

}


int main(){
    ifstream inputFile;
    const int SIZE = 50; // max size of songs in the array

    song songLib[SIZE];
    inputFile.open("library.txt");
    int count = 0;

    while (inputFile >> songLib[count].ID)  {
        inputFile >> ws;
        getline(inputFile, songLib[count].title);
        getline(inputFile, songLib[count].artist);
        inputFile >> songLib[count].fileSize;
        inputFile >> songLib[count].plays;
        inputFile >> songLib[count].rating;
        count++;
    }

    int quit = 0;
    while (quit != 1){
        displayMenu();
        cout << "Enter your choice: ";
        int input = 0;
        cin >> input;
        if (input == 1) {
            cout << "1. Display Songs by title" << endl;
        }
        if (input == 2) {
            cout << "2. Display Songs sorted by rating" << endl;
            displayByRating(songLib, count); //COMPLETE
        }
        if (input == 3) {
            cout << "3. Lookup title and artist by ID" << endl;
            searchID(songLib, count);
        }
        if (input == 4) {
            cout << "4. Lookup ID by title and artist" << endl;
            searchTitle(songLib, count);
        }
        if (input == 5) {
            cout << "Quitting the program..." << endl; //COMPLETE
            quit = 1;
        }

    }
    // Close the file.
    inputFile.close();

    return 0;
}
