#include <iostream>
#include <vector>

using Mat = std::vector<std::vector<int>>;

struct Pixel {
    int row, col;
    Pixel(int r = 0, int c = 0): row(r), col(c) {}
    Pixel operator+(const Pixel &p)
    {
        return Pixel(row + p.row, col + p.col);
    }
    void print() {
        std::cout << "(" << row << "," << col << ")\n";
    }
};

struct Sums {
    int left,right,bottom,top;
    Sums(int l = 0, int r = 0, int b = 0, int t = 0):
    left(l), right(r), bottom(b), top(t) {}
};


std::vector<std::vector<Sums>> helperSquares(Mat &mat)
{
    //helper creates a matrix with struct that has info about continious black squares
    //in all 4 directions. Leveraging this info, we can immediately know for two pixels
    // if they close a complete rectangle, or square in this case.
    std::vector<std::vector<Sums>> temp(mat.size(), std::vector<Sums>(mat.size(), Sums()));
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++) //first copy the array into the helper
            temp[i][j].right = temp[i][j].left = 
            temp[i][j].bottom = temp[i][j].top = mat[i][j];
            
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size() - 1; j++)
            temp[i][j+1].left += temp[i][j].left; //do the continious squares to left 

    for (int i = 0; i < mat.size() - 1; i++)
        for (int j = 0; j < mat[i].size(); j++)
            temp[i+1][j].top += temp[i][j].top; //do the continious squares to top

    for (int i = mat.size() - 1; i > 0; i--)
        for (int j = 0; j < mat[i].size(); j++)
            temp[i-1][j].bottom += temp[i][j].bottom; //do the continious squares to bottom

    for (int i = 0; i < mat.size(); i++)
        for (int j = mat[i].size() - 1; j > 0; j--)
            temp[i][j-1].right += temp[i][j].right; //do the continious squares to right
    return temp;
}

bool inBounds(int row, int col, int maxrow, int maxcol)
{
    return row >= 0 && col >= 0 && row < maxrow && col < maxcol;
}

//Works in O(N^3) time and O(N^2) memory
std::pair<Pixel,Pixel> sqFinder(Mat &mat)
{ // we go over every diagonal and by info from helper we get for two
 // corners immediately if they close rectangle.
    auto helper = helperSquares(mat);
    int max_edge = 0;
    Pixel top_left, bot_right;
    for (int k = 0; k < mat.size() - 1; k++) {
        for (Pixel i = Pixel(1, k+1); 
             inBounds(i.row, i.col, mat.size(), mat.size());
             i = i + Pixel(1,1))
            for (Pixel j = Pixel(0,k); j.row < i.row - max_edge + 1;
                         j = j + Pixel(1,1)) {
                if(helper[i.row][i.col].left > i.col - j.col &&
                   helper[i.row][i.col].top > i.row - j.row &&
                   helper[j.row][j.col].right > i.col - j.col &&
                   helper[j.row][j.col].right > i.row - j.row &&
                   i.row - j.row + 1 > max_edge) {
                       top_left = j;
                       bot_right = i;
                       max_edge = i.row - j.row + 1;
                }
            }
    
        for (Pixel i = Pixel(k+2, 1); 
             inBounds(i.row, i.col, mat.size(), mat.size());
             i = i + Pixel(1,1))
            for (Pixel j = Pixel(k+1,0); j.row < i.row - max_edge + 1;
                         j = j + Pixel(1,1)) {
                if(helper[i.row][i.col].left > i.col - j.col &&
                   helper[i.row][i.col].top > i.row - j.row &&
                   helper[j.row][j.col].right > i.col - j.col &&
                   helper[j.row][j.col].bottom > i.row - j.row &&
                   i.row - j.row + 1 > max_edge) {
                       top_left = j;
                       bot_right = i;
                       max_edge = i.row - j.row + 1;
                }
            }
    
    }
    return std::make_pair(top_left,bot_right);
}


//find biggest rectangle with black pixels as edges in black-white matrix
int main()
{
    Mat mat = {{0,0,0,0,0,1},
               {0,1,1,1,1,0},
               {0,1,1,0,1,0},
               {0,1,1,1,1,0},
               {0,1,1,1,1,0},
               {0,0,0,0,0,0}};
    auto result = sqFinder(mat);
    result.first.print();
    result.second.print();
}