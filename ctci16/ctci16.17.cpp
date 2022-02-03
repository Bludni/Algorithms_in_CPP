#include <iostream>

// O(N^2) solution, without small modification, that i somehow managed to miss for a long time
int lContSum(int arr[], int size)
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

// O(N) time solution, beautiful solution, cleaner code, cleaner algorithm
int lContSumFast(int arr[], int size)
{
    //We go through array tracking sum of continious elements. Whenever this sum
    //becomes negative, it means this whole sequence that we passed can only
    //contribute negatively to the sum of the sequences after so we discard it.
    //this way in only one pass we get the maximum sum of continious elements
    int sum = 0, max_sum = 0;
    for (int i = 0; i < size; i++) {
        sum = (sum + arr[i] > 0)? sum + arr[i] : 0;
        max_sum = (sum > max_sum)? sum : max_sum;
    }
    return max_sum;
}

int main()
{
    int size = 6;
    int arr[] ={2, -8, 20, -2, 4, -10};
    std::cout << "Largest continious sum faster way: "
     << lContSumFast(arr, size) << std::endl;
}