#include <iostream>
#include <bitset>

void drawLine(char screen[], int w, int x1, int x2, int y)
{
    int row_start = y * w;
    int p1_start = row_start + x1 / 8;
    int p2_start = row_start + x2 / 8;
    if (p1_start == p2_start) {
        screen[p1_start] |= (((1 << (x2 - x1 + 1)) - 1) << 
                            ((p1_start - row_start) * 8 + 7 - x2));
        return; 
    }
    screen[p1_start] |= (0xff >> (x1 - (p1_start - row_start) * 8));
    for(int i = p1_start + 1; i < p2_start; i++)
        screen[i] = 0xff;
    screen[p2_start] |= (0xff << ((p2_start - row_start) * 8 + 7 - x2));
}

int main()
{
    char screen[128] = {'\0'};
    drawLine(screen, 4, 11, 14, 14);
    int w = 0;
    for (auto c : screen) {
        std::cout << std::bitset<8>(c);
        if (w++ == 3) {
            std::cout << std::endl;
            w = 0;
        }
    }
}