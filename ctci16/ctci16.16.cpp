#include <iostream>
#include <limits>

int minRight(int arr[], int size, int pos)
{   
    int min_num = std::numeric_limits<int>::max();
    for (int i = pos; i < size; i++) 
        min_num = (arr[i] < min_num)? arr[i] : min_num;
    return min_num;
}

int maxLeft(int arr[], int size, int pos)
{
    int max_num = std::numeric_limits<int>::min();
    for (int i = pos; i >= 0; i--)
        max_num = (max_num < arr[i])? arr[i] : max_num;
    return max_num;
}

std::pair<int, int> sortRange(int arr[], int size)
{   
    int i = 1; //left end of sort seq
    while (arr[i] >= arr[i-1] && i < size - 1) i++;
    int j = size - 2; // right beg of sort seq
    while (arr[j] <= arr[j+1] && i >= 0) j--;
    int min_right = minRight(arr, size, i);
    int max_left = maxLeft(arr, size, j); 
    i--; j++; //setting i and j on the beggining of their seqs, not just before or after
    while (arr[i] > min_right && i >= 0) i--; //find sorted left part. if not, i goes to -1
    while (arr[j] < max_left && i < size) j++; //find sorted left part. if not, j goes to size
    return std::make_pair(++i, --j);  //putting indices just after(before) elements that broke loops  
}

int main()
{
    int size = 13;
    int arr[] = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
    auto indices = sortRange(arr, size);
    std::cout << "Minimal sorting sequence: (" << 
    indices.first << "," << indices.second << ")\n"; 
}

