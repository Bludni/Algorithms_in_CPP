#include <iostream>
#include <vector>

void print(std::vector<std::vector<char>> board, int count)
{
    std::cout << "Combination " << count << ":" << std::endl;
    for (auto row : board) {
        for (auto mem : row)
            std::cout << mem << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool onBoard(int row, int col)
{
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

bool attacks(int row, int col, std::vector<std::vector<char>> board)
{
    for (int i = 0; i < 8; i++) //vertical and horizontal
        if (board[i][col] == 'K' || board[row][i] == 'K')
            return true;
    std::vector<std::pair<int, int>> 
            increments = {{1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
    for (auto inc : increments) { // diagonal
        int row_ = row + inc.first; 
        int col_ = col + inc.second;
        while (onBoard(row_, col_)) {
            if (board[row_][col_] == 'K')
                return true;
            row_ += inc.first;
            col_ += inc.second;
        }
    }
    return false; // false means its not attacked
}

void queens(int row, int &count, std::vector<std::vector<char>> board)
{
    if (row == 8) {
        print(board, ++count);
        return;
    }
    for (int i = 0; i < 8; i++)
        if (!attacks(row, i, board)) {
            board[row][i] = 'K';
            queens(row + 1, count, board);
            board[row][i] = '*';
        }
}

int main()
{
    std::vector<std::vector<char>> board(8, std::vector<char>(8, '*'));
    int count = 0;
    queens(0, count, board);
}