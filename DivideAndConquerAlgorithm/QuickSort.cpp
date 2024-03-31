#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int medianOfThree(vector<int>& arr, int left, int right) {
    int mid = left + (right - left) / 2;
    if (arr[right] < arr[left]) swap(arr[left], arr[right]);
    if (arr[mid] < arr[left]) swap(arr[mid], arr[left]);
    if (arr[right] < arr[mid]) swap(arr[right], arr[mid]);
    return mid;
}

int partition(vector<int>& arr, int left, int right) {
    int pivotIndex = medianOfThree(arr, left, right);
    int pivotValue = arr[pivotIndex];
    swap(arr[pivotIndex], arr[right]); 
    int storeIndex = left;
    for (int i = left; i < right; ++i) {
        if (arr[i] < pivotValue) swap(arr[i], arr[storeIndex++]);
    }
    swap(arr[storeIndex], arr[right]); 
    return storeIndex;
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}

int main() {
    vector<int> arr = {8, 2, 4, 9, 1, 7, 5};
    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
