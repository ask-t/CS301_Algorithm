#include <iostream>
#include "Pokemon.h"

using namespace std;

void checkRange(int& a) {
    if (a >= 1 && a <=10) {
        cout << "Well done!" << endl;
    } else {
        cout << "Out of range!" << endl;
    }
    a = 42;
}

int main() {
    //cout is pronounced "see out"
    Pokemon pikachu(35, "Pichu");
    pikachu.talk();
    string firstname;
    int nima;
    cout << "Welcome to CS301";
    cout << " Go seasiders!!" << endl;
    cout << "What is your name? ";
    cin >> firstname;
    cout << "Pleased to meet you, " << firstname << "!" << endl;
    cout << "Give me a number between 1 and 10 inclusive: ";
    cin >> nima;
    cout << "you typed: " << nima << endl;
    checkRange(nima);
    cout << "After calling the function, nima is " << nima << endl;
    //return 0;
}

/*
 * multi
 * line
 * comment
 */
