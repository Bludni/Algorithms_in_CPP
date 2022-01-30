#include "bintree.h"

/* beautiful function, left for sheer beaty, although it didnt prove useful here.
ind is always 1 on start, dif_ind is the index which divides array.
sum starts with rightmost element.
dif_mode sets a mode for calculating only all continious sums from begining
till dif_ind. if it is false, then function calculates all continious sums from begining
that include all elements from dif_ind till end of vec.*/
/*
int eqSums(const std::vector<int> &vec, 
           const int &target_sum, int sum,
           int ind, int dif_ind,
           const bool &dif_mode)
{
    int vec_size, upper_bord = dif_ind;
    if (dif_mode) {
        vec_size = dif_ind;
        upper_bord = -1;
        if (ind == 1) sum = vec[vec_size - 1];
    }
    else vec_size = vec.size();

    if (ind >= vec_size) return 0;
    int count = 0;
    int new_sum = sum + vec[vec_size - 1 - ind]; // for next recursion cycle; 
    if (sum == target_sum)
        count++;
    for (int i = vec_size - 1 - ind; (i + ind) > upper_bord && i >= 0; i--) {
        sum += (vec[i] - vec[i + ind]);
        if (sum == target_sum)
            count++;
    }
   return count += eqSums(vec, target_sum, new_sum, ind +1, dif_ind, dif_mode);
} */


//less optimal solution
int countSums(bintree::Tree::Node *pok, const int &target_sum,
              int sum, bool cond)
{
    if (pok == NULL) return 0;
    int count = 0;
    sum += pok->get();
    if (sum == target_sum) 
        count++;
    count += countSums(pok->left, target_sum, sum, cond) 
           + countSums(pok->right, target_sum, sum, cond);
    if (cond) 
        count += countSums(pok->left, target_sum, 0, false) 
               + countSums(pok->right, target_sum, 0, false);
    return count;
}

//more optimal solution
//run_sums starts with 0 inside
int countAlongSums(bintree::Tree::Node *pok, const int &target_sum,
                   std::vector<int> &run_sums)
{
    if (pok == NULL) return 0;
    int count = 0;
    run_sums.push_back(run_sums.back() + pok->get());
    for (int i = 0; i < run_sums.size() - 1; i++) 
        if (run_sums.back() - run_sums[i] == target_sum)
            count++;
    count += countAlongSums(pok->left, target_sum, run_sums)
           + countAlongSums(pok->right, target_sum, run_sums);
    run_sums.pop_back();
    return count;
}
    

int main()
{
    std::vector<int> vec = {1, 1, 1, 1, 2, 3, 1, 2, 1};
    bintree::Tree tree = bintree::createTree(0, vec.size() - 1, vec);
    std::cout << countSums(tree.begin(), 3, 0, true) << std::endl;
    std::vector<int> run_sums{0};
    std::cout << countAlongSums(tree.begin(), 3, run_sums) << std::endl;
}