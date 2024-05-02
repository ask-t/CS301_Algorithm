#include<string>
using namespace std;

class Employee
{

  public:
    string name;
    string id;
    string age;
    string job;
    string year;
    Employee(string &n, string &i, string &a, string &j, string &y)
    {
      name = n;
      id = i;
      age = a;
      job = j;
      year = y;
    }

    /**
     * Retrieves the information of an employee.
     *
     * @param n Pointer to a string to store the employee's name.
     * @param i Pointer to an integer to store the employee's ID.
     * @param a Pointer to an integer to store the employee's age.
     * @param j Pointer to a string to store the employee's job.
     * @param y Pointer to an integer to store the employee's year of employment.
     */

    void getInfo(string *n, string *i, string *a, string *j, string *y)
    {
      *n = name;
      *i = id;
      *a = age;
      *j = job;
      *y = year;
    }

    string getID()
    {
      return id;
    }

};