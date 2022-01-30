#include <iostream>

// how many ways to get n with 1,5,10,25 cents

void shift_left(long arr[], int size, long right)
{
    for (int i = 0; i < size - 1; i++)
        arr[i] = arr[i+1];
    arr[size - 1] = right;
}

long lower(long arr[], int n, int m, int inc)
{
    return (n >= m + inc)? arr[n - m - inc] : 0;
}

long coins(int n)
{
    long arr[25] = {0};
    arr[0] = 1;
    int bord = (n >= 25)? n-25 : -1;
    for (int i = n-1; i > bord ; i--) // first 25  
        arr[n - i] = lower(arr, n, i, 1) + lower(arr, n, i, 5) 
                    + lower(arr, n, i, 10);
    if (n < 25) return arr[n]; 
    for (int i = n - 25; i >= 0; i--) { //rest
        long temp = arr[24] + arr[20] + arr[15] + arr[0];
        shift_left(arr, 25, temp);  
    }
    return arr[24];
}

int main()
{
    std::cout << coins(200) << std::endl;
}