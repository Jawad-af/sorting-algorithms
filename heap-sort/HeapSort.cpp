

// STUDENT: JAWAD ABO FAKHER 
// GROUP: 30411 - CALCULATOARE - ENGLEZA

/*

		----Heapify (Botoom-Up) Approch Correctness Proof----


Initialization Phase: For the first iteration we have (i = n/2 -1) which is the index of the last
	non-leaf node, at the same time it is a parent for one or two leaf nodes.

Maintenance Phase: At this stage the loop iterates over the nodes starting from [(i=n/2 -1), (i=n/2 -2),
	(i=n/2 -3), (i=n/2 -4), .... 0], and it calls the Heapify(array, i) for each node/index.
	By finding the node's left and right child and comparing it checks for any violation of the max heap property,
	if so it performs a swap operation on the root node and it's childern, which makes the root the largest element.
	Decrementing the index in the loop maintain the loop invariant for the next iteration.

Termination Phase: When the index i=0, the nodes of the array [0:n-1] are roots of a max heap.



			---- Top-Down Approch Correctness Proof----


Initialization: The algorithm starts by adding the first element (Array[0]) of the array to the heap, using a
	for loop that iterates over the array[0:n-1], and adds them to the heap.

Maintenance: Starting from index i = 1 to n-1, the algorithm compares each element added to the last node
	in the heap with its parent to check and maintain heap property, if the element added is bigger than its
	parent a swap operation is applied over them, since the element added is smaller than the root the heap
	is already sorted.

Termination: At index i = n-1, all elements in the array are roots for a max heap.



				---- Heap Sort Correctness Proof----


Initialization: The heap sort starts by building a max-heap on the array[0:n-1] starting from the last
	non-leaf node found on index (i=n/2-1) till it reaches the root of the array.
	Another for loop takes the node on index (i=n-1), swap it with the root and apply
	Heapify algorithm to the new root element to maintain heap property, the index get decremented
	till it reaches the 0.

Maintenance: To see that each iteration maintains the loop invariant, we observe that the Heapify
	algorithm is applied each time after decrementing the the index, so that even if the new root vaiolates
	the max heap property, its then restored which leaves a max heap in array[i:0], and the element on the last
	position get ignored after each iteration. The heapsort algorithm then repeats this process for the
	max-heap of size n - 1 down to a heap of size 2, maintaining the loop invariant at each iteration.

Termination: The algorithm stops when the array is left with only two unsorted elements array[0:1]
	the index i indicates the termination of the algorithm at i=1




*/



#include <stdio.h>
#include <math.h>
#include "Profiler.h"

Profiler profiler("HeapSort");

#define MAX_SIZE 1000
#define STEP_SIZE 10
#define TESTS_NUMBER 5



void Swap(int* a, int* b, int n)
{
	Operation assignment = profiler.createOperation("Assignments Heapify", n);
	Operation assignmentTD = profiler.createOperation("Assignments TopDown", n);

	int temp = *a;
	*a = *b;
	*b = temp;
}

void Heapify(int arr[], int n, int index)
{
	Operation comparasion = profiler.createOperation("Comparasions Heapify", n);
	Operation assignment = profiler.createOperation("Assignments Heapify", n);

	int parent = index;
	int LeftChild = 2 * index + 1;
	int RightChild = 2 * index + 2;

	if (LeftChild < n) {
		comparasion.count();
		if (arr[LeftChild] > arr[parent]) {
			parent = LeftChild;
		}
	}

	if (RightChild < n) {
		comparasion.count();
		if (arr[RightChild] > arr[parent]) 
			parent = RightChild;
		}
	
	comparasion.count();
	if (arr[parent] != arr[index]) {
		//Swap(&arr[parent], &arr[index], n);
		assignment.count(3);
		int temp = arr[parent];
		arr[parent] = arr[index];
		arr[index] = temp;
		Heapify(arr, n, parent);
	}
}




void HeapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		Heapify(arr, n, i);
	}

	for (int i = n-1; i > 0; i--)
	{
		Swap(&arr[0], &arr[i], n);
		Heapify(arr, i, 0);
	}
}


void HeapCreation_TopDownApproach(int arr[], int n, int i) {

	Operation comparasionTD = profiler.createOperation("Comparasions TopDown", n);
	Operation assignmentTD = profiler.createOperation("Assignments TopDown", n);

	comparasionTD.count();
	if (i == 0)
		return;
	while (i > 0) {
		assignmentTD.count();
		int parent = (i - 1) / 2;
		comparasionTD.count();
		if (arr[i] > arr[parent]) {
			//Swap(&arr[i], &arr[parent], n);
			assignmentTD.count(3);
			int temp = arr[i];
			arr[i] = arr[parent];
			arr[parent] = temp;
			i = parent;
		}
		return;
	}
}


void demo() {

	int arr[] = { 10, -20, 15, 17, -9, 21,34,534,53,46,346,4,7,-3,0,0,0,0,-2,-34,-45,-45 };
	int n = sizeof(arr) / sizeof(arr[0]);

	
	for (int i = 0; i < n; i++)
		printf("%d  ", arr[i]);
	printf(" --> Main array\n\n");
	

	for (int i = n / 2 - 1; i >= 0; i--){	
		Heapify(arr, n, i);
	}

	
	for (int i = 0; i < n; i++)
		printf("%d  ", arr[i]);
	printf(" --> Heapify\n");
	int arr2[] = { 10, -20, 15, 17, -9, 21,34,534,53,46,346,4,7,-3,0,0,0,0,-2,-34,-45,-45 };
	
	
	for (int i = 0; i < n; i++)
		HeapCreation_TopDownApproach(arr2, n, i);

	
	for (int i = 0; i < n; i++)
		printf("%d  ", arr[i]);
	printf(" --> Top-Down\n\n");

	HeapSort(arr, n);
	
	for (int i = 0; i < n; i++)
		printf("%d  ", arr[i]);
	printf(" --> After applying Heap Sort\n");
	printf("\n\n\n\n\n\n\n");



}

void performance(int order) {

	int vector1[MAX_SIZE];
	int vector2[MAX_SIZE];
	int vectorSimplu[MAX_SIZE];
	int i;
	for (i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
		
		
		FillRandomArray(vectorSimplu, i);
		CopyArray(vector1, vectorSimplu, i);
		CopyArray(vector2, vectorSimplu, i);
		
		for (int j = 0; j < i; j++)
		{
		HeapCreation_TopDownApproach(vector1, i, j);
		Heapify(vector2, i, j);

		}
	}

	profiler.addSeries("Heapify", "Comparasions Heapify", "Assignments Heapify");
	profiler.addSeries("TopDown Approach", "Comparasions TopDown", "Assignments TopDown");
	profiler.createGroup("Heapify VS TopDown", "Heapify", "TopDown Approach");

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
	//AllPerformances();
	return 0;
}

