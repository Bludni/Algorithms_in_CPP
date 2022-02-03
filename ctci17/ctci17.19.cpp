#include <iostream>
#include <math.h>

//one integer missing from 1 to N. we subtract sum of array from sum of 1 to N.
long missingOne(long arr[], long size)
{
    long sum = 0;
    for (long i = 0; i < size; i++)
        sum += arr[i];
    return ((size + 1) * (size + 2)) / 2 - sum;
}

//system of equations of sum of a+b and a^2+b^2
std::pair<long,long> missingTwo(long arr[], long size)
{
    long sum = 0, sumsq = 0;
    for (long i = 0; i < size; i++) {
        sum += arr[i];
        sumsq += arr[i] * arr[i];
    }
    int c1 = ((size + 2) * (size + 3)) / 2 - sum;
    int c2 = ((size+2) * (size+3) * (2*size+5)) / 6 - sumsq;
    return std::make_pair((c1 + sqrt(2*c2 - c1*c1)) / 2, //solutions to quadratic equation
                          (c1 - sqrt(2*c2 - c1*c1)) / 2);
}

int main()
{
    int size1 = 8, size2 = 7;
    long arr1[] = {1,2,3,4,5,6,7,9};
    long arr2[] = {1,2,3,4,6,7,8};
    std::cout << missingOne(arr1, size1) << std::endl;
    auto pair = missingTwo(arr2, size2);
    std::cout << "(" << pair.first << "," << pair.second << ")\n"; 
}