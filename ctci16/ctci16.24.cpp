#include <iostream>
#include <unordered_set>
#include <vector>
#include <set>

// finds all pairs that sum to given value

struct UserPair {
    int fst;
    int snd;
    UserPair(int f = 0, int s = 0): fst(f), snd(s) {}
    bool operator<(const UserPair &pair) const
    {
        if (fst == pair.snd && snd == pair.fst)
            return false;
        return fst < pair.fst || (fst == pair.fst && snd < pair.snd);
    } 
    friend std::ostream& operator<<(std::ostream& out, const UserPair &p) 
    {
        out << "(" << p.fst << "," << p.snd << ")\n";
        return out;
    } 
};

std::set<UserPair> sumOfTwo (std::vector<int> &vec, int val)
{
    std::set<UserPair> temp;
    std::unordered_set<int> hset;
    for (auto mem : vec) {
        if (hset.find(val - mem) != hset.end())
            temp.insert(UserPair(mem, val-mem));
        hset.insert(mem);
    }
    return temp;
}

int main()
{
    std::vector<int> vec = {1,4,8,2,4,2,5}; int val = 6;
    auto all_pairs = sumOfTwo(vec, val);
    for (auto mem : all_pairs) 
        std::cout << mem;
}
