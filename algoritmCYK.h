#ifndef LFA_ALGORITMUL_CYK_ALGORITMCYK_H
#define LFA_ALGORITMUL_CYK_ALGORITMCYK_H

#include <deque>
#include <string>
#include <iostream>

using namespace std;

class AlgoritmCYK {
    int numarProductii;
    char **productii;
    string cuvant;
    deque<char> **matrice; //matrice triunghiulara rezultata in urma aplicarii algoritmului CYK
public:
    AlgoritmCYK(); //constructor

    ~AlgoritmCYK(); //destructor

    void afisareProductii();

    void completareMatrice();

    //void afisareMatrice();

    //bool acceptat();
};

#endif //LFA_ALGORITMUL_CYK_ALGORITMCYK_H
