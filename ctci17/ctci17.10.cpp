#include <iostream>

//find if there is and which elements takes more than half of the array
int findMaj(int arr[], int size)
{
    int maj = 0, bit_msk, numOf1;
    for (int bit = 0; bit < 32; bit++) {
        bit_msk = 1 << bit;
        numOf1 = 0;
        for (int i = 0; i < size; i++)
            if (arr[i] & bit_msk) 
                numOf1++;
        maj = (size / 2 < numOf1)? maj + bit_msk : maj;
    }
    int num_maj = 0;
    for (int i = 0; i < size; i++) 
        num_maj = (arr[i] == maj)? num_maj+1 : num_maj;  
    return (num_maj > size / 2)? maj : -1; //-1 is for no majority element
}
//this is O(n * log n) solution, which is not good enough

// this solution leverages the fact that there has to be a subarray that starts with the 
// majority element of the whole array, if it exists. This subarray will go till the end of the array.
// This means that if we start from the left, we will encounter this subarray at some point, even if
// it is of length 1!  we break the majority search as soon as its not bigger than the half of the
// subarray we check, and check next element after subarray as majority. This works because, even
// if the element we checked was the actual majority of the whole array, we are substracting the same
// amount of elements equal to the current majority checked and different from it. So, if the element is
// truly a majority, it will be stay the majority of the rest of the array also.
int findMajBet(int arr[], int size)
{
    int count = 0, maj;
    for (int i = 0; i < size; i++)
        if (count = 0) maj = arr[i]; 
        else if (arr[i] == maj) count++;
        else count--;
    count = 0;
    for (int i = 0; i < size; i++) 
        if (maj = arr[i]) count++;
    return (count > size / 2)? maj : -1; 
}

int main()
{
    int size = 9;
    int arr[size] = {1, 2, 5, 9, 5, 9, 5, 5, 5};
    std::cout << findMaj(arr, size) << std::endl;
    std::cout << findMajBet(arr, size) << std::endl; 
}