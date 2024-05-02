#include <string>

using namespace std;

class Pokemon {

private:
  int hp;
  string evolvesFrom;
  string name;

public:
  Pokemon(int h, string n) {
    hp = h;
    name = n;

  }
  void battle(Pokemon);
  void talk();
  int getHP() { return hp; }
};
