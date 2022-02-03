#include <iostream>
#include <vector>
#include <tuple>
#include <limits>

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

Mat MatOfSum(Mat &mat)
{
    Mat temp = mat;
    for (int i = 1; i < temp.size(); i++) //first row
        temp[0][i] += temp[0][i-1];
    for(int i = 1; i < temp.size(); i++) //firsr col
        temp[i][0] += temp[i-1][0];
    
    for (int i = 1; i < temp.size(); i++)
        for (int j = 1; j < temp.size(); j++)
            temp[i][j] += temp[i-1][j] + temp[i][j-1] - temp[i-1][j-1];
    return temp;
}

int el(Mat &mat, int row, int col)
{
    return (row >= 0 && col >= 0 && row < mat.size() && col < mat.size())?
            mat[row][col] : 0;
}

std::tuple<Pixel,Pixel,int>  maxSumSubm(Mat &mat)
{
    auto mat_sum = MatOfSum(mat);
    int max_sum = std::numeric_limits<int>::min();
    Pixel top_left, bot_right;
    for (int ibr = 0; ibr < mat.size(); ibr++)
        for (int jbr = 0; jbr < mat.size(); jbr++)
            for (int itl = 0; itl <= ibr; itl++)
                for (int jtl = 0; jtl <= jbr; jtl++) {
                    int sum = el(mat_sum,ibr,jbr) - el(mat_sum,ibr, jtl-1)
                            - el(mat_sum,itl-1,jbr) + el(mat_sum,itl-1,jtl-1);
                    if (sum > max_sum) {
                        max_sum = sum;
                        top_left = Pixel(itl,jtl);
                        bot_right = Pixel(ibr,jbr);
                    } 
                }
    return std::make_tuple(top_left,bot_right,max_sum);
}

// Program returns submatrix with maximum sum.
int main()
{
    Mat mat ={{0,0,-1,-1},
              {-1,1,2,-1},
              {0,1,1,-1},
              {0,4,-1,1}};
    Pixel tl, br;
    int max;
    std::tie(tl,br,max) = maxSumSubm(mat);
    tl.print(); br.print();
    std::cout << max << std::endl;   
}