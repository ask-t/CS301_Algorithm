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
 * Sorts a vector of strings using the bubble sort algorithm.
 * = (N-1) + (N-2) +  (N-3) + . . . 2 + 1
 * = (N-1)*(N-1+1)/2  { by using sum of N natural Number formula }
 * = (N * (N-1)) / 2
 * = O(n^2)
 * @param vec The vector of strings to be sorted.
 */
void bubbleSort(vector<Employee *> &vec)
{
  int size = vec.size();
  int comparisons = 0;
  for (int i = 0; i < size; i++) // for i =1 to n - 1
  {
    for (int j = size-1; j > i; j--) // for j = n downto i+1
    {

      if(stoi(vec[j]->id) < stoi(vec[j-1]->id)) // if A[j] < A[j -1]
      {
        swap(vec[j], vec[j-1]); // exchange
      }
      for (int k = 0; k < size; k++)
      {
        cout << vec[k]->id << " ";
        if (k == size-1)
        {
          cout << endl;
        }
      }
      comparisons++; // O(n^2)
    }
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
  bubbleSort(employees);

  return 0;

}