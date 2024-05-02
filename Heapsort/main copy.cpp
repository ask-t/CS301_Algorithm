#include <bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;

int comparisons = 0;
int heapSize;
vector<Employee *> employees;

void getEmployees(ifstream &ifs, vector<Employee *> &employees)
{
	string size;
	getline(ifs, size);
	struct
	{
		string name, id, age, job, year;
	} employee;

	for (int i = 0; i < stoi(size); i++)
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

void heapify(int i)
{
	int largest = i;	 // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * (i + 1); // right = 2*i + 2

	comparisons++;
	// If left child is larger than root
	if (l < heapSize && stoi(employees[l]->id) > stoi(employees[largest]->id))
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	comparisons++;
	// If right child is larger than largest so far
	if (r < heapSize && stoi(employees[r]->id) > stoi(employees[largest]->id))
	{
		largest = r;
	}

	// If largest is not root
	if (largest != i)
	{
		swap(employees[i],employees[largest]);
		// Recursively heapify the affected sub-tree
		heapify(largest);
	}
}

void buildMaxHeap()
{
	heapSize = employees.size(); // Initialize heap size
	for (int i = heapSize / 2 - 1; i >= 0; i--) // Build heap (rearrange array)
	{
		heapify(i);
	}
}
void logging()
{
	for (int k = 0; k < employees.size(); k++)
	{
		cout << employees[k]->id << " ";
	}
	cout << endl;
}

void heapSort()
{
	logging();
	buildMaxHeap();
	logging();
	for (int i = heapSize - 1; i > 0; i--) // One by one extract an element from heap
	{
		// Move current root to end
		swap(employees[0], employees[i]);
		heapSize--; // Reduce the heap size
		// Call max heapify on the reduced heap
		heapify(0);
		logging();
	}
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

	getEmployees(ifs, employees);
	heapSize = employees.size();
	heapSort();
	cout << "It took " << comparisons << " comparisons to sort this list." << endl;

	return 0;
}