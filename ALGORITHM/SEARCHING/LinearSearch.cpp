#include <iostream>
using namespace std;


int linearSearch(int arr[], int n, int x){
    for (int i = 0; i < n; i++)
        if(arr[i] == x)
            return i;
    return -1;
}


int main(){

    int arr[] = {12, 31, 32, 50, 65};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 50;

    int result = linearSearch(arr, n, x);
    (result == -1)
        ? cout << "Element is not present in the array!" << endl
        : cout << "Element is present at index " << result;
        return 0;

}