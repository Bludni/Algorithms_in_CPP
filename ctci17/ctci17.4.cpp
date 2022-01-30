#include <iostream>

class BitNum {
    private:
        int num;
    public:
        BitNum(int num = 0):num(num){}
        int getBit(int bitpos)
        {
            return (num & (1 << bitpos)) && 1;
        }

        BitNum& operator=(int n) {
            num = n;
            return *this;
        }
};

int reconstrNum(BitNum n)
{
    int temp = 0;
    for (int i = 0; i < 32; i++) 
        temp += (n.getBit(i) << i);
    return temp;
}

int missingNum(BitNum arr[], int size)
{
    int temp = 0;
    for (int i = 0; i < size; i++) 
        temp += reconstrNum(arr[i]);
    return ((size + 1) * size) / 2 - temp; //subtracting sum of all from array
    // ,from all from 0 to n to get the missing element. size is equal to n because 
    //array has a zero inside also.
}

int main()
{
    int n = 50, size = n; // array contains zero too.
    BitNum arr[size];
    int j = 0;
    for (int i = 0; i < n; i++, j++) 
        if (i == 42) arr[i] = ++j;
        else arr[i] = j;
    std::cout << missingNum(arr, size) << std::endl;
}