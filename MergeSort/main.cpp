#include <bits/stdc++.h>
#include "../Header/Employee.h"
using namespace std;

int comparisons = 0;
/**
 * Reads employee data from an input file stream and populates a vector of Employee pointers.
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
		Employee *emp = new Employee(employee.name, employee.id, employee.age, employee.name, employee.year);
		employees.push_back(emp);
	}
}





/**
 * Merges two subarrays of the given vector.
 *
 * @param vec The vector containing the subarrays to be merged.
 * @param left The starting index of the first subarray.
 * @param mid The ending index of the first subarray.
 * @param right The ending index of the second subarray.
 */

void merge(vector<Employee *> &vec, int const left, int const mid, int const right)
{
	cout << "begin: " << left << " mid: " << mid << " end: " << right << endl;

	int const subArrayOne = mid - left + 1; // length of A[p: q]
	int const subArrayTwo = right - mid;		 // length of A[q + 1:r]

	// Create temp arrays
	vector<Employee *> leftArray(subArrayOne), rightArray(subArrayTwo);

	// Copy data to temp arrays
	for (int i = 0; i < subArrayOne; i++)
		leftArray[i] = vec[left + i]; // copy A[p: q] into L[O: nL - 1]
	for (int j = 0; j < subArrayTwo; j++)
		rightArray[j] = vec[mid + 1 + j]; // copy A[q + 1:r] into R[O:nR - 1]

	int indexOfSubArrayOne = 0,	 // Initial index of first sub-array
			indexOfSubArrayTwo = 0;		 // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into vec[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
	{
		comparisons++;
		if (stoi(leftArray[indexOfSubArrayOne]->id) <= stoi(rightArray[indexOfSubArrayTwo]->id))
		{
			vec[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else
		{
			vec[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of leftArray, if there are any
	while (indexOfSubArrayOne < subArrayOne)
	{
		vec[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
		comparisons++;
	}

	// Copy the remaining elements of rightArray, if there are any
	while (indexOfSubArrayTwo < subArrayTwo)
	{
		vec[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
		comparisons++;
	}
}

/**
 * Sorts the given vector of Employee pointers using the merge sort algorithm.
 * The sorting is done in ascending order based on the employee ID.
 *
 * @param vec The vector of Employee pointers to be sorted.
 * @param const begin The start index of the vector to be sorted.
 * @param const end The end index of the vector to be sorted.
 */
void mergeSort(vector<Employee *> &vec, int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively
	int mid = begin + (end - begin) / 2;
	mergeSort(vec, begin, mid);
	mergeSort(vec, mid + 1, end);
	merge(vec, begin, mid, end);
	int size = vec.size();
	// for (int k = 0; k < size; k++) // show logs
	// {
	// 	cout << vec[k]->id << " ";
	// }
	// cout << endl;
	// ofstream ofs("sorted.txt");
	// for (int i = 0; i < size; i++)
	// {
	// 	ofs << vec[i]->name << "|" << vec[i]->id << "|" << vec[i]->age << "|" << vec[i]->job << "|" << vec[i]->year << endl;
	// }
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
	if (argc < 2)					 // if no command line argument is given
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
	mergeSort(employees, 0, employees.size() - 1);
	cout << "It took " << comparisons << " comparisons to sort this list." << endl;

	return 0;
}