#include <iostream>
#include <vector>
#include <fstream>
#include <string>

typedef enum {
    BLACK,
    WHITE,
    RED,
    GREEN,
    BLUE
} Color;

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

void paintfill(int row, int col, Color old_color, Color new_color, 
               std::vector<std::vector<int>> &img)
{
    if (row >= img.size() || row < 0 || col > img[0].size() || col < 0)
        return;
    if (img[row][col] != old_color) return; 
    img[row][col] = new_color;
    paintfill(row - 1, col - 1, old_color, new_color, img);
    paintfill(row - 1, col, old_color, new_color, img);
    paintfill(row - 1, col + 1, old_color, new_color, img);
    paintfill(row, col - 1, old_color, new_color, img);
    paintfill(row, col + 1, old_color, new_color, img);
    paintfill(row + 1, col - 1, old_color, new_color, img);
    paintfill(row + 1, col, old_color, new_color, img);
    paintfill(row + 1, col + 1, old_color, new_color, img);
}

int main(int argc, char **argv)
{
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error opening the file!" << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<std::vector<int>> img;
    std::string line;
    while (std::getline(input,line)) 
        img.push_back(numParser(line, false));
    paintfill(2, 1, RED, BLUE, img);
    for (auto row : img) {
        for (auto mem : row)
            std::cout << mem << " ";
        std::cout << std::endl;
    }   
}