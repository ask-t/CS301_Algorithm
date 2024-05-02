#include <bits/stdc++.h>
using namespace std;

int main() {
  while (1) {

    // Ask how old the user is
    cout << "How old are you?" << endl;
    string input;
    cin >> input;
    int age = stoi(input);

    // Respond based on age
    if (age < 13) { // if the user is youger than teen
      int gap = 13 - age;
      cout << "Try again in " << gap << " year(s)." << endl;
    } else if (13 <= age && age < 20) { // if the user is a teen
      for (int i = 1; i <= age; i++) {
        cout << i << " TEEN POWER!!!!" << endl;
      }
    } else { // if the user is older than teen
      int gap = age - 19;
      cout << "You lost your teen power " << gap << " year(s) ago." << endl;
    }

    // Ask if the user wants to play again
    string answer;
    while (1) {
      cout << "Play again (y/n)?" << endl;
      cin >> answer;
      if (answer == "y" || answer == "n")
        break;
    }
    if (answer == "n") {
      cout << "Thank you for playing BRO. DRAPER'S REFERENCE IMPLEMENTATION of "
              "TEEN POWER. \nPress any key to exit."
           << endl;
      break;
    }
    // if the answer is "y" then go back at the beggining.
  }
  return 0;
}
