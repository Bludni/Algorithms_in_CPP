#include <iostream>
#include <random>

//generate rand_set set of numbers from arr
void randSet(int arr[], int size, int rand_set)
{
    if (rand_set == 0) return;
    int divider = RAND_MAX / size;
    int max_num = divider * size;
    int rand_num = rand();
    while (rand_num >= max_num) rand_num = rand();
    rand_num /= divider;
    std::swap(arr[rand_num], arr[size - 1]);
    return randSet(arr, size - 1, rand_set - 1);
}

int main()
{
    srand(time(0));
    int size = 45;
    int arr[size];
    for (int i = 0; i < size; i++) arr[i] = i;
    int m = 10;
    randSet(arr, size, m);
    for (int i = size - m; i < size; i++) std::cout << arr[i] << " ";
    std::cout << std::endl;  
}