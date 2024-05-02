#include <bits/stdc++.h>
#include "Employee.h"
using namespace std;


vector<Employee *> getEmployees(istream &ifs)
{
  vector<Employee *> employees;
  string size;
  getline(ifs, size); // Get the first line of the file
  cout << size << endl;
  string name, id, age, job, year;
  // for (int i = 0; i < stoi(size); i++)
  while (ifs.good()) // make a loop to get the data from the file
  {
    getline(ifs, name, '|');
    getline(ifs, id, '|');
    getline(ifs, age, '|');
    getline(ifs, job, '|');
    getline(ifs, year);
    Employee *emp = new Employee(name, stoi(id), stoi(age), job, stoi(year));
    employees.push_back(emp);
  }
  return employees;
}

int main(int argc, char *argv[])
{
  ifstream ifs(argv[1]); // Open the file

  if (argc < 2) // Check if there is a command line argument
  {
    cerr << "Missing command line argument\n";
    cerr << "Usage: " << argv[0] << " <filename.txt>" << endl;
    return 1;
  }
  if (!ifs.is_open()) // Check if the file can be opened
  {
    cerr << "Could not open file: " << argv[1] << endl;
    return 1;
  }
  vector<Employee *> employees = getEmployees(ifs);

  for (int i = 0; i < employees.size(); i++) // print the data
  {
    string name;
    int id;
    int age;
    string job;
    int year;
    employees[i]->getInfo(&name, &id, &age, &job, &year);
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Age: " << age << endl;
    cout << "Job: " << job << endl;
    cout << "Hire year: " << year << endl;
    cout << "******************************" << endl;
  }

  return 0;
}