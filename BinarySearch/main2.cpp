#include <bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;

/**
 * Reads employee data from the input file stream and populates the vector of employees.
 *
 * @param ifs The input file stream to read from.
 * @param employees The vector of Employee pointers to populate.
 */

void getEmployees(ifstream &ifs, vector<Employee *> &employees)
{
  string size;
  getline(ifs, size);
  struct
  {
    string name, id, age, job, year;
  } employee;

  for (int i = 0; i < stoi(size); i++) // read the number of employees
  {
    getline(ifs, employee.name, '|');
    getline(ifs, employee.id, '|');
    getline(ifs, employee.age, '|');
    getline(ifs, employee.job, '|');
    getline(ifs, employee.year);
    Employee *emp = new Employee(employee.name, employee.id, employee.age, employee.job, employee.year);
    employees.push_back(emp); // add the employee to the vector
  }
}

/**
 * Performs a sequential search on a vector of Employee objects.
 *
 * @param ifs The input file stream to read the search query and targets from.
 * @param employees The vector of Employee objects to search through.
 */

void binarySearch(ifstream &ifs, vector<Employee *> &employees)
{
  string query;
  getline(ifs, query);
  int size = employees.size();
  int total = 0;

  for (int i = 0; i < stoi(query); i++)
  {
    int comparisons = 0;
    int low = 0;
    int high = size - 1;
    string target;
    getline(ifs, target);
    int total = 0;
    while (low <= high)
    {
      int mid = (low + high) / 2;
      comparisons++;
      Employee *emp = employees[mid];
      string id = emp->getID();
      if (id == target)
      {
        string name, id, age, job, year;
        total += comparisons;
        emp->getInfo(&name, &id, &age, &job, &year);
        cout << "FOUND: Name: " << name << ", Age: " << age << ", Job: " << job << ", Hired: " << year << endl;
        cout << "at index " << mid << " after " << comparisons << " comparisons." << endl;
        break;
      }
      else if (id < target)
      {
        low = mid + 1;
      }
      else
      {
        high = mid - 1;
      }
      total++;
    }
  }
  double average = (double)total / (double)stoi(query); // calculate the average
  cout << fixed << "Done! Average amount of work per query: " << average << " comparisons." << endl;
}

int main(int argc, char *argv[])
{
  ifstream ifs(argv[1]); // input file stream
  if (argc < 2)          // if no command line argument is given
  {
    cerr << "Missing command line argument" << endl;
    cerr << "Usage: " << argv[0] << " <filename.txt>" << endl;
    return 1;
  }

  if (!ifs.is_open()) // if the file cannot be opened
  {
    cerr << "Could not open file: " << argv[1] << endl;
    return 1;
  }

  vector<Employee *> employees;
  getEmployees(ifs, employees);
  binarySearch(ifs, employees);
  ifs.close();

  return 0;
}