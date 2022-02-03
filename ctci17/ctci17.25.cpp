#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>


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
    
    void fillTrie(const std::unordered_set<std::string> &dict)
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

    bool isleaf(const TrieNode *pok) //I consider to be the leaf a node that doesnt
    // point to other letters exept maybe *
    {
        return isword(pok) && pok->next.size() == 1;
    }

    TrieNode* nextLetter(const char c, TrieNode *pok)
    {
        return (checkLetter(c,pok))? pok->next[c] : NULL;
    }

    TrieNode* getRoot()
    {
        return root;
    }

    ~PrefixTree()
    {
        destroyTree(root);
    }
};



int maxDictWordLen(std::unordered_set<std::string> &dict)
{
    int max_word = 0;
    for (auto word : dict) 
        max_word = (word.length() > max_word)? word.length() : max_word;
    return max_word;
}

std::vector<std::string> filterByLen(std::unordered_set<std::string> &dict,
                                     int len)
{
    std::vector<std::string> res;
    for (auto word : dict)
        if (word.length() == len)
            res.push_back(word);
    return res;
}

//helper function to halve the inserWordRect code
TrieNode* rootOrCurr(PrefixTree &trie, int ind,
                    std::vector<std::vector<TrieNode*>> &curr_rect)
{
    return (curr_rect.empty())? trie.getRoot() : curr_rect.back()[ind]; 
}

bool insertWordRect(PrefixTree &trie, std::string &word,
                std::vector<std::vector<TrieNode*>> &curr_rect)
{
    std::vector<TrieNode*> temp;
    temp.reserve(word.length());
    for (int i = 0; i < word.length(); i++)
        if (trie.checkLetter(word[i], rootOrCurr(trie, i, curr_rect)))
            temp.push_back(trie.nextLetter(word[i], 
                           rootOrCurr(trie, i, curr_rect)));
        else return false;
    curr_rect.push_back(temp);   
    return true;
}    

/*  // I leave this version for reference. It probably is faster since it asks
// only once if curr_rect is empty, but i have faith in the compiler!
bool insertWordRect(PrefixTree &trie, std::string &word,
                std::vector<std::vector<TrieNode*>> &curr_rect)
{
    std::vector<TrieNode*> temp;
    temp.reserve(word.length());
    if (curr_rect.empty()) {
        for (auto c : word) 
            if (trie.checkLetter(c, trie.getRoot()))
                temp.push_back(trie.nextLetter(c, trie.getRoot()));
            else return false;
        curr_rect.push_back(temp);
    }
    else {
        for (int i = 0; i < word.length(); i++)
            if (trie.checkLetter(word[i], curr_rect.back()[i]))
                temp.push_back(trie.nextLetter(word[i], curr_rect.back()[i]));
            else return false;
        curr_rect.push_back(temp);
    }
    return true;
}  */                              

bool validRect(PrefixTree &trie,
               std::vector<std::vector<TrieNode*>> &curr_rect)
{
    if (curr_rect.size() == 1) return true;
    for (auto node : curr_rect.back()) // check the verticals 
        if (!trie.isword(node)) 
            return false;
///the part till return is completely optional, i just wanted to see all rects that program sees
    std::vector<std::string> rect;
    for (auto &row : curr_rect) { //convert pointers to try nodes into letters
        std::string temp;
        for (auto c : row)
            temp.push_back(c->letter);
        rect.push_back(temp);
    }

    for (auto &str : rect) 
        std::cout << str << std::endl;
    std:: cout << "\n";
//////////////////////////////////////////
    return true;
}

void rectByLen(PrefixTree &trie,
               std::vector<std::string> &fixlen_words,
               std::vector<std::vector<TrieNode*>> &curr_rect, 
               std::vector<std::vector<TrieNode*>> &max_rect)
{
    if (!curr_rect.empty())
        for (auto p : curr_rect.back())
            if (trie.isleaf(p)) return; //this means there is a colon that cant support 
        //additional longer words then the current one in the colon

    int max_rect_size = (!max_rect.empty())? 
                          max_rect.size() * max_rect[0].size() : 0;
    for (auto &word : fixlen_words) {
        bool inserted = insertWordRect(trie, word, curr_rect);          
        if (inserted) { // if we inserted the word, we check if its valid rect
            if (validRect(trie, curr_rect)) {
                int curr_rect_size = curr_rect.size() * curr_rect[0].size();
                max_rect = (curr_rect_size > max_rect_size)?
                            curr_rect : max_rect;
            }
            rectByLen(trie,fixlen_words,curr_rect,max_rect); //We continue search with this word
            curr_rect.pop_back();
        }
        
    }
}

std::vector<std::string> rectOfWords(std::unordered_set<std::string> &dict)
{
    std::vector<std::string> result;
    std::vector<std::vector<TrieNode*>> curr_rect; 
    std::vector<std::vector<TrieNode*>> max_rect;
    int max_word = maxDictWordLen(dict);
    PrefixTree trie;
    trie.fillTrie(dict);
   
    for (int i = 1; i <= max_word; i++) { //find the max_rect for each word length
        auto fixlen_words = filterByLen(dict, i);
        if (!fixlen_words.empty()) 
            rectByLen(trie,fixlen_words,curr_rect,max_rect);
    }

    for (auto &row : max_rect) { //convert pointers to try nodes into letters
        std::string temp;
        for (auto c : row)
            temp.push_back(c->letter);
        result.push_back(temp);
    }
    return result; //result holds rectangle as strings
}

int main()
{
    std::unordered_set<std::string> dict = {"BUS","LAVA","ALAV","RAT","SAGA",
                                            "ALA","OTON","RAT","MINI","BABA",
                                            "LAVANDA","LOBANJA","POLAZAK",
                                            "ARI","BARA","LASOM","ULAR","RUKA",
                                            "ALATI","SATI","VAGON","AVANI",};
    auto rect = rectOfWords(dict);
    std::cout << "Max rectangle is:\n\n";
    for (auto &str : rect) 
        std::cout << str << std::endl;
    std::cout << std::endl;
}