#include <iostream>
#include <random>
#include <vector>


void prep_test(int num_bottles, std::vector<std::vector<bool>> &test_tracks)
{
    for (int i = 0; i < num_bottles; i++) {
        int j = i, ind = test_tracks.size() - 1; 
        while (j != 0) {
            if ( j & 1) test_tracks[ind][i] = true;
            j >>= 1; ind--;
        }
    }
}

int test(int pois_bot, std::vector<std::vector<bool>> &test_tracks)
{
    int ret_val = 0;
    for (auto track : test_tracks) 
        if (track[pois_bot]) ret_val = ret_val * 2 + 1;
        else ret_val *= 2; 
    return ret_val;
} 

int main()
{
    srand(time(0));
    int num_tests = 10;
    int num_bottles = 1000;
    int divider = RAND_MAX / num_bottles;
    int rand_max = divider * num_bottles;
    int pois_bot;
    while (true) {
        int temp = rand();
        if (temp < rand_max) {
            pois_bot = temp / divider;
            break;
        }
    } 
    std::vector<std::vector<bool>> test_tracks(num_tests, 
                    std::vector<bool>(num_bottles, false));
    prep_test(num_bottles, test_tracks);
    std::cout << "Poisoned bottle is: " << 
            test(pois_bot, test_tracks) << std::endl;            
}