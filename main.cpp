#include <iostream>
#include "algoritmCYK.h"

using namespace std;

int main() {
    AlgoritmCYK algoritm;
    //algoritm.afisareProductii();
    algoritm.completareMatrice();
    algoritm.afisareMatrice();
    if (algoritm.acceptat())
        cout << "\nCuvantul este acceptat.";
    else cout << "\nCuvantul nu este acceptat.";
}