#include <iostream>

//count all 2s till a number n

// tail recursion solution
int all2s(int n, int num2 = 0, int num2per_dec = 0, int mul = 1, int res = 0)
{
    if (n == 0) return res;
    int last_dig = n % 10;
    if (last_dig == 2) res += num2 + 1; // all of the decimals below count with 2
    res += last_dig * num2per_dec + (last_dig > 2) * mul;
    num2per_dec = 10 * num2per_dec + mul; 
    num2 += last_dig * mul ;
    mul *= 10;
    return all2s(n / 10, num2, num2per_dec, mul, res);
}

int all2sIter(int n)
{
    int num2 = 0, num2per_dec = 0, mul = 1, count = 0;
    while (n > 0) {
        int last_dig = n % 10;
        if (last_dig == 2) count += num2 + 1; // one is because the zero enters count
        count += last_dig * num2per_dec + (last_dig > 2) * mul;
        num2per_dec = 10 * num2per_dec + mul; 
        num2 += last_dig * mul;
        mul *= 10;
        n /= 10;
    }
    return count;
}

int main()
{
    std::cout << all2s(2022) << std::endl;
    std::cout << all2sIter(2010) << std::endl;
}