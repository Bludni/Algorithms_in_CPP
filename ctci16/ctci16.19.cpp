#include <iostream>
#include <vector>

using Mat = std::vector<std::vector<int>>;

struct Direction {
    int inc_row;
    int inc_col;
};

std::vector<Direction> DIR = {{-1,-1},{-1,0,},{-1,1},{0,-1},
                              {0,1},{1,-1},{1,0},{1,1}};

bool inBounds(int row, int col, int row_max, int col_max)
{
    return row >= 0 && row < row_max && col >= 0 && col < col_max;
}

int surfPond(int row, int col, Mat &mat, Mat &tracker)
{
    int surface = 1, new_row, new_col;
    for (auto dir : DIR) {
        new_row = row + dir.inc_row;
        new_col = col + dir.inc_col;
        if (inBounds(new_row, new_col, mat.size(), mat[0].size()))
            if (!mat[new_row][new_col] && !tracker[new_row][new_col]){
                tracker[new_row][new_col] = 1;
                surface += surfPond(new_row, new_col, mat, tracker);
            }
    }
    return surface;
}

std::vector<int> allPonds(Mat &mat)
{
    int surface = 0; 
    std::vector<int> surfs;
    Mat tracker(mat.size(), std::vector<int>(mat[0].size(), 0));
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++) 
            if (!mat[i][j] && !tracker[i][j]) {
                tracker[i][j] = 1;
                surfs.push_back(surfPond(i, j, mat, tracker));
            } 
    return surfs;
}

int main(){
    Mat mat = {{0,2,1,0},{0,1,0,1},{1,1,0,1},{0,1,0,1}};
    std::vector<int> surfaces = allPonds(mat);
    for (auto mem : surfaces)
        std::cout << mem << " ";
    std::cout << std::endl;
}