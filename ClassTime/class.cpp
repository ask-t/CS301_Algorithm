#include "Pokemon.h"
#include <bits/stdc++.h>
using namespace std;

void Pokemon::talk(){
  cout << "My HP is " << hp << " and I evolved from " << evolvesFrom << endl;
}


int main() {
  Pokemon p(100, "Pikachu", "Pichu");
  p.talk();

  return 0;
}
