#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

# include "PAPA.h"

int main() {
    PokemonDatabase db("PokemonAbility.txt");
    int choice;
    string ability;

    do {
        cout << "\n*** Pokemon Ability Search ***\n";
        cout << "1. View all abilities\n";
        cout << "2. Search Pokemon by ability\n";
        cout << "3. Check ability strengths & weaknesses\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                db.displayAbilities();
                break;
            case 2:
                cout << "Enter ability name: ";
                getline(cin, ability);
                db.displayPokemonByAbility(ability);
                break;
            case 3:
                cout << "Enter ability name: ";
                getline(cin, ability);
                db.displayAbilityMatchups(ability);
                break;
            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
