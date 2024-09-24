#include <iostream>
#include <string>
#include <cstdlib> // dla rand() i srand()
#include <ctime>   // dla time()
#include <thread>  // dla std::this_thread::sleep_for
#include <chrono>  // dla std::chrono::seconds
#include <vector>  // dla std::vector

using namespace std;

// Struktura dla jednostki
struct Jednostka {
    string nazwa;
    int punktySily;
};

// Struktura dla armii
struct Armia {
    vector<pair<Jednostka, int>> jednostki; // para jednostka + ilość
};

// Funkcja symulująca bitwę między dwiema armiami
void symulujBitwe(Armia a, Armia b) {
    cout << "=======================" << endl;
    cout << "Bitwa pomiedzy armiami!" << endl;

    // Obliczanie całkowitej siły jednostek
    int calkowitaSilaA = 0;
    int calkowitaSilaB = 0;

    for (auto &j : a.jednostki) {
        calkowitaSilaA += j.first.punktySily * j.second;
    }
    
    for (auto &j : b.jednostki) {
        calkowitaSilaB += j.first.punktySily * j.second;
    }

    int sumaSily = calkowitaSilaA + calkowitaSilaB;

    // Obliczanie procentowych szans
    double szansaA = static_cast<double>(calkowitaSilaA) / sumaSily * 100;
    double szansaB = static_cast<double>(calkowitaSilaB) / sumaSily * 100;

    // Wyświetlenie procentowych szans
    cout << "Armia A ma " << szansaA << "% szans na zwyciestwo." << endl;
    cout << "Armia B ma " << szansaB << "% szans na zwyciestwo." << endl;

    // Losowanie liczby z zakresu od 0 do 100
    int los = rand() % 101;

    cout << "=======================" << endl;
    cout << "Trwa bitwa";
    // Symulacja bitwy z opóźnieniem
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        this_thread::sleep_for(chrono::seconds(1)); // 1-sekundowa przerwa
    }
    cout << endl;

    // Wyznaczanie zwycięzcy na podstawie losowania
    if (los <= szansaA) {
        cout << "Armia A wygrywa!" << endl;
    }
    else {
        cout << "Armia B wygrywa!" << endl;
    }
    cout << "=======================" << endl;
}

int main() {
    // Ustawienie generatora liczb losowych
    srand(static_cast<unsigned int>(time(nullptr))); // inicjalizacja generatora

    cout << "=======================" << endl;
    cout << "     Witamy w grze      " << endl;
    cout << "=======================" << endl;

    // Tworzenie jednostek
    Jednostka rycerz = { "Rycerz", 10 };
    Jednostka kawalerzysta = { "Kawalerzysta", 9 };
    Jednostka halabardzista = { "Halabardzista", 7 };
    Jednostka topornik = { "Topornik", 6 };
    Jednostka wlocznik = { "Wlocznik", 5 };
    Jednostka lucznik = { "Lucznik", 4 };
    Jednostka wekiernik = { "Wekiernik", 3 };

    // Lista jednostek
    Jednostka jednostki[] = { rycerz, kawalerzysta, halabardzista, topornik, wlocznik, lucznik, wekiernik };
    int liczbaJednostek = sizeof(jednostki) / sizeof(jednostki[0]);

    char wyborKontynuacji;

    do {
        cout << "=======================" << endl;
        cout << "Budowanie armii A:" << endl;
        Armia armiaA;
        int iloscTypowA;

        cout << "Ile typow jednostek chcesz dodac do armii A? ";
        cin >> iloscTypowA;

        for (int i = 0; i < iloscTypowA; ++i) {
            int wybor;
            int ilosc;

            cout << "Wybierz jednostke (numer): " << endl;
            for (int j = 0; j < liczbaJednostek; ++j) {
                cout << j + 1 << ". " << jednostki[j].nazwa << " (Punkty sily: " << jednostki[j].punktySily << ")" << endl;
            }
            cin >> wybor;
            cout << "Podaj ilosc jednostek " << jednostki[wybor - 1].nazwa << ": ";
            cin >> ilosc;

            if (wybor < 1 || wybor > liczbaJednostek || ilosc <= 0) {
                cout << "Niepoprawny wybor jednostki lub ilosci!" << endl;
                i--; // Powtarzamy iterację
            } else {
                armiaA.jednostki.push_back(make_pair(jednostki[wybor - 1], ilosc));
            }
        }

        cout << "=======================" << endl;
        cout << "Budowanie armii B:" << endl;
        Armia armiaB;
        int iloscTypowB;

        cout << "Ile typow jednostek chcesz dodac do armii B? ";
        cin >> iloscTypowB;

        for (int i = 0; i < iloscTypowB; ++i) {
            int wybor;
            int ilosc;

            cout << "Wybierz jednostke (numer): " << endl;
            for (int j = 0; j < liczbaJednostek; ++j) {
                cout << j + 1 << ". " << jednostki[j].nazwa << " (Punkty sily: " << jednostki[j].punktySily << ")" << endl;
            }
            cin >> wybor;
            cout << "Podaj ilosc jednostek " << jednostki[wybor - 1].nazwa << ": ";
            cin >> ilosc;

            if (wybor < 1 || wybor > liczbaJednostek || ilosc <= 0) {
                cout << "Niepoprawny wybor jednostki lub ilosci!" << endl;
                i--; // Powtarzamy iterację
            } else {
                armiaB.jednostki.push_back(make_pair(jednostki[wybor - 1], ilosc));
            }
        }

        // Symulacja bitwy
        symulujBitwe(armiaA, armiaB);

        // Pytanie o kontynuacje
        cout << "Czy chcesz powtorzyc bitwe? (t/n): ";
        cin >> wyborKontynuacji;

    } while (wyborKontynuacji == 't' || wyborKontynuacji == 'T');

    cout << "Dziekujemy za gre!" << endl;

    return 0;
}
