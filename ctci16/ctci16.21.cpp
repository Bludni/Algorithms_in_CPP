#include <iostream>
#include <unordered_set>

int compare(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

// with sorting, hmap could be faster
std::pair<int, int> sumSwap(int arr1[], int size1, int arr2[], int size2)
{
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < size1; i++) sum1 += arr1[i];
    for(int i = 0; i < size2; i++) sum2 += arr2[i];
    int dif = sum1 - sum2;
    if (dif & 1) return std::make_pair(-1,-1); //if odd, cant be swapped
    dif /= 2;
    qsort(arr1, size1, sizeof(int), compare);
    qsort(arr2, size2, sizeof(int), compare);
    int i = 0, j = 0; 
    while (i < size1 && j < size2) 
        if (arr1[i] - arr2[j] < dif) i++;
        else if (arr1[i] - arr2[j] > dif) j++;
        else return std::make_pair(arr1[i],arr2[j]);
    return std::make_pair(-1,-1);
}

//faster solution with hset
std::pair<int, int> sumSwapAlt(int arr1[], int size1, int arr2[], int size2)
{
    int sum1 = 0, sum2 = 0;
    std::unordered_set<int> uset;
    for(int i = 0; i < size1; i++) sum1 += arr1[i];
    for(int i = 0; i < size2; i++) {
        sum2 += arr2[i];
        uset.insert(arr2[i]);
    }
    int dif = sum1 - sum2;
    if (dif & 1) return std::make_pair(-1,-1); //if odd, cant be swapped
    dif /= 2;
    for (int i = 0; i < size1; i++) 
        if (uset.find(arr1[i] - dif) != uset.end())
            return std::make_pair(arr1[i], arr1[i] - dif);
    return std::make_pair(-1,-1);
}

//swaps a number from first and from second so that the two sum to the same value
int main()
{
    int size1 = 6, size2 = 5;
    int arr1[]{4,1,2,1,1,2}, arr2[]{3, 6, 3, 3, 4};
    auto exc = sumSwap(arr1,size1,arr2,size2);
    std::cout << "(" << exc.first << "," << exc.second << ")\n";  
    exc = sumSwapAlt(arr1,size1,arr2,size2);
    std::cout << "(" << exc.first << "," << exc.second << ")\n";  
}