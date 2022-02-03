#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <limits>

struct TrieNode {
    char letter;
    std::unordered_map<char, TrieNode*> next;
    TrieNode(char l = 0): letter(l) {}
};

struct PrefixTree {
    TrieNode *root;
    PrefixTree() 
    {
        root = new TrieNode(' ');
    }

    void addWord(const std::string &s)
    {
        auto *curr = root;
        for (auto c : s) {
            if (curr->next.find(c) == curr->next.end()) 
                curr->next[c] = new TrieNode(c);
            curr = (curr->next[c]);
        }
        if (curr->next.find('*') == curr->next.end())
            curr->next['*'] = new TrieNode('*'); 
    }
    
    void fillTrie(const std::vector<std::string> &dict)
    {
        for (auto d : dict)
            addWord(d);
    }

    void destroyTree(TrieNode *pok)
    {
        if (pok == NULL) return;
        for (auto c : pok->next) {
            destroyTree(c.second);
            c.second = NULL;
        }
        delete pok;
    }

    bool checkLetter(const char c, const TrieNode *pok)
    {
        return pok->next.find(c) != pok->next.end();
    }

    bool isword(const TrieNode *pok)
    {
        return pok->next.find('*') != pok->next.end();
    }

    TrieNode* nextLetter(const char c, TrieNode *pok)
    {
        return (checkLetter(c,pok))? pok->next[c] : NULL;
    }

    TrieNode* getRoot()
    {
        return root;
    }

    //find number of unmatchable chars to words in prefix tree and return as true_min
    //str is the string to find words in, pok is pointer to trie node, ind is the
    //index of the string from where we continue search, runner is following current
    //reconstruction, word matches current word during search and res is vector 
    //which stores multiple possible reconstructions
    void recStr(const std::string &str, TrieNode *pok, int ind,
                std::string &runner, int run_min, int &true_min,
                std::string &word, std::vector<std::string> &res)
    {
        if (run_min > true_min) return;
        if (ind == str.length()) {
            if (run_min < true_min) {
                res.clear();
                true_min = run_min; 
            }
            res.push_back(runner);
            return;
        }
        int j = ind;
        TrieNode *temp;
        if (this->checkLetter(str[j], pok)) { // check if there is next letter for this partial word
            runner.push_back(str[j]);  word.push_back(str[j]);          
            temp = this->nextLetter(str[j++], pok);   //go to next letter in prefix tree    
            if (this->checkLetter('*', temp)) {
                std::string new_word;
                runner.push_back(' ');
                recStr(str,this->root,j,runner,run_min,true_min,new_word,res); //complete word, continue search from root, and next letter
                runner.pop_back();
            }
            if (j < str.length()) //if before the last letter
                recStr(str,temp,j,runner,run_min,true_min,word,res); //not complete word, continue filling it
            word.pop_back();
            if (word.empty()) {
                runner.push_back('_'); //this signifies the letter before isnt matched with any word in this search
                recStr(str,root,ind + 1,runner,run_min + 1,true_min,word,res); // mark letter as not found and search further
                runner.pop_back();  //runner.pop_back();
            }
            runner.pop_back();
        }
        else { 
            if (!word.empty()) return;
            runner.push_back(str[ind]);
            runner.push_back('_'); 
            recStr(str,root,ind + 1,runner,run_min + 1,true_min,word,res);
            runner.pop_back(); runner.pop_back();
        }

    } //has room for improvements with memoization and return value of the function

    ~PrefixTree()
    {
        destroyTree(root);
    }
};

int main() 
{
    std::vector<std::string> dict = {"looked", "just", "like", "her",
     "timber", "look", "bro", "the"};
    PrefixTree trie;
    trie.fillTrie(dict);
    std::string sent = "jesslookedjustliketimherbrother";
    std::vector<std::string> res;
    auto *pok = trie.getRoot();
    std::string runner, word;
    int true_min = std::numeric_limits<int>::max();  
    trie.recStr(sent,pok,0,runner,0,true_min,word,res);
    std::cout << "Possible reconstructed sentences:\n\n";
    for (auto &mem : res) {
        if (mem.back() == ' ') mem.pop_back();
        std::cout << mem << std::endl;
    }
    std::cout << "\nNumber of unrecognized characters: " << true_min << std::endl;   
}