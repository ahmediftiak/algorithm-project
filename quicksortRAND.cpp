#include <iostream>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

// function to swap elements
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// Founction to get an array of random numbers
int *getRandom(int A[], int n)
{
    // range of random numbers
    int range_from = 0;
    int range_to = 50000;

    random_device                   rand_dev;
    mt19937                         generator(rand_dev());
    uniform_int_distribution<int>   distr(range_from, range_to);

    for (int i = 0; i < n; ++i)
    {
        A[i] = distr(generator); // creating an array of random numbers
    }
    return A;
}

// function to print the array
void printArray(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
}

// function to rearrange array (find the partition point)
int partition(int A[], int p, int r)
{
    // select the rightmost element as pivot
    int pivot = A[r];

    // pointer for greater element
    int i = (p - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = p; j < r; j++)
    {
        if (A[j] <= pivot)
        {
            // if element smaller than pivot is found swap it with the greater element pointed by i
            i++;
            // swap element at i with element at j
            swap(&A[i], &A[j]);
        }
    }
    // swap pivot with the greater element at i
    swap(&A[i + 1], &A[r]);

    // return the partition point
    return (i + 1);
}

// Generates Random Pivot, swaps pivot with
// end element and calls the partition function
int partition_r(int A[], int p, int r)
{
    // Generate a random number in between
    // low .. high
    srand(time(NULL));
    int random = p + rand() % (r - p);

    // Swap A[random] with A[r]
    swap(A[random], A[r]);

    return partition(A, p, r);
}
void quickSort(int A[], int p, int r)
{
    if (p < r)
    {
        /* find the pivot element q such that
        elements smaller than pivot are on left of pivot
        elements greater than pivot are on righ of pivot */
        int q = partition_r(A, p, r);

        // recursive call on the left of pivot
        quickSort(A, p, q - 1);

        // recursive call on the right of pivot
        quickSort(A, q + 1, r);
    }
}

// Driver code
int main()
{
    int M = 1000000; // highest size 
    int n; // size of array
    
    for(n = 10; n <= M; n = n*10)
    {
        cout << "Sorting array of size " << n << endl; // prints size of array
        int B[n];
        int *A = getRandom(B, n);

        // cout << "Unsorted array" << endl; printArray(A,n);

        auto start = high_resolution_clock::now(); // clock starting point
        quickSort(A, 0, n - 1);
        auto stop = high_resolution_clock::now(); // clock stoping point

        auto totalTime_int = duration_cast<nanoseconds>(stop - start); // getting the total time with specified unit as an interger
        duration<double> totalTime_double = stop - start;              // getting the total time as double

        // cout << "Sorted array" << endl; printArray(A,n);

        cout << "Time taken by the Algorithm: " << totalTime_int.count() << " ns" << endl;
        cout << "Time taken by the Algorithm: " << totalTime_double.count() << " s" << endl;
    }
    return 0;
}