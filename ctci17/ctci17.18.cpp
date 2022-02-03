#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

//arr1 is shorter array with distinct elements. We search for 
//smallest chunk of arr2 that contains arr1
std::pair<int, int> findSeq(int arr1[], int size1, int arr2[], int size2)
{   //idea of the algorithm is to push indexes of elements from arr1 in arr2 in a vector.
    // hash map is tracking indexes of all elements from arr1 in vector.
    //whenever the element that is already in the vector appears, -1 is put on its position
    //and its new index is pushed to the end of the vector. Hashmap is also updated.
    //when there are no elements in hash map equal to -1, we start subtracting first nonnegative value
    //of the vector from the last, whenever we insert a new element. If the value is lesser than min
    // we update the min, and beginning and ending indexes of the sequence. 
    std::unordered_map<int, int> hmap;
    std::vector<int> vec;
    int beg, end;
    for (int i = 0; i < size1; i++) hmap[arr1[i]] = -1;
    int negs = hmap.size();
    int min = std::numeric_limits<int>::max();
    int offset = 0;
    for (int i = 0; i < size2; i++) {
        if (hmap.find(arr2[i]) != hmap.end()) {
            if (hmap[arr2[i]] != -1) 
                vec[hmap[arr2[i]]] = -1;
            else negs--;
            vec.push_back(i);
            hmap[arr2[i]] = vec.size() - 1;
            while (vec[offset] == -1) offset++;
            if (negs == 0 && (vec.back() - vec[offset] + 1 < min)) {
                min = vec.back() - vec[offset] + 1;
                beg = vec[offset];
                end = vec.back(); 
           }
        }
    }
    if (negs > 0) return std::make_pair(-1,-1);
    return std::make_pair(beg,end);
}

int main()
{
    int size1 = 5, size2 = 17;
    int arr1[] = {1,5,9};
    int arr2[] = {7, 5, 9, 13, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7};
    auto res = findSeq(arr1, size1, arr2, size2);
    std:: cout << res.first << "\n" << res.second << std::endl;
}