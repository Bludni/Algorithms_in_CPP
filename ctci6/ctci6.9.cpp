#include <iostream>

// brute force
void lockerOpener(bool arr[], int size)
{
    for (int i = 1; i <= size; i++)
        for (int j = i - 1; j < size; j += i) 
            arr[j] = !arr[j];
}

int countOpen(bool arr[], int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
        count += arr[i];
    return count;
}
////////////////////////////////////
/* more optimal */
// uses the fact that only squares are left opened,
// because only squares have odd number of factors
int optOpener(int num)
{
    int i = 1;
    for ( ; i * i <= num; i++);
    return i-1;   
}

int main()
{
    int size = 100;
    bool arr[size] = {false};
    lockerOpener(arr, size);
    std::cout << countOpen(arr, size) << std::endl;
    std::cout << optOpener(size) << std::endl;
}