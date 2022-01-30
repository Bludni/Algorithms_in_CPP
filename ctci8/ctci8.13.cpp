#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

struct Box {
    int w;
    int h;
    int d;
    Box(int w = 0, int h = 0, int d = 0):w(w),h(h),d(d) {}

    friend std::ostream& operator<<(std::ostream &out, const Box &box)
    {
        std::cout << "[" << box.w << ", " << box.h 
                  << ", " << box.d << "]" << std::endl;
        return out;
    }

    bool gt(const Box &box) { // check if it can be below &box
        return w > box.w && h > box.h && d > box.d; 
    }
};

//creates all possible stacks of boxes like subsets
std::deque<std::deque<Box>> allStacks(std::deque<Box> &boxes, 
                                     int ind)
{
    if (ind == boxes.size() - 1) 
        return std::deque<std::deque<Box>>(1, 
               std::deque<Box>(1, boxes.back()));
    std::deque<std::deque<Box>> temp = allStacks(boxes, ind + 1);
    int beg_size = temp.size(); // needed since temp will be expanded with new subsets
    // for goes through all subsets of elements after boxes[ind], and adds new subsets where possible
    for (int i = 0; i < beg_size; i++) 
        if (boxes[ind].gt(temp[i][0])) {
            temp.push_back(temp[i]);
            temp.back().push_front(boxes[ind]); // if greater, add a new subset to the end
        }
    temp.push_back(std::deque<Box>(1, boxes[ind]));
    return temp;
}
//unfortunately, the funcions above and below are very inefficient with memory, so
//alternative will be needed to find only the heights.

//returns highest stack of boxes and its height
std::pair<std::deque<Box>, int> bigStack(std::deque<Box> &boxes)
{
    std::deque<std::deque<Box>> temp = allStacks(boxes, 0);
    int max_ind, max_h = 0; 
    for (int i = 0; i < temp.size(); i++) {
        int h = 0;
        for (auto mem : temp[i])
            h += mem.h;
        if (h > max_h) {
            max_h = h;
            max_ind = i;
        }
    }
    return std::pair<std::deque<Box>, int> (temp[max_ind], max_h);
}
////////////////////////////////////////////////////////////////////////////////////

//alternative solution, hugely improved, and elegant
int createStack(std::deque<Box> &boxes, int ind, int memo[])
{
    if (memo[ind]) { // if its bigger than 0 return it
        return memo[ind];
    }
    int max_height = 0;
    for (int i = ind + 1; i < boxes.size(); i++) {
        int height = createStack(boxes, i, memo); // filling memo for every box(calculating max_height)
        if (boxes[ind].gt(boxes[i])) // if box[ind] can go under currently watched, take new height max 
            max_height = (max_height > height)? max_height : height;
    }
    max_height += boxes[ind].h; // add current box height, possibly is a one box stack
    memo[ind] = max_height;
    return max_height;
}

int findMaxH(std::deque<Box> &boxes)
{
    int memo[boxes.size()] = {0};
    createStack(boxes, 0, memo); // fill memo array
    int max_h = 0;
    for (int i = 0; i < boxes.size(); i++) // max of memo is max height achievable
        max_h = (max_h > memo[i])? max_h : memo[i];
    return max_h;
}

int main()
{
    std::deque<Box> boxes = {Box(1,1,1), Box(2,1,3), Box(2,2,2),
                             Box(3,4,5), Box(3,3,3), Box(4,2,1),
                             Box(5,4,5)};
    std::sort(boxes.begin(), boxes.end(), 
              [](Box b1, Box b2) { return b1.h > b2.h;} );
    
    auto result = bigStack(boxes);
    for (auto box : result.first)
        std::cout << box;
    std::cout << "Max height: " << result.second << std::endl;
   
    // alternative part
        std::cout << "Alternative max height: " << findMaxH(boxes) << std::endl; 
}