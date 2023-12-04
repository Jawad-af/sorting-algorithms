


// Student Name: JAWAD ABO FAKHER.
// Group: 30411 - Calculatoare Engleza.

// ** THE CODE IS PROVIDED WITH A PDF FILE THAT CONTAINS ALL THE THEORETICAL DISCUSSION **




#include <stdio.h>
#include "Profiler.h"

Profiler profiler("SelectionSort");
#define MAX_SIZE 10000
#define STEP_SIZE 100

void SelectionSort(int arr[], int n)
{
	Operation ComparasionOperation = profiler.createOperation("Comparasions", n);
	Operation AssignmentOperation = profiler.createOperation("Assignments", n);


	for (int i = 0; i < n; i++)
	{

		int min = i;
		int j = i + 1;

		while (j < n)
		{
			ComparasionOperation.count();
			if (arr[j] < arr[min]) {
				AssignmentOperation.count();
				min = j;
			}
			j++;
		}
		ComparasionOperation.count();
		if (arr[min] != arr[i])
		{
			AssignmentOperation.count();
			int temp = arr[min];
			AssignmentOperation.count();
			arr[min] = arr[i];
			AssignmentOperation.count();
			arr[i] = temp;
		}

	}
}

int MinimumIndex(int arr[], int i, int j)
{
	if (i == j)
		return i;

	int k = MinimumIndex(a, i + 1, j);

	if (arr[i] < arr[k])
		return i;
	else return k;
}

void SelectionSortRecursive(int arr[], int n, int index = 0)
{
	if (index == n)
		return;

	int k = MinimumIndex(arr, index, n - 1);

	if (k != index)
		swap(arr[k], arr[index]);

	recurSelectionSort(arr, n, index + 1);
}


void performance(int order)
{
	int vector[MAX_SIZE];
	int i;

	for (int i = STEP_SIZE; i < MAX_SIZE; i = i + STEP_SIZE)
	{
		FillRandomArray(vector, i, 10, 5000, false, order);
		SelectionSort(vector, i);
	}

	profiler.addSeries("SelectionSort Analysis", "Comparasions", "Assignments");
}


void demo()
{
	int arr[] = { 2,-5,4,3,3,5,5,6,78,-88,7,6,-5,44,3,4,5,-6,67,8, 0, 0 };
	int n = sizeof(arr) / sizeof(arr[0]);


	printf("Unsorted: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", arr[i]);
	}

	SelectionSort(arr, n);
	printf("\nAfter appling Selection Sort: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", arr[i]);
	}
}


void AllPerformances()
{
	performance(UNSORTED);
	profiler.reset("BEST");
	performance(ASCENDING);
	profiler.reset("WORST");
	performance(DESCENDING);

	profiler.showReport();
}

int main()
{
	demo();
	AllPerformances();

	return 0;
}