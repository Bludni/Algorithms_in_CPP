#include <iostream>
#include <string>

static const char *ones[] = {"","one","two","three","four",
                             "five","six","seven","eight","nine"};

static const char *tens[] = {"","ten","twenty","thirty","fourty",
                             "fifty","sixty","seventy","eighty","ninety"};

static const char *firstTen[] = {"","eleven","twelve","thirteen",
                                 "fourteen","fifteen","sixteen",
                                 "seventeen","eighteen","nineteen"};

void addName(int digit_ind, int digit, int digit_before, 
             int num_after, std::string &name)
{
    switch(digit_ind % 3) {
        case 0 : {
            name += " " + std::string(ones[digit]) + " hundred"; 
            return;
        }
        case 1 : { 
            if (!num_after) name += " " + std::string(ones[digit]);
            return;
        }
        case 2 : {
            name += (digit == 1)? 
                            " " + std::string(firstTen[digit_before]) :
                            " " + std::string(tens[digit]) + " " 
                                +  std::string(ones[digit_before]);
            return;
        }
        default : return;
    }
}

void addTripletName(int digit, std::string &name)
{
    switch (digit)
    {
        case 4 : {
            name += " thousand";
            return;    
        }
        case 7 : {
            name += " million";
            return;
        }
        case 10 : {
            name += " billion";
            return;
        }
        default: return;
    }
}

void numberName(int num, std::string &name, int digit, int digit_val = 0)
{
    if (!num) return;
    numberName(num / 10, name, digit + 1, num % 10);
    addName(digit, num % 10, digit_val, num / 10, name);
    addTripletName(digit, name);   
}

int main()
{
    std::string name; int num = 1985116221;
    numberName(num, name, 1);
    std::cout << name.erase(0,1) << std::endl;
}


