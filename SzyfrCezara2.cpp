#include <iostream>
#include <fstream>
#include <cstdlib>
#include <exception>
#include <string>
#include "trim.h"

using namespace std;

string deszyfruj(int k, string slowo);

int main() {

    ifstream odczyt("dane_cezara_2.txt");
    ofstream zapis("wyniki_cezara_2.txt");

    if (!odczyt || !zapis) {
        cerr << "Blad systemu plikow" << endl;
        return 1;
    }

    while (!odczyt.eof()) {
        string slowo;
        string klucz;
        string linia;
        getline(odczyt, linia);

        if (0 == trim(linia).length()) {
            slowo += " BLEDNY KOD - brak znakow ASCII";
        }
        else if (linia.find(" ") == string::npos) {
            slowo += " BLEDNY KOD - brak spacji";
        }
        else if (linia.find(" ") >= linia.length() - 1) {                // ostatnia (pusta) linijka w pliku tekstowym
            slowo += " BLEDNY KOD - spacja na koncu";                    // "dane_cezara_2.txt" musi zostac usunieta,
        }                                                                // aby instrukcja warunkowa dzialala poprawnie
        else {
            slowo = linia.substr(0, linia.find(" "));
            klucz = linia.substr(linia.find(" "), linia.length());
            int k;

            try {
                k = atoi(klucz.c_str());
                slowo = deszyfruj(k, slowo);
            }
            catch (exception e) {
                slowo += " BLEDNY KLUCZ - nie cyfry";
            }
        }

        zapis << slowo << endl;
    }

    odczyt.close();
    zapis.close();

    return 0;
}

string deszyfruj(int k, string slowo) {
    int kmod = k % 26;
    char* tmp = (char*)slowo.c_str();

    for (int i = 0; i < (int)slowo.length(); i++) {
        char a = tmp[i];

        if ((a - kmod) < 65) {
            tmp[i] = (a + (26 - kmod));
        }
        else {
            tmp[i] = a - kmod;
        }
    }

    return string(tmp);
}