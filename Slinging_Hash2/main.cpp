#include <bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;

string m, n;
vector<Employee *> employees;
vector <vector<Employee *>> hashTable;
int collisions = 0;
int collisionResolve = 0;
double A = (sqrt(5) - 1) / 2;
int total = 0;
Employee *employ;

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
 * Converts a string to an integer hash value.
 * The hash value is calculated using the polynomial rolling hash function.
 * @param s The string to convert.
 * @return The integer hash value of the string.
 */
int string2int(const string &s)
{
  const int p = 31;      // Prime number close to the number of characters in your alphabet
  const int m = 1e9 + 9; // A large prime number to take modulo with
  long long hash_value = 0;
  long long p_pow = 1; // p^0 initially

  for (char c : s)
  {
    hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m; // Adjust for character offset and modulo m to keep within int range
    p_pow = (p_pow * p) % m;                               // Next power of p
  }

  return static_cast<int>(hash_value);
}


/**
 * Resolves collisions by adding an employee to the hash table at the specified index.
 * If there are already elements at the index, collisionResolve counter is incremented.
 * @param index The index in the hash table where the employee should be added.
 * @param e Pointer to the Employee object to be added.
 */
void colisionResolution(int index, Employee *e)
{
  int length = hashTable.at(index).size();  // for checking if there are already elements at the index
  if(length > 0) // if there is collision
  {
    collisionResolve++;
  }
  hashTable.at(index).push_back(e);
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
  k = abs(k);
  int a = (int)(stoi(m)* fmod(k*A, 1.0));
  cout << "Index for " << k << " is " << a << endl;
  return a;
}

/**
 * Detects collisions for the given employee.
 * @param e The employee object to check for collisions.
 */
void colisionDetect(Employee *e)
{
  int nameToHash = string2int(e->name);
  int index = multiple(nameToHash);
  colisionResolution(index, e);
}

/**
 * Compares the target string with the names of employees stored in the hash table.
 * 
 * @param ifs The input file stream containing the target string.
 * @param index2 The index of the target string in the hash table.
 * @return True if the target string is found in the hash table, false otherwise.
 */
bool compare(ifstream &ifs, int &index2)
{
  string target;
  getline(ifs, target);
  int targetHash = string2int(target);
  int index = multiple(targetHash);
  index2 = index;
  vector<Employee *> emp = hashTable.at(index);
  int count = 0;
  for (auto &e : emp)
  {
    if (e->name == target)
    {
      total += count;
      employ = e;
      return true;
    }
    else
    {
      count++;
    }
  }
  return false;
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
  hashTable.resize(stoi(m));
  getline(ifs, n);
  getEmployees(ifs, employees);

  for (auto &e : employees) // check collisions and add the data to hashTable
  {
    colisionDetect(e);
  }

  string line;
  getline(ifs,line);
  if(line == "***")
  {
    string input;
    getline(ifs, input);
    int q = stoi(input);
    for(int i=0; i<q; i++)
    {
      int index;
      if(compare(ifs, index))
      {
        cout << "Found " << employ->name << " after " << total << " collisions at index " << index << " in the hashtable." << endl;
        cout << "COMPLETE RECORD: " << employ->name << "|" << employ->id << "|" << employ->age << "|" << employ->job << "|" << employ->year << endl;
      }
      else
      {
        cout << "Not found" << endl;
      }
    }
  }
  cout << "Total collisions during lookup phase: " << total << endl;

  return 0;
}