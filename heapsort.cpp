#include <iostream>
#include <chrono>
#include <random>
using namespace std;
using namespace std::chrono;

// Founction to get an array of random numbers
int *getRandom(int A[], int n)
{
    // range of random numbers
    int range_from = 0;
    int range_to = 50000;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);

    for (int i = 0; i < n; ++i)
    {
        A[i] = distr(generator); // creating an array of random numbers
    }
    return A;
}
void heapify(int A[], int n, int i)
{
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;

    if (right < n && A[right] > A[largest])
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i)
    {
        swap(A[i], A[largest]);
        heapify(A, n, largest);
    }
}

// main function to do heap sort
void heapSort(int A[], int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--)
    {
        swap(A[0], A[i]);
        // Heapify root element to get highest element at root again
        heapify(A, i, 0);
    }
}

// Print an array
void printArray(int A[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << A[i] << " ";
    cout << "\n";
}

// Driver code
int main()
{
    int M = 10; // highest size
    int n;           // size of array

    for (n = 10; n <= M; n = n * 10)
    {
        cout << "Sorting array of size " << n << endl; // prints size of array
        int B[n];
        int *A = getRandom(B, n);

        cout << "Unsorted array" << endl;
        printArray(A, n);

        auto start = high_resolution_clock::now(); // clock starting point
        heapSort(A, n);
        auto stop = high_resolution_clock::now(); // clock stoping point

        // getting the total time with specified unit as an interger
        auto totalTime_int = duration_cast<nanoseconds>(stop - start);
        // getting the total time as double
        duration<double> totalTime_double = stop - start;

        cout << "Sorted array" << endl;
        printArray(A, n);

        cout << "Time taken by the Algorithm: " << totalTime_int.count() << " ns" << endl;
        cout << "Time taken by the Algorithm: " << totalTime_double.count() << " s" << endl;
    }
    return 0;
}