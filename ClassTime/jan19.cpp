#include <iostream>
#include "Pokemon.h"

using namespace std;

void checkRange(int a) {
    if (a >= 1 && a <=10) {
        cout << "Well done!" << endl;
    } else {
        cout << "Out of range!" << endl;
    }
    a = 42;
}

//this is an example of a "simple factory" method
//that instantiates a Pokemon object and returns
//a pointer to it
Pokemon* pokemonFactory(int h, string parent) {
    return new Pokemon(h, parent);
}

//this method accepts a pointer to a Pokemon object,
//then calls the talk method on it.
void makeItTalk(Pokemon* p) {
    p->talk();
}

int main(int argc, char* argv[]) {
    cout << "You passed " << argc << " command-line parameters." << endl;
    int sum = 0;
    for (int i=1; i<argc; i++) {
        cout << "parameter#" << i << " is " << argv[i] << endl;
        sum += stoi(argv[i]);
    }
    cout << "their sum is " << sum << endl;
    //cout is pronounced "see out"
    Pokemon pikachu(35, "Pichu");
    //use "dot" to call methods on an object
    pikachu.talk();

    Pokemon* bulbasaur = new Pokemon(40, "megasaur");
    //use an "arrow" to call methods on an object pointer
    //bulbasaur->talk();
    makeItTalk(bulbasaur);

    Pokemon* janet = pokemonFactory(25, "charmander");
    makeItTalk(janet);

    string firstname;
    int nima;
    cout << "Welcome to CS301";
    cout << " Go seasiders!!" << endl;
    //cout << "What is your name? ";
    //cin >> firstname;
    //cout << "Pleased to meet you, " << firstname << "!" << endl;
    cout << "Give me a number between 1 and 10 inclusive: ";
    cin >> nima;
    cout << "you typed: " << nima << endl;
    int* ask = &nima;
    cout << "Nima's memory address is " << ask << endl;

    //arrays in C++ are basically just fancy pointers.
    int* shohei = new int[5];
    shohei[0] = 42;

    checkRange(nima);
    //cout << "After calling the function, nima is " << nima << endl;
    //return 0;
}

/*
 * multi
 * line
 * comment
 */
