#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <thread>  // for std::this_thread::sleep_for
#include <chrono>  // for std::chrono::seconds
#include <vector>  // for std::vector

using namespace std;

// Structure for a unit
struct Unit {
    string name;
    int strengthPoints;
};

// Structure for an army
struct Army {
    vector<pair<Unit, int>> units; // pair of unit + quantity
};

// Function to simulate a battle between two armies
void simulateBattle(Army a, Army b) {
    cout << "=======================" << endl;
    cout << "Battle between armies!" << endl;

    // Calculating total strength of units
    int totalStrengthA = 0;
    int totalStrengthB = 0;

    for (auto& j : a.units) {
        totalStrengthA += j.first.strengthPoints * j.second;
    }

    for (auto& j : b.units) {
        totalStrengthB += j.first.strengthPoints * j.second;
    }

    int totalStrength = totalStrengthA + totalStrengthB;

    // Calculating percentage chances
    double chanceA = static_cast<double>(totalStrengthA) / totalStrength * 100;
    double chanceB = static_cast<double>(totalStrengthB) / totalStrength * 100;

    // Displaying percentage chances
    cout << "Army A has " << chanceA << "% chance of winning." << endl;
    cout << "Army B has " << chanceB << "% chance of winning." << endl;

    // Random number from 0 to 100
    int randomValue = rand() % 101;

    cout << "=======================" << endl;
    cout << "The battle is underway";
    // Simulating battle with delay
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        this_thread::sleep_for(chrono::seconds(1)); // 1-second pause
    }
    cout << endl;

    // Determining the winner based on the random draw
    if (randomValue <= chanceA) {
        cout << "Army A wins!" << endl;
    }
    else {
        cout << "Army B wins!" << endl;
    }
    cout << "=======================" << endl;
}

int main() {
    // Setting up the random number generator
    srand(static_cast<unsigned int>(time(nullptr))); // initializing the generator

    cout << "=======================" << endl;
    cout << "     Welcome to the game      " << endl;
    cout << "=======================" << endl;

    // Creating units
    Unit knight = { "Knight", 10 };
    Unit cavalryman = { "Cavalryman", 9 };
    Unit halberdier = { "Halberdier", 7 };
    Unit axeman = { "Axeman", 6 };
    Unit spearman = { "Spearman", 5 };
    Unit archer = { "Archer", 4 };
    Unit pikeman = { "Pikeman", 3 };

    // List of units
    Unit units[] = { knight, cavalryman, halberdier, axeman, spearman, archer, pikeman };
    int numberOfUnits = sizeof(units) / sizeof(units[0]);

    char continueChoice;

    do {
        cout << "=======================" << endl;
        cout << "Building Army A:" << endl;
        Army armyA;
        int numberOfTypesA;

        cout << "How many types of units do you want to add to Army A? ";
        cin >> numberOfTypesA;

        for (int i = 0; i < numberOfTypesA; ++i) {
            int choice;
            int quantity;

            cout << "Choose a unit (number): " << endl;
            for (int j = 0; j < numberOfUnits; ++j) {
                cout << j + 1 << ". " << units[j].name << " (Strength Points: " << units[j].strengthPoints << ")" << endl;
            }
            cin >> choice;
            cout << "Enter the quantity of unit " << units[choice - 1].name << ": ";
            cin >> quantity;

            if (choice < 1 || choice > numberOfUnits || quantity <= 0) {
                cout << "Invalid unit choice or quantity!" << endl;
                i--; // Repeat iteration
            }
            else {
                armyA.units.push_back(make_pair(units[choice - 1], quantity));
            }
        }

        cout << "=======================" << endl;
        cout << "Building Army B:" << endl;
        Army armyB;
        int numberOfTypesB;

        cout << "How many types of units do you want to add to Army B? ";
        cin >> numberOfTypesB;

        for (int i = 0; i < numberOfTypesB; ++i) {
            int choice;
            int quantity;

            cout << "Choose a unit (number): " << endl;
            for (int j = 0; j < numberOfUnits; ++j) {
                cout << j + 1 << ". " << units[j].name << " (Strength Points: " << units[j].strengthPoints << ")" << endl;
            }
            cin >> choice;
            cout << "Enter the quantity of unit " << units[choice - 1].name << ": ";
            cin >> quantity;

            if (choice < 1 || choice > numberOfUnits || quantity <= 0) {
                cout << "Invalid unit choice or quantity!" << endl;
                i--; // Repeat iteration
            }
            else {
                armyB.units.push_back(make_pair(units[choice - 1], quantity));
            }
        }

        // Simulating the battle
        simulateBattle(armyA, armyB);

        // Asking if the user wants to continue
        cout << "Do you want to repeat the battle? (y/n): ";
        cin >> continueChoice;

    } while (continueChoice == 'y' || continueChoice == 'Y');

    cout << "Thank you for playing!" << endl;

    return 0;
}
