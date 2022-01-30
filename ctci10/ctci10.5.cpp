#include <iostream>
#include <string>
#include <vector>

int sparseSearch(const std::vector<std::string> &vec, const std::string &str)
{
    int beg = 0, end = vec.size() - 1;
    int middle;
    while (beg <= end) {
        middle = (beg + end) / 2;
        if (vec[middle] == "") {
            int left = middle, right = middle;
            while (vec[--left] == "" && vec[++right] == ""); //find first non empty string
            middle = (vec[left] != "")? left : right; //put middle as that
        }
        if (vec[middle] > str) //continue classic binary search
            end = middle - 1;
        else if (vec[middle] < str)
            beg = middle + 1;
        else return middle;
    }
    return -1;
}

//sparse search
int main()
{
    std::vector<std::string> vec = {"at","","","","ball","","",
                                    "car","","","dad","",""};
    std::cout << sparseSearch(vec, "dad") << std::endl;
}