#include <iostream>


void shiftRight(int arr[], int size, int shift)
{
    for (int i = size -1; i >= 0; i--)
        arr[i + shift] = arr[i];
}

void merge(int arr1[], int size1, int arr2[], int size2)
{
    int i = size2, j = 0, k = 0;
    while (i < size1 + size2 || j < size2) {
        if (i >= size1 + size2) {
            arr1[k++] = arr2[j++];
            continue;
        }
        if (j >= size2) {
            arr1[k++] = arr1[i++];
            continue;
        }
        if (arr1[i] < arr2[j]) arr1[k++] = arr1[i++];
        else arr1[k++] = arr2[j++];
    }
}

int main()
{   int size1 = 6, size2 = 4;
    int arr1[10] = {1,4,5,6,8,9}, arr2[4] = {0,2,3,7};
    shiftRight(arr1, size1, size2);
    merge(arr1, size1, arr2, size2);
    for (int i = 0; i < size1 + size2; i++) 
        std::cout << arr1[i] << " ";
    std::cout << std::endl; 
}