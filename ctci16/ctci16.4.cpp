#include <iostream>

class TicTacToe {
    char board[3][3];
    public:
        struct Position {
            int row;
            int col;
            Position (int r = 0, int c = 0): row(r), col(c) {}

            friend Position operator+(const Position &p1, const Position &p2)
            {
                int new_row = (p1.row + p2.row > 2)? 
                            p1.row + p2.row -3 : p1.row + p2.row;
                int new_col = (p1.col + p2.col > 2)?
                            p1.col + p2.col -3 : p1.col + p2.col;
                return Position(new_row, new_col);
            }
        };
        
        TicTacToe(char arr[3][3])
        {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    board[i][j] = arr[i][j];
        }

        char getField(const Position &p)
        {
            return board[p.row][p.col];
        }

        bool checkThree(const Position &p1, const Position &inc)
        {
            return getField(p1) == getField(p1 + inc) && 
                   getField(p1) == getField(p1 + inc + inc);
        }

        char findWinner()
        {
            bool cond = false; Position curr;
            Position vert(0,1),hor(1,0),diag1(1,1), diag2(-1,1);
            cond = cond || checkThree(curr, vert) || checkThree(curr, hor) 
                    || checkThree(curr, diag1);
            if (cond) return getField(curr);
            curr = curr + diag1;
            cond = cond || checkThree(curr,vert) || checkThree(curr, hor)
                   || checkThree(curr, diag2);
            if (cond) return getField(curr);
            curr = curr + diag1;
            cond = cond || checkThree(curr,vert) || checkThree(curr, hor);
            if (cond) return getField(curr);
            return ' '; //no winner
        }        
};

int main()
{
    char arr[3][3] = {{'X','O','O'}, {'O','O','X'},{'X','X','X'}};
    TicTacToe game(arr);
    char winner = game.findWinner();
    if (winner != ' ') std::cout << "Winner is player " << winner << std::endl;
    else std::cout << "Game is a tie!" << std::endl;
}

