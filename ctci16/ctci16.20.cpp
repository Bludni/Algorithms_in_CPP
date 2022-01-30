#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

//phone dialer
static const std::string mapping[10] = {"","","abc","def","ghi","jkl","mno",
                                        "pqrs","tuv","wxyz"};

//solution with hashset, but i think with prefix try it would be much faster
void posWords(const std::string &input, int ind, 
              std::unordered_set<std::string> &dict,
              std::vector<std::string> &words,
              std::string &curr_word)
{
    if (input.length() == curr_word.length()) {
        if (dict.find(curr_word) != dict.end()) 
            words.push_back(curr_word);
        return;
    }
    for (auto c : mapping[input[ind] - 48]) {
        curr_word.push_back(c);
        posWords(input, ind+1, dict, words, curr_word);
        curr_word.pop_back();
    }
}

int main()
{
    std::unordered_set<std::string> dict = {"better","tree","sticky","used","urde"};
    std::vector<std::string> words;
    std::string curr_word;
    posWords("8733", 0, dict, words, curr_word);
    for (auto word : words)
        std::cout << word << " ";
    std::cout << std::endl;
}