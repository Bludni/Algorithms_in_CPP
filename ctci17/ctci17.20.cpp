#include <iostream>
#include <queue>
#include <random>
#include <vector>

//algorithm creates two priority queues, one to have maximum on top, and other minimum.
//the queues are kept with maximum of 1 in size difference. so on top one of them is the median
//all the time, if the number of elements is odd. 
std::pair<int,int> trackMedian(int n)
{
    if (n <= 0) return std::make_pair(-1,-1);
    if (n == 1) return std::make_pair(rand(), -1);
    if (n == 2) return std::make_pair(rand(), rand());
    auto less = [](int l, int r){return l < r;};
    auto great = [](int l, int r){return l > r;};
    std::priority_queue<int, std::vector<int>, decltype(less)> lpq(less);
    std::priority_queue<int, std::vector<int>, decltype(great)> gpq(great);
    int temp1 = rand(), temp2 = rand(); n -= 2;
    if (temp1 > temp2) std::swap(temp1,temp2);
    lpq.push(temp1); gpq.push(temp2);
    while (--n >= 0) {
        int val = rand();
        if (val >= gpq.top()) gpq.push(val);
        else if (val < lpq.top()) lpq.push(val);
        else {
            if (gpq.size() > lpq.size()) lpq.push(val);
            else gpq.push(val);
            continue;
        }
        if (gpq.size() - 1 > lpq.size()) {
            lpq.push(gpq.top()); 
            gpq.pop();
        }
        else if (lpq.size() - 1 > gpq.size()) {
            gpq.push(lpq.top());
            lpq.pop();
        }
    }
    if (gpq.size() == lpq.size()) return std::make_pair(lpq.top(),gpq.top());
    else if (gpq.size() > lpq.size()) return std::make_pair(gpq.top(), -1);
    else return std::make_pair(lpq.top(), - 1);
}

int main()
{
    srand(time(0));
    auto res = trackMedian(21);
    if (res.second == -1) std::cout << res.first << std::endl;
    else std::cout << res.first << " " << res.second << std::endl;
}