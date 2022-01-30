#include <iostream>

void peakValSort(int arr[], int size)
{
    if (size <= 2) return;
    auto peak = (arr[1] > arr[0]); //if not, first element is a valley
    for (int i = 1; i < size - 1; i++, peak = !peak)    
        if (peak && (arr[i] < arr[i+1]) ||
            !peak && (arr[i] > arr[i+1])) 
                std::swap(arr[i], arr[i+1]);
}

int main()
{
    int size = 9;
    int arr[] = {1,3,5,6,2,1,8,7,9};
    peakValSort(arr, size);
    for (int i = 0; i < size; i++) 
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}