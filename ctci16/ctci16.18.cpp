#include <iostream>
#include <string>

//pattern matching (string with pattern consising of a and b into other string)


bool checkPat(const std::string &value, const char c,
              int &pos_val, std::string arr[])
{
    int i = pos_val, j = 0; 
    for (; i < pos_val + arr[c - 97].length(); i++, j++) 
        if (arr[c-97][j] != value[i]) return false;
    pos_val = i;
    return true;
}

bool patternMatch(const std::string &value, const std::string &pattern)
{
    if (pattern.length() == 1 || 
        ((pattern == "ab" || pattern == "ba") && value.length() > 1))
        return true;
    std::string arr[2];
    char c = pattern[0];
    int firstc_app = 0;
    for (auto s : pattern)
        firstc_app += (s == c);
    int secc_app = pattern.length() - firstc_app;
    if (!secc_app) { //only one letter type in pattern
        if (value.length() % firstc_app) return false;
        arr[c-97] = value.substr(0, value.length() / firstc_app);
        return checkPat(value, c, secc_app, arr); //sec_app used because its zero, and func needs a reference 
    }
    int secc_fst = 0;
    while (pattern[++secc_fst] == pattern[0]); // secc_fst is first different from pattern[0] 

    int pos_pat = 1;
    //border for the first for is determined by amount of first element of the pattern(a or b)
    // and the second type of element. because each pattern has to be at least 1 in length
    //we subtract the second pattern appearances and then divide with the first pattern appearance
    // to get the maximum value pattern[0] can have.
    for (int i = 0; i <= (value.length() - secc_app) / firstc_app; i++) {
        arr[c - 97].push_back(value[i]);
        int pos_val = i+1; //we start pattern match after the first symbol

        int inter = value.length() - (firstc_app) * arr[c-97].length();
        if (inter % secc_app) { //second pattern cant be made 
            pos_pat = 1; continue;
        }
        int secc_len = inter / secc_app;
       /* We calculate second pattern length as difference between length of value and assigned
       length to first symbol multiplied by its frequency, then divided with second pattern frequency.
       If these two numbers arent divisible, we cant pattern match that combination */ 
        arr[pattern[secc_fst] - 97] = value.substr(secc_fst * arr[c-97].length(), secc_len);
        while (pos_pat < pattern.length() && 
               checkPat(value, pattern[pos_pat], pos_val, arr)) pos_pat++;

        if(pos_pat == pattern.length() && pos_val == value.length()) 
            return true;
        pos_pat = 1;
        arr[!((bool)(pattern[0] - 97))].erase(); //erase the string thats been in second pat variable
    }    
    return false;
}
int main()
{
    std::cout << patternMatch("catcatgocatgo", "aabab") << std::endl;
}