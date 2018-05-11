#include <fstream>
#include "algoritmCYK.h"

/**
 * constructor
 */
AlgoritmCYK::AlgoritmCYK() {
    ifstream f("gramatica.in");
    f >> numarProductii; //citesc numarul de productii
    productii = new char *[numarProductii]; //aloc memorie pentru productii
    int i, j; //contoare
    for (i = 0; i < numarProductii; i++) //citesc productiile
    {
        string productieAuxiliara; //folosesc un string suplimentar pentru a sti cata memorie
        // trebuie sa aloc pentru fiecare productie in parte
        f >> productieAuxiliara;
        int n = productieAuxiliara.size();
        productii[i] = new char[n + 1];
        for (j = 0; j < n; j++)
            productii[i][j] = productieAuxiliara[j]; //memorez productiile
        productii[n + 1] = nullptr; //marchez sfarsitul productiei
    }
    cout << "Introduceti cuvantul:\n";
    cin >> cuvant; //citesc cuvantul pe care trebuie sa il verific
    matrice = new deque<char> *[cuvant.size()]; //aloc memorie pentru matricea triunghiulara
    for (i = 0; i < cuvant.size(); i++)
        matrice[i] = new deque<char>[cuvant.size() - i];
}

/**
 * destructor
 */
AlgoritmCYK::~AlgoritmCYK() {
    int i;
    for (i = 0; i < numarProductii; i++)
        delete[] productii[i];
    delete[] productii; //eliberez memoria ocupata de productii
    for (i = 0; i < cuvant.size(); i++)
        delete[] matrice[i];
    delete[] matrice; //eliberez memoria ocupata de matricea triunghiulara
}

/**
 * metoda de afisare a productiilor citite din fisier
 */
void AlgoritmCYK::afisareProductii() {
    for (int i = 0; i < numarProductii; i++)
        cout << productii[i] << '\n';
}