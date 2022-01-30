#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> matrix;

void zeroize(matrix& mat)
{ //bolje resenje od ovog je ako se iskoriste prvi red i kolona matrice
    int red[mat.size()] = {0}, kolona[mat[0].size()] = {0};
    //pravimo mapu sa indikacijom gde idu nule prema redu i koloni
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++) 
            if (mat[i][j] == 0) {
                red[i] = 1;
                kolona[j] = 1;
            }
    // stavljamo nule u matricu na oznacena mesta
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++)
            if (red[i] || kolona[j]) mat[i][j] = 0;
}

void zeroize2(matrix& mat)
{
    bool row_zero = false, col_zero = false;
    //pravimo mapu sa indikacijom gde idu nule prema redu i koloni.
    //posto koristimo prvi red i kolonu, proveravamo da li oni imaju 0
    for (int i = 0; i < mat[0].size(); i++) 
        if (mat[0][i] == 0) {
            row_zero = true;
            break;
        }
    for (int i = 0; i < mat.size(); i++) 
        if (mat[i][0] == 0) {
            col_zero = true;
            break;
        }  
    //mapiranje redova i kolona sa nulama
    for (int i = 1; i < mat.size(); i++)
        for (int j = 1; j < mat[i].size(); j++) 
            if (mat[i][j] == 0) {
                mat[i][0] = 0;
                mat[0][j] = 0;
            }
    // stavljamo nule u matricu na oznacena mesta
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++)
            if (!(mat[i][0] && mat[0][j])) mat[i][j] = 0;
    //prvi red i prva kolona se stavljaju na 0 ukoliko treba
    if (row_zero) for (int i = 0; i < mat[0].size(); i++) mat[0][i] = 0;
    if (col_zero) for (int i = 0; i < mat.size(); i++) mat[i][0] = 0; 
}


int main ()
{
    matrix mat {{1,0,2,1},{2,3,3,2},{1,4,2,5},{2,2,4,0}};

    std::cout << "Program postavlja 0 u redove i kolone matrice onog \
    elementa koji je 0 u originalnoj matrici" << std::endl;
    zeroize2(mat);
    for (int i = 0; i < mat.size(); i++)
        for (int j = 0; j < mat[i].size(); j++) {
            std::cout << mat[i][j];
            if (j == mat[i].size() - 1) {
                std::cout << std::endl;
                continue;
            }
            std::cout << " | ";
        }
}