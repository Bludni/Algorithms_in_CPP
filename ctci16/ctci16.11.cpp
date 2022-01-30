#include <iostream>
#include <set>
#include <vector>

// peasant solution
void allLengths(int shorter, int longer, int k, int leng, std::set<int> &lengs)
{
    if (k == 0) {
        lengs.insert(leng);
        return;
    }
    allLengths(shorter, longer, k - 1, leng + shorter, lengs);
    allLengths(shorter, longer, k - 1, leng + longer, lengs);    
}

// linear time solution
std::vector<int> allLengths(int shorter, int longer, int k)
{
    int len = k * shorter;
    std::vector<int> temp = {len};
    for (int i = 1; i <= k; i++) {
        len += (longer - shorter);
        temp.push_back(len);
    }
    return temp;
}

int main()
{
    int shorter = 2, longer = 4 , k = 4;
    std::set<int> lengs;
    allLengths(shorter, longer, k, 0, lengs);
    for (auto mem : lengs) std::cout << mem << std::endl; 
    //better
    
    std::vector<int> vec = allLengths(shorter, longer, k);
    std::cout << std::endl;
    for (auto mem : lengs) std::cout << mem << std::endl;
}