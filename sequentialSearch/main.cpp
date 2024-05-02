#include<bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;


/**
 * Reads employee data from the input file stream and populates the vector of employees.
 *
 * @param ifs The input file stream to read from.
 * @param employees The vector of Employee pointers to populate.
 */

void getEmployees(ifstream &ifs, vector<Employee*> &employees)
{
  string size;
  getline(ifs, size);
  struct
  {
    string name,id,age,job,year;
  } employee;

  for(int i=0; i<stoi(size); i++) // read the number of employees
  {
    getline(ifs, employee.name, '|');
    getline(ifs, employee.id, '|');
    getline(ifs, employee.age, '|');
    getline(ifs, employee.job, '|');
    getline(ifs, employee.year);
    Employee *emp = new Employee(employee.name, employee.id,employee.age,employee.job,employee.year);
    employees.push_back(emp); // add the employee to the vector
  }
}


/**
 * Performs a sequential search on a vector of Employee objects.
 * 
 * @param ifs The input file stream to read the search query and targets from.
 * @param employees The vector of Employee objects to search through.
 */

void search(ifstream &ifs, vector<Employee*> &employees)
{
  string query;
  int size = employees.size();
  getline(ifs,query);
  int total = 0;
  for(int i=0; i<stoi(query); i++)
  {
    string target;
    getline(ifs, target);
    for(int i=0; i<size;i++) // liner search
    {
      Employee* emp = employees[i];
      if(emp->getID() == target) // if the employee is found
      {
        string name, id, age, job, year;
        int comparisons = i+1;
        total += comparisons;
        emp->getInfo(&name,&id,&age,&job,&year);
        cout << "FOUND: Name: " << name <<", Age: " << age << ", Job: " << job << ", Hired: " << year << endl;
        cout << "at index " << i << " after " << i+1 << " comparisons." << endl;
      }
    }
  }
  double average = (double)total / (double)stoi(query); // calculate the average
  cout << fixed <<"Done! Average amount of work per query: " << average << " comparisons." << endl;
}

int main(int argc, char *argv[])
{
  ifstream ifs(argv[1]); // input file stream
  if(argc < 2) // if no command line argument is given
  {
    cerr << "Missing command line argument" << endl;
    cerr << "Usage: " << argv[0] << " <filename.txt>" <<endl;
    return 1;
  }

  if(!ifs.is_open()) // if the file cannot be opened
  {
    cerr << "Could not open file: " << argv[1] << endl;
    return 1;
  }

  vector<Employee* > employees;
  getEmployees(ifs,employees);
  search(ifs,employees);
  ifs.close();

  return 0;
}