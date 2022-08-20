#include <iostream>
#include <math.h>
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
// Merge two subarrays L and R into arr
void merge(int A[], int p, int q, int r)
{

  // Create L ← A[p..q] and R ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], R[n2];

  for (int i = 0; i < n1; i++)
    L[i] = A[p + i];
  for (int j = 0; j < n2; j++)
    R[j] = A[q + 1 + j];

  // Maintain current index of sub-arrays and main array
  int i = 0;
  int j = 0;
  int k = p;

  // Until we reach either end of either L or R, pick larger among
  // elements L and R and place them in the correct position at A[p..r]
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      A[k] = L[i];
      i++;
    }
    else
    {
      A[k] = R[j];
      j++;
    }
    k++;
  }
  // When we run out of elements in either L or R,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1)
  {
    A[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    A[k] = R[j];
    j++;
    k++;
  }
}

// Divide the Array into two subarrays, sort them and merge them
void mergeSort(int A[], int left, int right)
{
  if (left < right)
  {
    // mid is the point where the Aray is divided into two subarrays
    int mid = floor(left + right) / 2;
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    // Merge the sorted subarrays
    merge(A, left, mid, right);
  }
}

// Print the array
void printArray(int A[], int size)
{
  for (int i = 0; i < size; i++)
    cout << A[i] << " ";
  cout << endl;
}
// Driver program
int main()
{
  int M = 1000000; // highest size
  int n;           // size of array

  for (n = 10; n <= M; n = n * 10)
  {
    cout << "Sorting array of size " << n << endl; // prints size of array
    int B[n];
    int *A = getRandom(B, n);

    int left = 0;
    int right = n - 1;

    // cout << "Unsorted array" << endl; printArray(A,n); // for test

    auto start = high_resolution_clock::now(); // clock starting point
    mergeSort(A, left, right);
    auto stop = high_resolution_clock::now(); // clock stoping point

    auto totalTime_int = duration_cast<nanoseconds>(stop - start); // getting the total time with specified unit as an interger
    duration<double> totalTime_double = stop - start;              // getting the total time as double

    // cout << "Sorted array" << endl; printArray(A,n); // for test

    cout << "Time taken by the Algorithm: " << totalTime_int.count() << " ns" << endl;
    cout << "Time taken by the Algorithm: " << totalTime_double.count() << " s" << endl;
  }
  return 0;
}