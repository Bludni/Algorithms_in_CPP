#include <iostream>
#include <vector>

std::vector<std::vector<int>>& rotate90(std::vector<std::vector<int>>& arr){
    for (int i = 0; i < arr.size()/2; i++)
        for (int j = i; j < arr[i].size() - i - 1; j++){
            int temp1 = arr[i][j], temp2, index;
            for (int k = 0; k <= 3; k++) {
                temp2 = arr[j][arr[i].size() - 1 - i];
                arr[j][arr[i].size() - 1 - i] = temp1;
                temp1 = temp2;
                index = j;  
                j = arr[i].size() - 1 - i;
                i = index; 
            }
        }
    return arr;
}

int main()
{
    std::vector<std::vector<int>> arr = {{1,2,3},{4,5,6},{7,8,9}};
    std::cout << "Program rotira kvadratnu matricu za 90 stepeni" << std::endl;
    arr = rotate90(arr);
    for (int i = 0; i < arr.size(); i++)
        for (int j = 0; j < arr[i].size(); j++) {
            std::cout << arr[i][j];
            if (j == arr[i].size() - 1) {
                std::cout << std::endl;
                continue;
            }
            std::cout << " | ";
        }
}