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
 * Performs a binary search on a vector of Employee objects.
 *
 * @param x The target to search for.
 * @param l The lower bound of the search range.
 * @param h The upper bound of the search range.
 * @param employees The vector of Employee objects to search through.
 * @param com The number of comparisons made during the search.
 * @return The index of the target in the vector, or -1 if the target is not found.
 */
int binarySearch(int x, int l, int h, vector<Employee *> &employees, double *com)
{
  int low = l;
  int high = h + 1;
  int target = x;
  double comparisons = 0;
  while(low < high)
  {
    int mid = (low + high) / 2;
    comparisons++;
    Employee *emp = employees[mid];
    int id = stoi(emp->getID());
    if(target <= id)
    {
      high = mid;
    }
    else
    {
      low = mid +1 ;
    }
  }
  *com = comparisons;
  return low;
}

/**
 * Performs a binary search on a vector of Employee objects.
 *
 * @param ifs The input file stream to read the search query and targets from.
 * @param employees The vector of Employee objects to search through.
 */

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
  cout << employees.size() << endl;
  string query;
  getline(ifs, query);
  int num = stoi(query);
  double total = 0;
  for(int i = 0; i < num; i++)
  {
    double comparisons = 0.0;
    string target;
    getline(ifs, target);
    for(int j = 0; j < employees.size(); j++)
    {
      int a = binarySearch(stoi(target), 0, employees.size() - 1, employees, &comparisons);
      if(a != -1)
      {
        string name, id, age, job, year;
        employees[a]->getInfo(&name, &id, &age, &job, &year);
        cout << "FOUND: Name: " << name << ", Age: " << age << ", Job: " << job << ", Hired: " << year << endl;
        cout << "at index " << a << " after " << comparisons << " comparisons." << endl;
        total += comparisons;
        break;
      }

    }
  }

  double average = total / (double)stoi(query); // calculate the average
  cout << fixed << "Done! Average amount of work per query: " << average << " comparisons." << endl;
}