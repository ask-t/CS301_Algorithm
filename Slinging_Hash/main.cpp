#include <bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;

string m, n;
vector<Employee *> employees;
vector<Employee *> hashTable;
vector <vector<int>> hashTable2;
int collisions = 0;
int collisionResolve = 0;
double A = (sqrt(5) - 1) / 2;

void getEmployees(ifstream &ifs, vector<Employee *> &employees)
{
  struct
  {
    string name, id, age, job, year;
  } employee;

  for (int i = 0; i < stoi(n); i++)
  {
    getline(ifs, employee.name, '|');
    getline(ifs, employee.id, '|');
    getline(ifs, employee.age, '|');
    getline(ifs, employee.job, '|');
    getline(ifs, employee.year);
    Employee *emp = new Employee(employee.name, employee.id, employee.age, employee.job, employee.year);
    employees.push_back(emp);
  }
}

/**
 * @brief Inserts an employee into the hash table at the specified index.
 *
 * This function attempts to hash an employee object at the given index in the hash table.
 * If the index is empty, the employee is successfully inserted.
 * If there is a collision at the index, the collision count is incremented.
 * 
 * @param index The index in the hash table where the employee should be inserted.
 * @param e A pointer to the Employee object to be inserted.
 */
void result(int index, Employee *e)
{
  cout << "Attempting to hash " << e->name << " at index " << index << "...";
  if (hashTable[index] == nullptr)
  {
    cout << " SUCCESS!" << endl;
    hashTable[index] = e;
  }
  else
  {
    cout << "OUCH! Collision with " << hashTable[index]->name << "!" << endl;
    collisions++;
  }
}

/**
 * Resolves collisions by adding an employee to the hash table at the specified index.
 * If there are already elements at the index, collisionResolve counter is incremented.
 * 
 * @param index The index in the hash table where the employee should be added.
 * @param e Pointer to the Employee object to be added.
 */
void colisionResolution(int index, Employee *e)
{
  int length = hashTable2.at(index).size();  // for checking if there are already elements at the index
  if(length > 0) // if there is collision
  {
    collisionResolve++;
  }
  hashTable2.at(index).push_back(stoi(e->id));
  cout << "Adding " << e->name << " to table at index " << index << " ("<< length  << " collisions)" << endl;
}

/**
 * Calculates the remainder of dividing an integer by a given value.
 * 
 * @param k The integer to be divided.
 * @return The remainder of dividing k by m.
 */
int devision (int k)
{
  return k % stoi(m);
}

/**
 * Calculates the result of multiplying the input parameter `k` with a constant value `A`,
 * and then taking the fractional part of the product.
 * 
 * @param k The input value to be multiplied with `A`.
 * @return The result of multiplying `k` with `A` and taking the fractional part.
 */
int multiple(int k)
{
  return (int)(stoi(m)* fmod(k*A, 1.0));
}

/**
 * Detects collisions for the given employee.
 * 
 * @param e The employee object to check for collisions.
 */
void colisionDetect(Employee *e)
{
  int index = devision(stoi(e->id));
  // result(index, e);
  colisionResolution(index, e);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Missing command line argument" << endl;
    cerr << "Usage: " << argv[0] << " <filename.txt>" << endl;
    return 1;
  }

  ifstream ifs(argv[1]);
  if (!ifs.is_open())
  {
    cerr << "Could not open file: " << argv[1] << endl;
    return 1;
  }

  getline(ifs, m);
  getline(ifs, n);
  getEmployees(ifs, employees);
  hashTable.resize(stoi(m)); // initialize hashTable
  hashTable2.resize(stoi(m)); // initialize hashTable2

  for (int i=0; i<stoi(m); i++) // initialize hashTable2
  {
    hashTable2.push_back(vector<int>());
  }

  for (auto &e : employees) // check collisions and add the data to hashTable
  {
    colisionDetect(e);
  }
  cout << "Total collisions: " << collisions << endl;
  cout << "Total collisions to resolve: " << collisionResolve << endl;

  return 0;
}