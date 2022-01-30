#include <iostream>
#include <vector>

bool inBounds(int row, int col, int maxrow, int maxcol)
{
    return row >= 0 && row < maxrow && col >= 0 && col < maxcol;
}

std::pair<int, int> matSearch(std::vector<std::vector<int>> &vec, int target,
             int rowtl, int coltl, int rowbr, int colbr)
{
    std::pair<int, int> not_found(-1,-1);
    if (!inBounds(rowtl, coltl, vec.size(), vec[0].size()) || 
        !inBounds(rowbr, colbr, vec.size(), vec[0].size())) // base case when fails
            return not_found;

    int row_middle, col_middle;
    if (rowtl == rowbr) { //binary search one row
        while (coltl <= colbr) { 
            col_middle = (coltl + colbr) / 2;
            if (vec[rowtl][col_middle] > target) 
                colbr = col_middle - 1;
            else if (vec[rowtl][col_middle] < target)
                coltl = col_middle + 1;
            else return std::pair<int,int>(rowtl, col_middle); 
        }
        return not_found;
    }
   
    if (coltl == colbr) { //binary search one col
        while (rowtl <= rowbr) {
            row_middle = (rowtl + rowbr) / 2;
            if (vec[row_middle][coltl] > target) 
                rowbr = row_middle - 1;
            else if (vec[row_middle][coltl] < target)
                rowtl = row_middle + 1;
            else return std::pair<int,int>(row_middle, coltl); 
        }
        return not_found;
    }

    row_middle = (rowtl + rowbr) / 2 ; //prep for 2d search
    col_middle = (coltl + colbr) / 2; 

    if (vec[row_middle][col_middle] > target) { //this means its not in bot right quarter approx
        std::pair<int, int> t1, t2, t3;
        t1 = matSearch(vec, target, rowtl, coltl, //top left rectangle search
                       row_middle - 1, col_middle - 1);
        if (t1.first > -1) return t1;
        t2 = matSearch(vec, target, rowtl, col_middle, //top right rect 
                       row_middle - 1, colbr);
        if (t2.first > -1) return t2;
        t3 = matSearch(vec, target, row_middle, coltl, //bot left rect 
                       rowbr, col_middle - 1);
        if (t3.first > -1) return t3;
        return not_found;
    }
    else if (vec[row_middle][col_middle] < target) { //this means its not in top left quarter approx
        std::pair<int, int> t1, t2, t3;
        t1 = matSearch(vec, target, rowtl, col_middle + 1, //top right rectangle search
                       row_middle, colbr);
        if (t1.first > -1) return t1;
        t2 = matSearch(vec, target, row_middle + 1, coltl, //bot left rect 
                       rowbr, col_middle);
        if (t2.first > -1) return t2;
        t3 = matSearch(vec, target, row_middle + 1, col_middle + 1, //bot right rect 
                       rowbr, colbr);
        if (t3.first > -1) return t3;
        return not_found;
    }
    else return std::pair<int,int>(row_middle, col_middle);
}


//an alternative, that upgrades on the before algorithm is to search on main diagonal
// until we find a spot where wanted element is between two elements of the diagonal.
// this way, we only have to search for in top right and bot left recs which makes it more
//efficient than searching 3 quadrants. Next function incorporates this. Wise to mention is
// that this function loses its efficiency for very large differences in dimensions 
// and even for large square matrices where we find that element is in a submatrix with
//very large difference in dimensions. For these cases, the previous function works better
// since it cuts dimensions much more effectively and then uses binary search on singular arrays
std::pair<int, int> matModSearch(std::vector<std::vector<int>> &vec, int target,
             int rowtl, int coltl, int rowbr, int colbr)
{
    std::pair<int, int> not_found(-1,-1);
    if (!inBounds(rowtl, coltl, vec.size(), vec[0].size()) || 
        !inBounds(rowbr, colbr, vec.size(), vec[0].size())) // base case when fails
            return not_found;
    
    int row_middle, col_middle;
    if (rowtl == rowbr) { //binary search one row
        while (coltl <= colbr) { 
            col_middle = (coltl + colbr) / 2;
            if (vec[rowtl][col_middle] > target) 
                colbr = col_middle - 1;
            else if (vec[rowtl][col_middle] < target)
                coltl = col_middle + 1;
            else return std::pair<int,int>(rowtl, col_middle); 
        }
        return not_found;
    }
   
    if (coltl == colbr) { //binary search one col
        while (rowtl <= rowbr) {
            row_middle = (rowtl + rowbr) / 2;
            if (vec[row_middle][coltl] > target) 
                rowbr = row_middle - 1;
            else if (vec[row_middle][coltl] < target)
                rowtl = row_middle + 1;
            else return std::pair<int,int>(row_middle, coltl); 
        }
        return not_found;
    }
          //searching a biggest square matrix
    int diag = std::min(rowbr - rowtl, colbr - coltl); // diagonal of biggest square
    int row_start = rowtl, col_start = coltl;
    int row_end = row_start + diag, col_end = col_start + diag;
    while (row_start <= row_end && col_start <= col_end) {
        row_middle = (row_start + row_end) /2;
        col_middle = (col_start + col_end) /2;
        if (target > vec[row_middle][col_middle]) {
            row_start = row_middle + 1;
            col_start = col_middle + 1;
        }
        else if (target < vec[row_middle][col_middle]) {
            row_end = row_middle - 1;
            col_end = col_middle - 1;
        }
        else return std::pair<int, int>(row_middle, col_middle);
    } //the start field ends on the first element of diagonal thats bigger then target
    //if not found on diagonal, do top right and bot left quadrants
    auto t1 = matModSearch(vec, target, rowtl, col_start, row_start - 1, colbr); // top right
    if (t1.first != -1) return t1;
    return matModSearch(vec, target, row_start, coltl, rowbr, col_start - 1); //bot left or nothing
}

int main()
{
    std::vector<std::vector<int>> vec1 = {{1,5,9,13},{2,6,10,14}}, 
                                  vec2 = {{1,5,9,13},{2,6,10,14},{3,7,11,15}},
                                  vec3 = {{1,5,9,13},{2,6,10,14},{3,7,11,15},{4,8,12,16}};
    auto res = matSearch(vec1, 10, 0, 0, 1, 3);
    std::cout << "row: " << res.first << ", col: " << res.second << std::endl;
    res = matSearch(vec2, 13, 0, 0, 2, 3);
    std::cout << "row: " << res.first << ", col: " << res.second << std::endl;
    res = matSearch(vec3, 11, 0, 0, 3, 3);
    std::cout << "row: " << res.first << ", col: " << res.second << std::endl
    << std::endl;
    // faster approach if matrix doesnt deviate from square too much follows
    res = matModSearch(vec1, 10, 0, 0, 1, 3);
    std::cout << "row: " << res.first << ", col: " << res.second << std::endl;
    res = matModSearch(vec2, 13, 0, 0, 2, 3);
    std::cout << "row: " << res.first << ", col: " << res.second << std::endl;
    res = matModSearch(vec3, 11, 0, 0, 3, 3);
    std::cout << "row: " << res.first << ", col: " << res.second << std::endl;
}