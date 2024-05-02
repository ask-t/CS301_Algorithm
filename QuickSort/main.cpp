#include <bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;

int comparisons = 0;
vector<Employee *> employees;

/**
 * Reads employee data from the given input file stream and populates the vector of employees.
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

/**
 * Prints the IDs of all employees in the "employees" vector.
 */
void logging()
{
	for (int k = 0; k < employees.size(); k++)
	{
		cout << employees[k]->id << " ";
	}
	cout << endl;
}

/**
 * Creates a file named "sorted.txt" and writes the employee data to it.
 * The employee data includes the name, ID, age, job, and year of each employee.
 */
void create()
{
	ofstream ofs("sorted.txt");
	for (int i = 0; i < employees.size(); i++)
	{
		ofs << employees[i]->name << "|" << employees[i]->id << "|" << employees[i]->age << "|" << employees[i]->job << "|" << employees[i]->year << endl;
	}
}
/**
 * @brief Partitions the array of employees based on a pivot element.
 *
 * @param low The starting index of the partition.
 * @param high The ending index of the partition.
 * @return The index of the pivot element after partitioning.
 */
int partition(int low, int high)
{
	Employee *pivot = employees[high]; // Pivot
	int i = low - 1;
	for (int j = low; j <= high - 1; j++)
	{
		comparisons++;
		// Assuming you're sorting by ID as an example
		if (stoi(employees[j]->id) < stoi(pivot->id))
		{
			i++;
			swap(employees[i], employees[j]);
			// logging();
		}
	}
	swap(employees[i + 1], employees[high]);
	// logging();
	return (i + 1);
}

/**
 * @brief Sorts an array using the QuickSort algorithm.
 *
 * @param low The starting index of the array.
 * @param high The ending index of the array.
 */
void quicksort(int low, int high)
{
	if (low < high)
	{
		int pi = partition(low, high);

		quicksort(low, pi - 1);
		quicksort(pi + 1, high);
	}
}

int randomizedPartition(int low, int high)
{
	// Generating a random number between low and high
	int random = low + rand() % (high - low);

	// Swapping the random element with the last to use it as a pivot
	swap(employees[random], employees[high]);

	return partition(low, high); // Use the original partition logic
}

void randomizedQuicksort(int low, int high)
{
	if (low < high)
	{
		int pi = randomizedPartition(low, high);

		randomizedQuicksort(low, pi - 1);
		randomizedQuicksort(pi + 1, high);
	}
}

void tailRecursiveQuicksort(int low, int high)
{
	while (low < high)
	{
		int pi = partition(low, high);

		// Tail recursive optimization - sort the smaller part using recursion
		// and iterate for the larger part to reduce the height of recursion tree
		if (pi - low < high - pi)
		{
			tailRecursiveQuicksort(low, pi - 1);
			low = pi + 1;
		}
		else
		{
			tailRecursiveQuicksort(pi + 1, high);
			high = pi - 1;
		}
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
	// quicksort(0, employees.size() - 1); // Call to quicksort
	// randomizedQuicksort(0, employees.size() - 1);
	tailRecursiveQuicksort(0, employees.size() - 1);
	cout << "It took " << comparisons << " comparisons to sort this list." << endl;
	// create();
	return 0;
}