#include <iostream>
#include <vector>
#include <algorithm>

struct Human {
    int height;
    int weight;
    Human(int h, int w): height(h), weight(w) {}

    bool canGoUnder(const Human &human)
    {
        return height > human.height && weight > human.weight; 
    }
};

//hum is the sorted array of humans, memo is memoization for number of people in the tower
int findMaxTower(std::vector<Human> &hum, std::vector<int> &memo, int ind)
{
    if (memo[ind] != 0) return memo[ind];
    int max_tower = 0;
    for (int i = ind + 1; i < hum.size(); i++) {
        int tower = findMaxTower(hum, memo, i); //filling memo for every box
        if (hum[ind].canGoUnder(hum[i])) { // checking max only if hum[ind] can go under hum[i]
            max_tower = (tower > max_tower)? tower : max_tower;
        }
    }
    max_tower++; //add the current human to the count
    memo[ind] = max_tower;
    return memo[ind];
}

int main()
{
    std::vector<Human> vec = {{80,130}, {65,100}, {70, 150}, {69,120}, {56, 90}, {75, 190}, {60, 95}, {68, 110}};
    std::vector<int> memo(vec.size(), 0);
    std::sort(vec.begin(), vec.end(), [](Human x, Human y) {return x.height > y.height;} );
    findMaxTower(vec, memo, 0);
    int max = 0;
    for (auto m : memo) max = (max < m)? m : max;
    std::cout << max << std::endl;
}