#include <stdio.h>
#include <stdlib.h>
#include "Profiler.h"

Profiler profiler("HybridQuickSort");
#define MAX_INSERTION_SORT 30
#define ARRAY_MAX_SIZE 10000
#define STEP_SIZE 100

int quickSortOpCount = 0;

void insertionSort(int array[], int beg, int end) 
{
    for (int i = beg + 1; i < end + 1; i++) {
        int key = array[i];
        int j = i;
        while (j > beg && array[j - 1] > key) {
            quickSortOpCount++;
            array[j] = array[j - 1];
            j -= 1;
        }
        array[j] = key;
    }
}

int partition(int array[], int beg, int end) 
{

	int pivot = end;
	int i = beg - 1;

	for (int j = beg; j <= end - 1; j++)
	{
        quickSortOpCount++;
		if (array[pivot] >= array[j])
		{
            quickSortOpCount += 3;
			i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
		}
	}
    quickSortOpCount += 3;
    int temp = array[i + 1];
    array[i + 1] = array[pivot];
    array[pivot] = temp;
	return i + 1;
}

void quickSort(int array[], int beg, int end) 
{
    if (beg < end) {
        int pivot = partition(array, beg, end);
        quickSort(array, beg, pivot - 1);
        quickSort(array, pivot + 1, end);
    }
}

void quickSortHybirdization(int array[], int beg, int end) 
{
    while (beg < end) {

        quickSortOpCount++;
        if (end - beg + 1 <= MAX_INSERTION_SORT) {
            insertionSort(array, beg, end);
            break;
        }
        else {
            quickSortOpCount++;
            int pivot = partition(array, beg, end);

            // sort the part of the array that comes before the pivot and the part of the array after the pivot
            quickSortHybirdization(array, beg, pivot - 1);
            quickSortHybirdization(array, pivot + 1, end);

            // update the boundaries
            beg = pivot + 1;
            end = pivot - 1;
        }
    }
}


//-------------------------------------------------- down below is the implementation of the normal quick sort from assignment 3

int normalQuickSortOpCount = 0;

void Swap(int* a, int* b, int n)
{
    normalQuickSortOpCount += 3;
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int arr[], int n, int beg, int end)
{

    int pivot = end;
    int i = beg - 1;

    for (int j = beg; j <= end - 1; j++)
    {
        normalQuickSortOpCount++;
        if (arr[pivot] >= arr[j])
        {
            i++;
            Swap(&arr[i], &arr[j], n);
        }
    }
    Swap(&arr[i + 1], &arr[pivot], n);
    return i + 1;
}

void QuickSort(int arr[], int n, int beg, int end) {
    if (beg < end) {
        int q = Partition(arr, n, beg, end);
        QuickSort(arr, n, beg, q - 1);
        QuickSort(arr, n, q + 1, end);
    }
}

void normalQuickSortAlgorithm(int arr[], int n) {
    QuickSort(arr, n, 0, n - 1);
}

void performance()
{
    int array[ARRAY_MAX_SIZE];
    int array2[ARRAY_MAX_SIZE];

    for (int test = 0; test < 5; test++)
    {
        for (int i = STEP_SIZE; i < ARRAY_MAX_SIZE; i += STEP_SIZE)
        {
            FillRandomArray(array, i, 10, 50000, false, 0);
            quickSortOpCount = 0;
            quickSortHybirdization(array, 0, i - 1);
            profiler.countOperation("Hybrid Quick Sort", i, quickSortOpCount);

            profiler.startTimer("Hybrid Quick Sort", i);
            for (int test2 = 0; test2 < 100; ++test2) {
                quickSortHybirdization(array,0, i);
            }
            profiler.stopTimer("Hybrid Quick Sort", i);

            FillRandomArray(array2, i, 10, 50000, false, 0);
            normalQuickSortOpCount = 0;
            normalQuickSortAlgorithm(array2, i);
            profiler.countOperation("Normal Quick Sort", i, normalQuickSortOpCount);


            profiler.startTimer("Normal Quick Sort", i);
            for (int test2 = 0; test2 < 100; ++test2) {
                normalQuickSortAlgorithm(array, i);
            }
            profiler.stopTimer("Normal Quick Sort", i);
        }
    }

    profiler.divideValues("Hybrid Quick Sort", 5);
    profiler.divideValues("Normal Quick Sort", 5);
    profiler.createGroup("Both Algorithms", "Hybrid Quick Sort", "Normal Quick Sort");
    profiler.showReport();
}

int main() {
    int array[] = { -1,0,23,423,4,235,23,0,-534,-63,46,346,354,63,-45,346,34,6,345,34,-634,6,45,-75,68,678,5645,7634,563,-52,35,35,756,8,578,543 };

    int n = sizeof(array) / sizeof(array[0]);
    quickSortHybirdization(array, 0, n-1);

    for (int i = 0; i < n; i++)
        printf("%d, ", array[i]);

    performance();

    return 0;
}


