//Brett Owen A04850405
//CS2308 section 225
//January 29th, 2019

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct food{
        string name;
        float price;
        int timesOrdered = 0;
    };


void menuList(food menuInput[8]) {

    cout << "Here's our menu: " << endl;
            for (int i = 0; i < 8; i++){
                cout << setw (3) << left << " " <<(i + 1) << "|"<< setw (15) << left << menuInput[i].name << setw(6) << right <<"$" << menuInput[i].price << endl;
            }
}

void makeOrder (food menuInput[8]) {
    cout << "What would you like to order? (Enter the number next to the menu item)." << endl;
    cout << "Type '0' to exit ordering" << endl;

    int input;
    while (input != 0) {
        cin >> input;
        if (input == 0) {
            break;
        }
        if (input <  9) {
            menuInput[input-1].timesOrdered++;
        }
        else {
            cout << "Please enter a valid number!" << endl;
        }
    }
    return;
}

void finalBill(food menuInput[8]) {
    float subTotal = 0.00;
    for (int i = 0; i < 8; i++) {
        subTotal += (menuInput[i].price * menuInput[i].timesOrdered);
    }
    cout << "Subtotal = $"<< fixed << setprecision(2) << subTotal << endl;
    cout << "Tax = $" << fixed << setprecision(2) << (subTotal* .07) << endl;
    cout << "Final total = $" << fixed << setprecision(2) << subTotal * 1.07 << endl;
    return;
}

int main() {
    //Defines the values for the food items.
    struct food menu[8];
    menu[0].name = "Plain Egg";
    menu[0].price = 1.45;
    menu[1].name = "Bacon and Egg";
    menu[1].price = 2.45;
    menu[2].name = "Muffin";
    menu[2].price = 0.99;
    menu[3].name = "French Toast";
    menu[3].price = 1.99;
    menu[4].name = "Fruit Basket";
    menu[4].price = 2.49;
    menu[5].name = "Cereal";
    menu[5].price = 0.69;
    menu[6].name = "Coffee";
    menu[6].price = 0.49;
    menu[7].name = "Tea";
    menu[7].price = 0.75;

    //Introduces the program while also letting me make a Baby Driver reference.
    cout << "Welcome to Bo's Diner!" << endl;

    //Enters a loop that lets the user make multiple orders.
    int quit = 0;
    while (quit != 1) {

        menuList(menu); //Lists the menu
        makeOrder(menu); // lets user choose the menu items
        finalBill(menu); // calculates the final bill

        // Checks if the user wants to make another order.
        cout << "Would you like to make another order? (y/n)" << endl;
        char startOver;
        cin >> startOver;
        if ( startOver == 'n'){
            quit = 0;
        }
        // Clears the amount of times ordered.
        for (int i = 0; i < 8; i++){
            menu[i].timesOrdered = 0;
        }
    }
return 0;
}

