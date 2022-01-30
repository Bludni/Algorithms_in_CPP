#include <iostream>
#include <vector>


//langton ant simulation(cellular automaton)
struct Directions {
    int inc_row;
    int inc_col;
};

static const std::vector<Directions> DIR = {{0,1},{1,0},{0,-1},{-1,0}};

int fastMod(int n, int mod)
{
    return (n >= mod)? n-mod : (n < 0)? n + mod : n;
}

class Ant {
    private:
        int row;
        int col;
        int dir; // index of DIR vec;
        std::vector<std::vector<bool>> grid;
    public:
        Ant(int r = 8, int c = 8, int d = 0) : row(r), col(c), dir(d) 
        {
            for (int i = 0; i < 18; i++) {
                std::vector<bool> temp;
                temp.reserve(18);
                for(int j = 0; j < 18; j++)
                    temp.push_back(0);
                grid.push_back(temp);
            }
        }

        void turn()
        {
            if (grid[row][col]) dir = fastMod(dir + 1, 4);
            else dir = fastMod(dir - 1, 4);
        }
        
        void flip()
        {
            grid[row][col] = !grid[row][col];
        }

        void expand_rows(bool bot)
        {
            int new_row_size = 2 * grid.size();
            std::vector<std::vector<bool>> temp(new_row_size, 
                                std::vector<bool>(grid[0].size(), 0));
            int wrt_beg;
            if (bot) wrt_beg = 0;
            else wrt_beg = grid.size() / 2;
          //  printGrid();
            for (int i = wrt_beg; i < wrt_beg + grid.size(); i++)
                for (int j = 0; j < grid[0].size(); j++) {
                    temp[i][j] = grid[i - wrt_beg][j];
                }
            row += wrt_beg;
            grid = std::move(temp);
        }

        void expand_cols(bool left)
        {
            int new_col_size = 2 * grid[0].size();
            std::vector<std::vector<bool>> temp(grid.size(), 
                                std::vector<bool>(new_col_size, 0));
            int wrt_beg;
            if (left) wrt_beg = 0;
            else wrt_beg = grid[0].size() / 2;
            for (int i = 0; i < grid.size(); i++)
                for(int j = wrt_beg; j < wrt_beg + grid[0].size(); j++)
                    temp[i][j] = grid[i][j - wrt_beg];
            col += wrt_beg;
            grid = std::move(temp);
        }
        
        void forward() 
        {
            row += DIR[dir].inc_row;
            col += DIR[dir].inc_col;
            if (row == grid.size()) expand_rows(1);
            if (row == -1) expand_rows(0);
            if (col == grid[0].size()) expand_cols(1);
            if (col == -1) expand_cols(0);
        }

        void makeAMove(int k = 1)
        {
            for (; k > 0; k--) {
                turn();
                flip();
                forward();
            }
        }

        void printGrid() 
        {
            for (auto row : grid) {
                for (auto mem : row)
                    std::cout << mem;
                std::cout << std::endl;
            }
        }
};

int main()
{
    std::cout << "Input the number of moves of the ant:\n";
    int k;
    std::cin >> k;
    Ant atomic_ant;
    atomic_ant.makeAMove(k);
    atomic_ant.printGrid();
}