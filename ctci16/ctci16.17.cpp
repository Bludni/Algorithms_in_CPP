#include <iostream>

int lConstSum(int arr[], int size)
{
    int sum = arr[0];
    int max_sum = arr[0];
    for (int i = 1; i < size; i++){ //turn array into continious sum of first i on position i
        sum += arr[i];
        arr[i] = sum;
        max_sum = (sum > max_sum)? sum : max_sum; // check big contigious sequences first
    }

    for (int i = 1; i < size; i++) //go through array and check sums as differences
        for (int j = 0; j < i; j++) 
            max_sum = (max_sum > arr[i] - arr[j])? max_sum : arr[i] - arr[j];
    return max_sum;
}

int main()
{
    int size = 6;
    int arr[] ={2, -8, 20, -2, 4, -10};
    std::cout << "Largest continious sum: "
     << lConstSum(arr, size) << std::endl;
}