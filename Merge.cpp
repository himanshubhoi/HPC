#include <iostream>
#include <vector>
#include <omp.h>

void merge(std::vector<int>& arr, int low, int mid, int high) {
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    std::vector<int> leftArr(leftSize);
    std::vector<int> rightArr(rightSize);

    for (int i = 0; i < leftSize; ++i)
        leftArr[i] = arr[low + i];

    for (int i = 0; i < rightSize; ++i)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = low;

    while (i < leftSize && j < rightSize) {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    while (i < leftSize)
        arr[k++] = leftArr[i++];

    while (j < rightSize)
        arr[k++] = rightArr[j++];
}

void mergeSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        {
            mergeSort(arr, low, mid);
            mergeSort(arr, mid + 1, high);
        }

        merge(arr, low, mid, high);
    }
}

int main() {
    std::vector<int> arr = {9, 7, 5, 3, 1, 8, 6, 4, 2, 0};

    std::cout << "Original Array: ";
    for (int num : arr)
        std::cout << num << " ";

    std::cout << std::endl;

    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted Array: ";
    for (int num : arr)
        std::cout << num << " ";

    std::cout << std::endl;

    return 0;
}