#include <iostream>
#include <vector>

using Subset = std::vector<std::vector<int>>;

void subsets(std::vector<int> &vec, std::vector<int> &tracker,
               Subset &result, int len, int ind)
{
    if (len == 0) {
        result.push_back(tracker);
        return;
    }
    tracker.push_back(vec[ind]);
    subsets(vec, tracker, result, len - 1, ind + 1);
    tracker.pop_back();
    if (len + ind < vec.size())
        subsets(vec, tracker, result, len, ind + 1);
}

void merge(Subset &set1, Subset &set2)
{
    for (auto row : set2)
        set1.push_back(row);
}

void allSubsets(std::vector<int> &vec, Subset &result)
{
    std::vector<int> tracker;
    for (int i = 1; i <= vec.size(); i++) {
        Subset temp;
        subsets(vec, tracker, temp, i, 0);
        merge(result, temp);
    }
}

int main()
{
    std::vector<int> vec = {1,2,3,4,5};
    Subset result;
    allSubsets(vec, result);
    std::cout << "{}" << std::endl; 
    for (auto row : result) {
        std::cout << "{";
        for (auto mem : row)
           if (mem != row.back()) std::cout << mem << ", ";
           else std::cout << mem << "}";
        std::cout << std::endl;
    }
}