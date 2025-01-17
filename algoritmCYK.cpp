#include <fstream>
#include <cstring>
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

/**
 * metoda de completare a matricei triunghiulare rezultate in urma aplicarii algoritmului CYK
 */
void AlgoritmCYK::completareMatrice() {
    int i, j, k, r, s, t; //contoare
    bool dublura;
    char *aux;
    for (i = 0; i < cuvant.size(); i++) //completez prima linie a matricei
    {
        for (k = 0; k < numarProductii; k++) //caut productiile in care se regaseste a i-a litera din cuvant
            if (strchr(productii[k], cuvant[i]))
                matrice[0][i].push_back(productii[k][0]); //si adaug neterminalul in matrice
    }
    for (j = 1; j < cuvant.size(); j++) //parcurg matricea incepand cu linia a 2-a (prima linie este deja completata)
        for (i = 0; i < cuvant.size() - j; i++) //pe coloane
            for (k = 0; k < j; k++) {
                for (r = 0; r < matrice[k][i].size(); r++)
                    //parcurg elementele din coada de pe pozitia matrice[k][i]
                    for (s = 0; s < matrice[j - k - 1][i + k + 1].size(); s++)
                        //si pe cele din coada de pe pozitia matrice[j-k-1][i+k+1]
                    {
                        aux = new char[3]; //aux este un sir auxiliar in care se va afla produsul cartezian dintre
                        // un element de pe pozitia matrice[k][i] si un element de pe pozitia matrice[j-k-1][i+k+1]
                        // din cele doua cozi
                        aux[0] = matrice[k][i][r];
                        aux[1] = matrice[j - k - 1][i + k + 1][s];
                        aux[2] = '\0';
                        for (t = 0; t < numarProductii; t++)
                            //caut productiile in care gaseste produsul cartezian obtinut
                        {
                            if (strstr(productii[t], aux)) {
                                dublura = false;
                                for (int it = 0; it < matrice[j][i].size(); it++) //nu vreau ca in matrice, pe o anumita
                                    // pozitie sa imi apara de mai multe ori acelasi neterminal
                                    if (productii[t][0] == matrice[j][i][it]) dublura = true;
                                if (!dublura) matrice[j][i].push_back(productii[t][0]);
                                //daca nu este dublura adaug in matrice neterminalul
                            }
                        }
                        delete[] aux; //eliberez memoria ocupata de "produsul cartezian"
                    }
            }
}

/**
 * metoda de afisare a matricei triunghiulare rezultate in urma aplicarii algoritmului CYK
 */
void AlgoritmCYK::afisareMatrice() {
    int i, j, k;
    for (j = cuvant.size() - 1; j >= 0; j--) //afisez matricea incepand cu ultima linie, ca in exemplu
    {
        for (i = 0; i < cuvant.size() - j; i++) {
            if (matrice[j][i].empty()) //daca am multimea vida
                cout << "multime vida ";
            else {
                cout << "{ ";
                for (k = 0; k < matrice[j][i].size(); k++) {
                    cout << matrice[j][i][k] << ' ';
                }
                cout << "} ";
            }
        }
        cout << '\n';
    }
}

/**
 * metoda de verificare a unui cuvant
 * @return true, in cazul in care cuvantul poate fi generat si false in caz contrar
 */
bool AlgoritmCYK::acceptat() {
    bool raspuns = false;
    for (int i = 0; i < matrice[cuvant.size() - 1][0].size(); i++)
        //parcurg coada in care se afla neterminalele care pot genera cuvantul
        if (matrice[cuvant.size() - 1][0][i] == 'S') //daca printre ele se gaseste neterminalul S
            raspuns = true; //cuvantul poate fi generat
    return raspuns;
}