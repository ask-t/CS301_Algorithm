#include "Pokemon.h"
#include <iostream>
using namespace std;

Pokemon::Pokemon(int h, string n) {
  hp = h;
  name = n;
}

void Pokemon::battle(Pokemon opponent) {

  // TODO make them fight
}

void Pokemon::talk() {

  cout << "My HP is " << hp << " and I evolved from " << evolvesFrom << endl;
}
