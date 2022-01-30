#include <iostream>
#include <string>

std::string& bin2str(int num, std::string& str)
{
    if (num == 0) return str;
    bin2str(num / 2, str);
    str.push_back(num & 1 ? '1' : '0');
    return str;
}

int oneFlip1s(std::string str)
{
    int count1 = 0, count2 = 0, max = 1;
    for (auto c : str) 
        if (c == '0') {
            max = (count1 > max)? count1 : max;
            count1 = ++count2; // starting new flip and counting that zero
            count2 = 0;
        }
        else {
            count1++;
            count2++;
        }
    return max = (count1 > max)? count1 : max;
}

int main()
{
    std::cout << oneFlip1s(std::string("1110111101111011111")) << std::endl;
}