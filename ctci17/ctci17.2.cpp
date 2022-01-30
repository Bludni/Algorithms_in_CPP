#include <iostream>
#include <random>

void shuffle(int cards[52], int rand_set)
{
    if (rand_set == 1) return;
    int divider = RAND_MAX / rand_set;
    int max_num = divider * rand_set;
    int card = rand();
    while (card >= max_num) card = rand();
    card /= divider;
    std::swap(cards[card], cards[rand_set - 1]);
    return shuffle(cards, rand_set - 1);
}

int main()
{
    srand(time(0));
    int cards[52];
    for (int i = 0; i < 52; i++) cards[i] = i;
    shuffle(cards, 52);
    for (int i = 0; i < 52; i++) std::cout << cards[i] << " ";
    std::cout << std::endl;  
}