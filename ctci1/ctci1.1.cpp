#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    string word;    unordered_map<char, int> umap;   bool unique = true;
    cout << "Provera da li string ima sve jedinstvene karaktere!" << endl;
    cout << "Unesite string: ";
    cin >> word;

// with hash map    
    for (char c : word) {
        if (umap.find(c) != umap.end()) {
            unique = false;
            break;
        }
        umap[c] = 1;
    }

    if (unique == false) cout << "String nema sve jedinstvene karaktere." << endl;
    else  cout << "String ima sve jedinstvene karaktere." << endl;
}