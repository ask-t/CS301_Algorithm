#include<bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;



/**
 * Reads employee data from an input file stream and populates a vector of Employee pointers.
 *
 * @param ifs The input file stream to read from.
 * @param employees The vector of Employee pointers to populate.
 */
void getEmployees(ifstream &ifs, vector<Employee*> &employees)
{
  string size;
  getline(ifs,size);
  struct
  {
    string name, id,age,job,year;
  }employee;

  for (int i = 0; i < stoi(size); i++) // read the number of employees
  {
    getline(ifs,employee.name,'|');
    getline(ifs,employee.id,'|');
    getline(ifs,employee.age,'|');
    getline(ifs,employee.job,'|');
    getline(ifs,employee.year);
    Employee *emp = new Employee(employee.name, employee.id, employee.age, employee.name,employee.year);
    employees.push_back(emp);
  }
}



/**
 * Sorts a vector of Employee pointers using the insertion sort algorithm.
 *
 * @param vec The vector of Employee pointers to be sorted.
 */

void insertionSort(vector<Employee *> &vec)
{
  int size = vec.size();
  int comparisons = 0;
  for (int i = 1; i < size; i++) // 1 is second positi≠on
  {
    Employee *key = vec[i]; // set key
    int j = i - 1;
    while (j >= 0 and stoi(vec[j]->id) > stoi(key->id)) //exchange position until meeting the number less than target
    {
      vec[j+1] = vec[j];
      j = j - 1;
      comparisons++; // O(n^2)
    }
    vec[j + 1] = key;
    for (int k = 0; k < size; k++)
    {
      cout << vec[k]->id << " ";
    }
    cout << endl;
  }
  cout <<"It took " << comparisons << " comparisons to sort this list." << endl;
}


/**
 * @brief The main function of the program.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of command line arguments.
 * @return int The exit status of the program.
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
  getEmployees(ifs,employees);
  insertionSort(employees);

  return 0;

}