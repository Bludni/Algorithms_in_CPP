#include <iostream>
#include <random>

int randInt(int offset, int num)
{
    int divider = RAND_MAX / num;
    int max_num = divider * num;
    int res = rand();
    while (res >= max_num)
        res = rand();
    res /= divider;
    return offset + res;
}

void smallestK(int arr[], int beg, int end, int k)
{   
    if (beg == end) return; //this means we hit k elements left of beg
    int ind = randInt(beg, end - beg + 1);
    std::swap(arr[ind], arr[beg]);
    int left = beg + 1;
    int pivot = arr[beg];
    for (int i = left; i <= end; i++) 
        if (arr[i] < pivot)
            std::swap(arr[i], arr[left++]);
    std::swap(arr[beg],arr[left-1]); //left was pointing one after the last element smaller then k
    if (k > left) smallestK(arr, left, end, k);
    else if (k < left) smallestK(arr, beg, left - 1, k);

}
//the algorithm works as quicksort that goes only through one part of the subarray its called upon
//In optimal case, runtime is the sum (N + N/2 + N/4 + .. + 1) which is O(N) complexity.
//In worst optimal case, it goes to O(N^2) like quicksort

void smallestKWrap(int arr[], int size, int k)
{
    if (k == size) return;
    if (k > size) {
        std::cout << "K cant be bigger than array!\n";
        return;
    }
    smallestK(arr, 0, size - 1, k);
}

int main()
{
    srand(time(0));
    int size = 9;
    int arr[] = {5,1,9,7,3,8,4,6,2};
    smallestKWrap(arr, size, 6);
    for (int i = 0; i < size; i++) 
        std:: cout << arr[i] << " ";
    std:: cout << std::endl;
    // smallest k are first k elements of the array
}