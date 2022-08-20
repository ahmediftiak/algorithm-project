#include <iostream>
#include <random>
#include <chrono>
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

// Function to get the largest element from an array
int getMax(int A[], int n)
{
  int max = A[0];
  for (int i = 1; i < n; i++)
    if (A[i] > max)
      max = A[i];
  return max;
}

// Using counting sort to sort the elements in the basis of significant places
void countingSort(int A[], int size, int place)
{
  const int max = 10;
  int output[size];
  int count[max];

  for (int i = 0; i < max; ++i)
    count[i] = 0;

  // Calculate count of elements
  for (int i = 0; i < size; i++)
    count[(A[i] / place) % 10]++;

  // Calculate cumulative count
  for (int i = 1; i < max; i++)
    count[i] += count[i - 1];

  // Place the elements in sorted order
  for (int i = size - 1; i >= 0; i--)
  {
    output[count[(A[i] / place) % 10] - 1] = A[i];
    count[(A[i] / place) % 10]--;
  }

  for (int i = 0; i < size; i++)
    A[i] = output[i];
}

// Main function to implement radix sort
void radixsort(int A[], int size)
{
  // Get maximum element
  int max = getMax(A, size);

  // Apply counting sort to sort elements based on place value.
  for (int place = 1; max / place > 0; place *= 10)
    countingSort(A, size, place);
}

// Print an array
void printArray(int A[], int size)
{
  int i;
  for (i = 0; i < size; i++)
    cout << A[i] << " ";
  cout << endl;
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

    cout << "Unsorted array quick sort" << endl; printArray(A,n);

    auto start = high_resolution_clock::now(); // clock starting point
    radixsort(A, n);
    auto stop = high_resolution_clock::now(); // clock stoping point

    auto totalTime_int = duration_cast<nanoseconds>(stop - start); // getting the total time with specified unit as an interger
    duration<double> totalTime_double = stop - start;              // getting the total time as double

    cout << "Sorted array" << endl; printArray(A,n);

    cout << "Time taken by the Algorithm: " << totalTime_int.count() << " ns" << endl;
    cout << "Time taken by the Algorithm: " << totalTime_double.count() << " s" << endl;
  }
  return 0;
}