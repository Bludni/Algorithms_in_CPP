#include <iostream>
#include <random>

class Mastermind {
    private:
        char comb[4];
        int col[4]; // array with numbers representing colors(each place has weight
        bool all_colors[128] = {false};              //going as degree of 2). switch below gives color values
    public:
        Mastermind()
        {
            for (int i = 0; i < 4; i++) col[i] = 0;
            all_colors['R'] = true; all_colors['G'] = true;
            all_colors['B'] = true; all_colors['Y'] = true;
            this->start();
        }
 
    private:
        void start()
        {
            generateComb();
            printf("Put your guess without whitespaces!");
            printf("\nPossible input is RGBY, upper or lower.\n\n");
            for (int i = 6; i > 0; i--) {
                char g[4];
                guess(g);   std::cout << std::endl;
                if (victory(g)){
                    std::cout << "\nYou got it! Congratulations!"
                    << std::endl;
                    return;
                } 
            }
            std::cout << std::endl << 
            "You run out of tries! Game over!\n\n"; 
        }

        char generateLetter()
        {
            int div = (RAND_MAX / 4);
            int max_rand = div * 4;
            int temp = rand();
            while (temp >= max_rand) 
                temp = rand();
            switch(temp / div) {
                case 0 : return 'R';
                case 1 : return 'Y';
                case 2 : return 'G';
                case 3 : return 'B';
                default : return ' ';
            }
        }

        int let2num(char c)
        {
            switch(c) {
                case 'R' : return 0;
                case 'Y' : return 1;
                case 'G' : return 2;
                case 'B' : return 3;
                default  : return -1;
            }
        }

        void generateComb()
        {
            srand(time(0));
            for (int i = 0; i < 4; i++) { 
                comb[i] = generateLetter();
                col[let2num(comb[i])] += (1 << i); 
            }
        }

        void insertSort(char arr[], int size)
        {
            for (int i = 0; i < size; i++)
                for (int j = size - 1; j > i; j--)
                    if (arr[j] < arr[j-1]) 
                        std::swap(arr[j-1], arr[j]);
        }

        bool victory(const char g[4])
        {
            for (int i = 0; i < 4; i++)
                if (g[i] != 'H') return false;
            return true;
        }


        int bitLength(int num) {
            switch(num) {
                case 0: return 0;
                case 1:
                case 2:
                case 4:
                case 8: return 1;
                case 3:
                case 5:
                case 6:
                case 9:
                case 10:
                case 12: return 2;
                case 7:
                case 11:
                case 14: return 3;
                case 15: return 4;
                default: return -1;
            }
        }

        void insertOver(char g[4], char c, int &pos, int num)
        {
            for (; num > 0; num--)
                g[pos++] = c;
        }

        void guess(char g[4])
        {
            bool cond = true;
            while (cond) {
                scanf("%s", g);
                cond = false;
                for (int i = 0; i < 4; i++) {
                    g[i] = toupper(g[i]);
                    if (!all_colors[g[i]]) {
                        std::cout << "\t\t\t\t Mistake! Correct the input!" <<
                        "(RGBY is available)" << std::endl;
                        i = 4; cond = true;     
                    }
                }
            }
            char col_guess[4] = {0};
            for (int i = 0; i < 4; i++) 
                col_guess[let2num(g[i])] += (1 << i);
            int i = 0, j = 0, sum = 0; //i is index, j is for position of overwrite and 
            //sum is for break condition if all colors are checked before last element 
            while (sum < 15) {
                if (col_guess[i]) {
                    int numh = bitLength(col_guess[i] & col[i]);
                    int nump = std::min(bitLength(col_guess[i]), 
                                        bitLength(col[i])) - numh;
                    sum += col_guess[i];
                    insertOver(g, 'H', j, numh);
                    insertOver(g, 'P', j, nump);
                }
                i++;
            }
            insertOver(g, '_', j, 4-j); // fill the rest as empty
            insertSort(g, 4);
            std::cout << "\t\t\t\t";
            for (int i = 0; i < 4; i++) std::cout << g[i];
        }

};

int main()
{
    while (true)
    {
        Mastermind game;
        std::cout << "\nDo you wish to play again?(Y/N)\n";
        char cont;
        std:: cin >> cont;
        if (cont == 'Y' || cont == 'y') {
            std::cout << std::endl;
            continue;
        }
        else break; 
    }
}