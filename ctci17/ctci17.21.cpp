#include <iostream>

struct Frame {
    int value, index;
    Frame(int v = 0, int i = 0): value(v), index(i) {}
};


Frame findMaxLeft(int arr[], int cmp_val, int beg, int end)
{    //function searches for the first bigger of the cpm_val to the right,
    // or max of right sequence if there is no bigger
    int max = 0, index = 0;
    for(int i = beg; i <= end; i++) 
        if (arr[i] > max) {
            max = arr[i];
            index = i;
            if (max > cmp_val)
                return {max, index};
        }
    return {max, index};
}

Frame findMaxRight(int arr[], int cmp_val, int beg, int end)
{
    //function searches for the first bigger of the cpm_val to the left,
    // or max of left sequence if there is no bigger
    int max = 0, index = 0;
    for(int i = end; i >= beg; i--) 
        if (arr[i] > max) {
            max = arr[i];
            index = i;
            if (max > cmp_val) // 
                return {max, index};
        }
    return {max, index};
}


int countWatAr(int arr[], int beg, int end)
{
    int area = 0;
    int val = (arr[beg] < arr[end])? arr[beg] : arr[end];
    for (int i = beg + 1; i < end; i++)
        area += (val - arr[i] > 0)? val - arr[i] : 0;
    return area;
}

//amount of water histrogram can hold
//O(N^2) solution, in worst case.
int histogramArea(int arr[], int size)
{
    int beg = 0, end = size - 1;
    Frame left_end, right_beg;
    int i = beg, j = end;
    int water_area = 0;
    while (beg < end) {
        while (arr[i] <= arr[i+1] && i < end) i++;
        if (i == end) return water_area;
        beg = i;

        while (arr[j] <= arr[j-1] && j > beg ) j--;
        if (j == beg) return water_area;
        end = j;

        while (arr[i] >= arr[i+1] && i < end) i++;
        if (i == end) return water_area;
        left_end = findMaxLeft(arr, arr[beg], i, end);
        water_area += countWatAr(arr, beg, left_end.index);
        beg = left_end.index;

        while (arr[j] >= arr[j-1] && j > beg) j--;
        if (j == beg) return water_area;
        right_beg = findMaxRight(arr, arr[end], beg, j);
        water_area += countWatAr(arr, right_beg.index, end);
        end = right_beg.index;
    } 
    return water_area;
}


//O(N) time O(N) memory alternative
int histogramAreaAlt(int arr[], int size)
{
    int maxes[size] = {0};
    int size_left = 0, size_right = size - 1;
   
    int run_max = 0;
    for (int i = 0; i < size; i++) // mapping left first maximums, rightmost is array maximum
        if (arr[i] > run_max) {
            while (arr[i] < arr[i+1] && i < size) i++;
            if (i == size) i--;
            run_max = arr[i];
            maxes[size_left++] = i;
        }
    
    run_max = 0;
    for (int j = size - 1; j >= maxes[size_left - 1]; j--) 
        if (arr[j] > run_max) { //mapping maximum from the right. leftmost is maximum of the array
            while(arr[j] < arr[j-1] && j > maxes[size_left - 1]) j--;
            run_max = arr[j];
            maxes[size_right--] = j;
        }
    
    int water_area = 0;
    if (size_left > 1)
        for (int i = 0; i < size_left - 1; i++) //count water area left of maximum
            water_area += countWatAr(arr, maxes[i], maxes[i+1]);
    if ((size - 1) - size_right > 1)
        for (int j = size_right + 1; j < size - 1; j++) //count water are right of maximum
            water_area += countWatAr(arr, maxes[j], maxes[j+1]);
    return water_area;
}


//Program counts the amount of water that could be between 
//columns of array. each column has width 1
int main()
{
    int size = 16;
    int arr[] = {0, 0, 4, 0, 0, 6, 0, 0, 3, 0, 5, 0, 1, 0, 0, 0};
    std::cout << histogramArea(arr, size) << std::endl;
    std::cout << histogramAreaAlt(arr, size) << std::endl;
}