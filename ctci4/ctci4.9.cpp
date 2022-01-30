#include "bintree.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

using Veci32 = std::vector<int>;

std::vector<Veci32>& combine(int i1, int i2, const Veci32 &v1, 
                             const Veci32 &v2, Veci32 &res_vec, 
                             std::vector<Veci32> &combs)
{
    if (i1 == v1.size() && i2 == v2.size()) {
        combs.push_back(res_vec);
        return combs;
    }
    if (i1 == v1.size()) {
        combs.push_back(res_vec);
        for (int j = i2; j < v2.size(); j++)
            combs.back().push_back(v2[j]);
        return combs;
    }
    if (i2 == v2.size()) {
        combs.push_back(res_vec);
        for (int j = i1; j < v1.size(); j++)
            combs.back().push_back(v1[j]);
        return combs;
    }

    res_vec.push_back(v1[i1]);
    combine(i1 + 1, i2, v1, v2, res_vec, combs);
    res_vec.pop_back();
    res_vec.push_back(v2[i2]);
    combine(i1, i2 + 1, v1, v2, res_vec, combs);
    res_vec.pop_back();
    return combs;
}

std::vector<Veci32> allArrays(bintree::Tree::Node *pok)
{
    std::vector<Veci32> left_arrs, right_arrs, all_arrs;
    if (pok->left != NULL) 
        left_arrs = allArrays(pok->left);
    if (pok->right != NULL)
        right_arrs = allArrays(pok->right);    
    
    if (right_arrs.empty() && left_arrs.empty()) {
        all_arrs.push_back(Veci32(1, pok->get()));
        return all_arrs;
    }
    if (left_arrs.empty()) {
        for (auto vec : right_arrs) {
            Veci32 temp;
            temp.push_back(pok->get());
            for (auto mem : vec)
                temp.push_back(mem);
            all_arrs.push_back(temp);
        }
        return all_arrs;
    }
    if (right_arrs.empty()) {
        for (auto vec : left_arrs) {
            Veci32 temp;
            temp.push_back(pok->get());
            for (auto mem : vec)
                temp.push_back(mem);
            all_arrs.push_back(temp);
        }
        return all_arrs;
    }

    Veci32 res_vec = {pok->get()};
    for (auto mem1 : left_arrs)
        for (auto mem2 : right_arrs) 
            all_arrs = combine(0, 0, mem1, mem2, res_vec, all_arrs);
    return all_arrs;
}

int main()
{
    std::vector<int> vec = {1, 3, 4, 5, 9, 11, 22}; //, 34, 39, 45, 46, 50, 55, 62, 70};
    bintree::Tree tree = bintree::createTree(0, vec.size() - 1, vec);
    std::vector<Veci32> combs;
    combs = allArrays(tree.begin());
    for (auto vec : combs) {
        for (auto mem : vec)
            std::cout << mem << " ";
        std::cout << std::endl;
    }

    std::cout << combs.size() << std::endl;
    struct rusage *usage = new struct rusage; // important to add dynamic memory so it doesnt throw EFAULT
    if (getrusage(RUSAGE_SELF, usage) == -1) {
        int errsv = errno;
        std::cout << errsv << std::endl;
    }
    else {
        std::cout << usage->ru_maxrss << std::endl;
    }
    delete usage;
}