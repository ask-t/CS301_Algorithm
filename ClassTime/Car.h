#include <bits/stdc++.h>
using namespace std;

class Car {
private:
  string make;
  string model;
  int year;

public:
  Car(string make, string model, int year);
  string getMake();
  string getModel();
  int getYear();
  void setMake(string make);
  void setModel(string model);
  void setYear(int year);
};
