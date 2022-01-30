#include <iostream>
#include <string>
#include <unordered_map>

struct NumLet {
    int num_app;
    int let_app;
    NumLet(int n = 0, int l = 0): num_app(n), let_app(l) {}
    bool isEq()
    {
        return num_app == let_app;
    }
    friend NumLet operator-(const NumLet &n1, const NumLet &n2)
    {
        return {n1.num_app - n2.num_app, n1.let_app - n2.let_app};
    }
};


//slower solution, O(N^2). upgrade later
std::string letNumApps(const std::string &str)
{
    NumLet arr[str.length()];
    int run_num = 0, run_let = 0;
    int max_len = 0, beg = 0, end;
    for (int i = 0; i < str.length(); i++) { 
        if (isdigit(str[i]))
            arr[i] = {++run_num, run_let};
        else 
            arr[i] = {run_num, ++run_let};
        if (arr[i].num_app == arr[i].let_app && i+1 > max_len) {
            max_len = i+1;
            end = i;
        }
    }

    for (int i = 1; i < str.length(); i++) 
        for (int j = 0; j < i - max_len; j++)
            if ((arr[i] - arr[j]).isEq() && i - j > max_len) {
                max_len = i - j;
                beg = j+1; end = i;
            }
    return str.substr(beg, end - beg +1);
}


//this run in O(N). makes differences array of continious substrings to beginning
// creates hashmap of these differences in second pass, and for each subsequent
// appearance of this difference (appearance of same difference means we added same 
//amount of nums and lets) we subtract value from hashmap, and if its bigger than max_val,
// we put it as new max_val
std::string letNumAppsBet(const std::string &str)
{
    int diff[str.length()];
    int run_num = 0, run_let = 0;
    int max_len = 0, beg = 0, end;
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]))
            diff[i] = ++run_num - run_let;
        else 
            diff[i] = run_num - (++run_let);
        if (diff[i] == 0 && i+1 > max_len) {
            max_len = i+1;
            end = i;
        }
    }    // we created array of differences of continious substrings from beginning till pos i.

    std::unordered_map<int, int> hmap; // maps diff to its first appearance index
    for (int i = 0; i < str.length(); i++) {
        if (hmap.find(diff[i]) == hmap.end())
            hmap[diff[i]] = i;
        else if (i - hmap[diff[i]] > max_len) {
            max_len = i - hmap[diff[i]];     
            beg = hmap[diff[i]] + 1;
            end = i;
        }
    
    }

    return str.substr(beg, end - beg +1);
}

int main()
{
    std:: cout << letNumApps("120a1b21c34") << std::endl;
    std:: cout << letNumAppsBet("120a1b21c34") << std::endl;
}
