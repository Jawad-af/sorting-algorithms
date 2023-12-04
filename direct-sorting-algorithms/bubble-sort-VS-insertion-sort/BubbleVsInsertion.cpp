


// Student Name: JAWAD ABO FAKHER.
// Group: 30411 - Calculatoare Engleza.




/*
Based on the operation counters analysis values and the chart representing them, we deduce that:
 - Both algorithms are closed to each others by means of time complexity, however on big size
    vectors > 50000 elements the bubble sort tends to be faster and more efficient!!
    which is unusual, the algorithm might has some issues with the implementation.

 - The insertion sort seems to increase in a more stable and curvey manner, on the other hand,
   bubble sort algorithm's operation counters assignments vary based on the input value.

 - Overall "if we consider that the analysis and the algorithms implementations are done correctly"
   we can see that the algorithms seem to behave the same in Best, Worst as well as the Average case.

*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Profiler.h"

#define MAX_SIZE 1000
#define STEP_SIZE 10


Profiler profiler("BubbleSortVSInsertionSort");



void InsertionSort(int arr[], int n) {

    Operation compOp = profiler.createOperation("Comparisons insertionSort", n);
    Operation attrOp = profiler.createOperation("Assignments insertionSort", n);

    for (int j = 1; j < n; j++) {
        attrOp.count();
        int key = arr[j];
        attrOp.count();
        int i = j - 1;
        while (i > 0) {
            compOp.count();
            if (arr[i] >= key)
            {
                attrOp.count();
                arr[i + 1] = arr[i];
            }
            attrOp.count();
            i -= 1;
        }
        attrOp.count();
        arr[i + 1] = key;
    }
}



void BubbleSort(int arr[], int n) {

    Operation opComp = profiler.createOperation("Comparisons BubbleSort", n);
    Operation opAttr = profiler.createOperation("Assignments BubbleSort", n);


    //**** The commented section is used to compare the enhanced bubble sort with the normal one.
    //bool flag; // The flag is used to check whether the elements of the array are
                // already sorted or not. => it decreases the time complexity of the alg.
    int i, j;

    for (int i = 0; i < n - 1; i++) {
        //opAttr.count();
        //flag = false;
        for (int j = 0; j < n - i - 1; j++) {
            opComp.count();
            if (arr[j] > arr[j + 1]) {
                opAttr.count();
                int temp = arr[j];
                opAttr.count();
                arr[j] = arr[j + 1];
                opAttr.count();
                arr[j + 1] = temp;
                // opAttr.count();
                 //flag = true;
            }
        }
        //opAttr.count();
        //if (!flag)
            //break;
    }
}



int InsertionBinarySearch(int arr[], int key, int L, int R, int n) {

    Operation compOp = profiler.createOperation("Comparisons BinaryInsertionSort", n);
    Operation attrOp = profiler.createOperation("Assignments BinaryInsertionSort", n);

    compOp.count();
    if (L >= R)
    {
        compOp.count();
        if (key > arr[L])
            return L + 1;
        else return L;
    }
    else {
        attrOp.count();
        int mid = L + (R - L) / 2;

        compOp.count();
        if (arr[mid] == key) {
            return mid + 1;
        }
        compOp.count();
        if (arr[mid] > key) {
            return InsertionBinarySearch(arr, key, L, mid - 1, n);
        }
        else {
            return InsertionBinarySearch(arr, key, mid + 1, R, n);
        }
    }
}


void BinaryInsertionSort(int arr[], int n) {

    Operation compOp = profiler.createOperation("Comparisons BinaryInsertionSort", n);
    Operation attrOp = profiler.createOperation("Assignments BinaryInsertionSort", n);

    for (int i = 1; i < n; i++) {
        attrOp.count();
        int j = i - 1;
        attrOp.count();
        int key = arr[i];
        attrOp.count();
        int index = InsertionBinarySearch(arr, key, 0, j, n);
        while (j >= index) {
            attrOp.count();
            arr[j + 1] = arr[j];
            attrOp.count();
            j--;
        }
        attrOp.count();
        arr[j + 1] = key;
    }
}





void demo() {
    int arr[] = { 2,6,7,8,9,5,4,3,5,6,7,7,0,3,5,-5,0,-33,-22,-5,-9,-2,6,5,0,33,2,7,6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Unsorted: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    BubbleSort(arr, n);

    printf("\nAfter applying Bubble Sort: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    int arr2[] = { 2,6,7,8,9,5,4,3,5,6,7,7,0,3,5,-5,0,-33,-22,-5,-9,-2,6,5,0,33,2,7,6 };

    InsertionSort(arr2, n);

    printf("\nAfter applying Insertion Sort: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    int arr3[] = { 2,6,7,8,9,5,4,3,5,6,7,7,0,3,5,-5,0,-33,-22,-5,-9,-2,6,5,0,33,2,7,6 };

    BinaryInsertionSort(arr3, n);

    printf("\nAfter applying Binary Insertion Sort: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

void performance(int order) {
    int vector1[MAX_SIZE];
    int vector2[MAX_SIZE];
    int vector3[MAX_SIZE];
    int vectorSimplu[MAX_SIZE];
    int i;
    for (i = STEP_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            FillRandomArray(vectorSimplu, i);
            vector1[i] = vector2[i] = vector3[i] = vectorSimplu[i];
        }
        InsertionSort(vector1, i);
        BubbleSort(vector2, i);
        BinaryInsertionSort(vector3, i);
    }
    profiler.addSeries("BubbleSort Sort", "Comparisons BubbleSort", "Assignments BubbleSort");
    profiler.addSeries("Insertion Sort", "Comparisons insertionSort", "Assignments insertionSort");
    profiler.addSeries("Binary Insertion Sort", "Comparisons BinaryInsertionSort", "Assignments BinaryInsertionSort");
    profiler.createGroup("Insertion VS Bubble VS Binary Insertion OVERALL COMPARASION", "BubbleSort Sort", "Insertion Sort", "Binary Insertion Sort");

    profiler.createGroup("Comparasions", "Comparisons BubbleSort", "Comparisons insertionSort", "Comparisons BinaryInsertionSort");
    profiler.createGroup("Assignments", "Assignments BubbleSort", "Assignments insertionSort", "Assignments BinaryInsertionSort");
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


int main() {

    demo();
    AllPerformances();
    return 0;
}


