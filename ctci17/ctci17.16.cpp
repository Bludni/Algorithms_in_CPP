#include <iostream>

int maxSched(int arr[], int size, int index, int memo[])
{
    if (index >= size) return 0;
    if (memo[index]) return memo[index];
    int even,odd;
    even = maxSched(arr, size, index + 1, memo);
    odd = arr[index] + maxSched(arr, size, index + 2, memo);
    memo[index] = (even > odd)? even : odd;
    return memo[index];
}

//masseuse schedule
int main()
{
    int size = 8;
    int arr[] = {30, 15, 60, 75, 45, 15, 15, 45};
    int memo[size] = {0};
    std::cout << maxSched(arr, size, 0, memo) << std::endl;
}