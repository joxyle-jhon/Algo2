#include <iostream>
using namespace std;



// Passing Array to Function in C++
// 1. Passing Array as a Pointer

 // passing array as a sized array argument 
void printArrSize(int arr[], int n) {
    cout << "Size of thr arr: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}



// Initialize Array with Values in C++
int main(){
    int arr[5] = {1, 2, 3, 4, 5};
    cout << arr[4] << "\n";

    // Initialize Array with Values and without Size in C++

    int arrs[] = {1, 2, 3, 4, 5};
    cout << arrs[2] << "\n";

    // The C++ Program to Illustrate How to Traverse an Array

    int table[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 8; i++) {
        cout << table[i] << " "; 
    }

    // Next Line
    cout << endl;

    // Size of one element of an array
    cout << "Size of table[0]: " << sizeof(table[0]) << endl;

    // Size of array 'table'
    cout << "Size of table: " << sizeof(table) << endl;

    // Length of array 'table'
    cout << "Length of table: " << sizeof(table) / sizeof(table[0]) << endl;

    // Illustrating the Relationship between Array and Pointers
    int* ptr = arr;
    cout << "Memory address using ptr: " << ptr << endl;
    cout << "Memory address using ptr: " << &arr << endl;

    // calling function printArrSize
    printArrSize(arr, 5);

    
}





