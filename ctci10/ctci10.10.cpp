#include <iostream>

struct IntStream {
    private:
        int *stream;
        int size;
        int end_alloc;

    public:
        IntStream(int arr[] = NULL, int size = 0, int end_alloc = 4):
            end_alloc(end_alloc)
        {
            if (size > end_alloc) end_alloc = size; 
            stream = (int*) malloc(end_alloc * sizeof(int));
            IntStream::size = 0;
            for (int i = 0; i < size; i++) { 
                pushToStream(arr[i]);
            }
        }
        
        void pushToStream(int n)
        {
            if (++size >= end_alloc) {
                stream = (int*) realloc(stream, 2*end_alloc);
                end_alloc *= 2;
            } 
            if (size == 1) {
                stream[0] = n;
                return;
            }
            int i = size - 2; // since we increased size immediately upon enetring 
            //the function, we need to drop it by 2;
            for ( ; i >= 0; i--)
                if (stream[i] > n) 
                    stream[i+1] = stream[i]; 
                else 
                    break; 
            stream[++i] = n;
        }

        int getRankOf(int n)
        {
            int beg = 0, end = size - 1;
            int middle;
            while (beg <= end) {
                middle = (beg + end) / 2;
                if (n > stream[middle])
                    beg = middle + 1;
                else if ( n < stream[middle])
                    end = middle - 1;
                else return middle;
            }
            return -1; // not found
        }
        
        void printStream()
        {
            for (int i = 0; i < size; i++)
                std::cout << stream[i] << " ";
            std::cout << std::endl;
        }

        ~IntStream()
        {
            free(stream);
            stream = NULL;
        }
};

//this algorithn can be optimized for insertion and searching by creating a binary tree.
//since it is worthless without knowing how to balance a tree, i skipped it here
int main()
{
    int arr[] = {7,2,4,1}; int size = 4;
    IntStream streamy(arr, size);
    streamy.pushToStream(3);
    std::cout << streamy.getRankOf(4) << std::endl;
    streamy.printStream();
}