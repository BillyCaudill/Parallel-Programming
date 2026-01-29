#include <iostream>
#include <cstdlib>   // atoi, rand, srand
#include <ctime>     // time
#include <chrono>    // timing
using namespace std;

// Merge two sorted halves of arr[]
void merge(int arr[], int left, int mid, int right) {
    int n = right - left + 1;
    int* temp = new int[n];

    int i = left;        // left half pointer
    int j = mid + 1;     // right half pointer
    int k = 0;           // temp pointer (0..n-1)

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (int x = 0; x < n; x++) {
        arr[left + x] = temp[x];
    }

    delete[] temp;
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./mergesort <array_size>\n";
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        cout << "Error: array_size must be positive\n";
        return 1;
    }

    int* arr = new int[n];
    srand(time(nullptr));

    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }

    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
    cout << "Sorted " << n << " elements in " << elapsed.count() << " seconds\n";

    delete[] arr;
    return 0;
}
