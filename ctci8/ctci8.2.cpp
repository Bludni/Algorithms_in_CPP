#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<int> numParser(std::string &str, bool negative)
{
    std::vector<int> temp;
    int i = 0, j = 0;
    for ( ; i < str.length(); i++)
        if (isdigit(str[i]) || str[i] == '-' && negative) {
            j = i;
            while (isdigit(str[++i]));
            if ((str[j] == '-') && (i - j == 1)) continue;
            temp.push_back(std::stoi(str.substr(j, i - j)));
            if (str[i] == '-') i--;
        }
    return temp;
}

// initial cond is false, am row and col are 0
bool& getPath(bool &cond, int row, int col,
              std::vector<std::vector<int>> &vec)
{
    if (row == vec.size() - 1 && col == vec[0].size() - 1) {
        cond = true;
        vec[row][col] = 1; 
        return cond;
    }
    if (row >= vec.size() || col > vec[0].size()) return cond;
    if (cond || vec[row][col] >= 2) return cond;
    getPath(cond, row, col + 1, vec);
    getPath(cond, row + 1, col, vec);
    if (cond) {
        vec[row][col] = 1;
        return cond;
    }
    vec[row][col] = 3;
    return cond;
}

int main(int argc, char **argv)
{
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error opening the file!" << std::endl;
        return EXIT_FAILURE;
    }

    std::string line;
    std::vector<std::vector<int>> vec;
    while (std::getline(input, line)) {
        std::vector<int> temp = numParser(line, false);
        vec.push_back(temp);
    }
    bool cond = false;
    if (getPath(cond, 0, 0, vec))
        for (auto row : vec) {
            for (auto mem : row)
                std::cout << mem << " ";
            std::cout << std::endl;
        }
    else std::cout << "There is no path!" << std::endl;
}