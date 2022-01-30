#include <iostream>
#include <set>

void print(char arr[], int size)
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

void permsWithDups(char arr[], int size, int ind)
{
    if (ind == size) print(arr, size);
    std::set<char> unique;
    for (int i = ind; i < size; i++) {
        std::swap(arr[ind], arr[i]);
        if (unique.find(arr[ind]) == unique.end())
            permsWithDups(arr, size, ind + 1);
        unique.insert(arr[ind]);
        std::swap(arr[ind], arr[i]);
    }
}

int main()
{
    char arr[] = {'a','b','b','c','c'}, size = 5;
    permsWithDups(arr, size, 0);
}