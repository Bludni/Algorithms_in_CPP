#include <iostream>
#include <vector>


int min3(int a, int b, int c) 
{    
    return std::min(std::min(a,b), c);
}

int kthFact357(int k)
{
    std::vector<int> magnum357 = {1,3,5,7}; //1 is a dummy here to match k with index
    if (k <= 0) return magnum357[0]; //we use dummy as error code
    if (k <= 3) return magnum357[k];
    int ind3 = 1, ind5 = 2, ind7 = 3;
    int val3, val5, val7;
    for (int i = 1; i <= k-3; i++) {
        val3 = 3 * magnum357[ind3];
        val5 = 5 * magnum357[ind5];
        val7 = 7 * magnum357[ind7];
        int min_el = min3(val3,val5,val7);
        if (val3 == min_el) {
            magnum357.push_back(val3); 
            ind3++;
        }
        if (val5 == min_el) {
            magnum357.push_back(val5); 
            ind5++;
        }
        if (val7 == min_el) {
            magnum357.push_back(val7); 
            ind7++;
        }
    }
    return magnum357.back();
}

int main()
{
    std::cout << kthFact357(1000000) << std::endl;
}