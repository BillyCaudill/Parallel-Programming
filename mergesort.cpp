#include <iostream>
#include <cstdlib>   // for std::atoi

#include <iostream>
using namespace std;

// Merge two sorted halves of arr[]
// Left half:  left .. mid
// Right half: mid+1 .. right
void merge(int arr[], int left, int mid, int right) {
    int temp[100];        // temporary array (assume max size)
    int i = left;         // pointer for left half
    int j = mid + 1;      // pointer for right half
    int k = left;         // pointer for temp array

    // Merge both halves into temp[]
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements from left half
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements from right half
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy sorted data back into original array
    for (int x = left; x <= right; x++) {
        arr[x] = temp[x];
    }
}

// Recursive merge sort
void mergeSort(int arr[], int left, int right) {
    // Base case: one element
    if (left >= right)
        return;

    int mid = (left + right) / 2;

    // Sort left half
    mergeSort(arr, left, mid);

    // Sort right half
    mergeSort(arr, mid + 1, right);

    // Merge sorted halves
    merge(arr, left, mid, right);
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = 6;

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}