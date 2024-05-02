#include <bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;




/**
 * Reads employee data from the input stream and populates the vector of employees.
 *
 * @param ifs The input stream to read from.
 * @param employees The vector of Employee pointers to populate.
 */

void getEmployees(istream &ifs, vector<Employee *> &employees)
{
  string size;
  getline(ifs, size); // Get the first line of the file
  string name, id, age, job, year;
  while (ifs.good()) // make a loop to get the data from the file
  {
    getline(ifs, name, '|');
    getline(ifs, id, '|');
    getline(ifs, age, '|');
    getline(ifs, job, '|');
    getline(ifs, year);
    Employee *emp = new Employee(name, id, age, job, year);
    employees.push_back(emp);
  }
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
  vector<Employee *> employees;
  getEmployees(ifs, employees);
  ifs.close();

  for (int i = 0; i < employees.size(); i++) // print the data
  {
    string name, id, age,job, year;
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