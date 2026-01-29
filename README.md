Merge Sort
Sequential implementation of the merge sort algorithm in C++.
Compilation
g++ -o mergesort mergesort.cpp or make from MakeFile
Usage
./mergesort <array_size>
Example:
./mergesort 10000
Output
The program outputs the array size and execution time in seconds:
Sorted 10000 elements in 0.0025411 seconds
Algorithm
Merge sort is a divide-and-conquer sorting algorithm with O(n log n) time complexity. 

The implementation:

Generates a random array of the specified size
Sorts the array using merge sort
Measures and reports the sorting time
