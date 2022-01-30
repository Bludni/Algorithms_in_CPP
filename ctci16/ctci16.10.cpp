#include <iostream>
#include <vector>

struct LifeCard {
    int birth;
    int death;
};

static LifeCard YEARS[200] = {{0,0}};

int main()
{
    std::vector<LifeCard> people = {{1900,1950}, {1949, 1988},{1989, 2001}}; 
    for (auto human : people) {
        YEARS[human.birth - 1900].birth++;
        YEARS[human.death - 1900].death++;
    }
    std::vector<int> max_years;
    int max_alive = 0, alive = 0;
    for (int i = 0; i < 200; i++) {
        alive += YEARS[i].birth;
        if (alive > max_alive) {
            alive = max_alive;
            max_years.clear();
            max_years.push_back(i + 1900);
        }
        else if (alive == max_alive) 
            max_years.push_back(i + 1900);
        alive -= YEARS[i].death;
    }

    for (auto mem : max_years) std::cout << mem << std::endl;
}