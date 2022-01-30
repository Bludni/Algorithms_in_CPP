#include <iostream>

//works for distinct elements
int indBinSearch(int beg, int end, int arr[])
{
    if (beg > end)
        return -1;
    int middle = (beg + end) / 2;
    if (arr[middle] > middle) 
        return indBinSearch(beg, middle - 1, arr);
    if (arr[middle] < middle)
        return indBinSearch(middle + 1, end, arr);
    return middle; // found magic index;
}

// if elements arent distinct
int modBinSearch(int beg, int end, int arr[])
{
    if (beg > end)
        return -1;
    int middle = (beg + end) / 2;
    if (arr[middle] == middle) return middle;
    int left = modBinSearch(beg, std::min(middle - 1, arr[middle]), arr);
    // this approach takes into account the value of the middle element and recursively narrows
    // the search area by searhing to the left from min of array value and index. searching through
    // the right applies the same approach but with maximum.
    if (left >= 0) return left;
    int right = modBinSearch(std::max(middle + 1, arr[middle]), end, arr);
    return right; // -1 if no magic index, magic index otherwise
}

int magicInd(int beg, int end, int arr[])
{
    if (arr[beg] == beg) return beg;
    if (arr[end] == end) return end;
    return modBinSearch(beg, end, arr);
}

int main()
{
    int arr[] = {-5, -3, 1, 3, 5, 10, 12};
    int arr1[] = {-10, -5, 2, 2, 2, 3, 4, 7, 9 ,12 ,13};
    std::cout << magicInd(0, 6, arr1) << std::endl;
}