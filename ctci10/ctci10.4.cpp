#include <iostream>

struct Listy {
    private:
        int size;
        int *list;
    public:
        Listy(int array[], int size) : size(size)
        {
            list = static_cast<int*>(malloc(size * sizeof(int)));
            for (int i = 0; i < size; i++) 
                list[i] = array [i];
        }
        
        void print()
        {
            for (int i = 0; i < size; i++)
                std:: cout << list[i] << " ";
            std::cout << std::endl;
        }

        int elementAt(int i)
        {
            return (i < size)? list[i] : -1;
        }
};

int findEl(Listy listy, int el)
{
    int prev = 0, next = 0, inc = 1;
    while (listy.elementAt(next) < el && (listy.elementAt(next) != -1)) {
        prev = next; next += inc; inc *= 2; // double the increment to simulate a binary search without knowing size
    }
    if (listy.elementAt(next) == el) return next;
    //binary search time
    int middle;
    while (prev <= next) {
        middle = (prev + next) / 2;
        if (listy.elementAt(middle) == -1 || listy.elementAt(middle) > el)
            next = middle - 1;
        else if (listy.elementAt(middle) < el)
            prev = middle + 1;
        else 
            return middle; // found it           
    }
    return -1; //not found
}

int main()
{
    int size = 10;
    int array[] = {1,2,3,4,10,11,15,20,22,30};
    Listy some_listy(array, size);
    some_listy.print();
    std::cout << findEl(some_listy, 22) << std::endl;
}