#include <iostream>
#include <random>
#include <chrono>
#include <math.h>
using namespace std;
using namespace std::chrono;

// Founction to get an array of random numbers
int *getRandom(int A[], int n)
{
    // range of random numbers
    int range_from = 0;
    int range_to = 500000;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);

    for (int i = 0; i < n; ++i)
    {
        A[i] = distr(generator); // creating an array of random numbers
    }
    return A;
}
/* Function to sort an Array using insertion sort*/
void insertionSort(int A[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = A[i];
        int j = i - 1;

        /* Move elements of A[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}
// A utility function to print an array of size n
void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

int main()
{
    int M = 10; // highest size
    int n;           // size of array

    for (n = 10; n <= M; n = n * 10)
    {
        cout << "Sorting array of size " << n << endl; // prints size of array

        int B[n];
        int *A = getRandom(B, n);

        cout << "Unsorted array" << endl; printArray(A,n);

        auto start = high_resolution_clock::now(); // clock starting point
        insertionSort(A, n);
        auto stop = high_resolution_clock::now(); // clock stoping point

        auto totalTime_int = duration_cast<nanoseconds>(stop - start); // getting the total time with specified unit as an interger
        duration<double> totalTime_double = stop - start;              // getting the total time as double

        cout << "Sorted array" << endl; printArray(A,n);

        cout << "Time taken by the Algorithm: " << totalTime_int.count() << " ns" << endl;
        cout << "Time taken by the Algorithm: " << totalTime_double.count() << " s" << endl;
    }
    return 0;
}
