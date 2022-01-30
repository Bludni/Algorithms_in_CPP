#include <iostream>

//rotated array search. returns index in array of found target, or -1
int search(int arr[], int size, int target)
{
    int beg = 0, end = size - 1;
    if (size == 1 && arr[0] == target) return 0; 
    int middle;
    //find point of rotation with binary search
    while (beg <= end) {
        middle = (beg + end) / 2;
        if (arr[middle] < arr[0]) end = middle - 1; // go left if smaller then arr[0]
        else beg = middle + 1; //else go right 
    }
    end = size - 1; // returning end to original place
    beg = 0; // beg too
    if (target >= arr[beg])  // setting border for searching sorted part
        end = (arr[middle] > arr[beg])? middle : middle - 1;
    else  
        beg = (arr[middle] < arr[beg])? middle : middle + 1; 

    // finish with second binary search for element
    while (beg <= end) {
        middle = (beg + end) / 2;
        if (arr[middle] > target) 
            end = middle - 1;
        else if (arr[middle] < target)
            beg = middle + 1;
        else return middle;
    }
    return -1; //found nothing
}

int main()
{
    int size = 12;
    int arr[] = {15,16,19,20,25,31,44,1,3,4,5,7,10,14};
    std::cout << search(arr, size, 5) << std::endl;
}