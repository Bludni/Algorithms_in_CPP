#include <iostream>

void print(char arr[], int size)
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

void perms(char arr[], int size, int ind)
{
    if (ind == size) print(arr, size);
    for (int i = ind; i < size; i++) {
        std::swap(arr[ind], arr[i]);
        perms(arr, size, ind + 1);
        std::swap(arr[ind], arr[i]);
    }
}

int main()
{
    char arr[] = {'a','b','c','d'}, size = 4;
    perms(arr, size, 0);
}