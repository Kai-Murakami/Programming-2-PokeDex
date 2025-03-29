#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class PokemonDatabase {
private:
    map<string, vector<string>> abilityMap;       
    map<string, string> abilityDescriptionMap;   
    map<string, string> strongAgainstMap;        
    map<string, string> weakAgainstMap;           


    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        return (first == string::npos) ? "" : str.substr(first, last - first + 1);
    }

   
    string toLowerCase(const string& str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

public:
 
    PokemonDatabase(const string& filename) {
        loadFromFile(filename);
    }


    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error: Could not open file '" << filename << "'.\n";
            return;
        }

        string line, currentAbility;
        while (getline(file, line)) {
            line = trim(line); 

            if (line.empty()) continue; 

           
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string key = trim(line.substr(0, pos)); 
                string value = trim(line.substr(pos + 1)); 

                if (key == "AbilityDescription") {
                    abilityDescriptionMap[toLowerCase(currentAbility)] = value;
                } else if (key == "StrongAgainst") {
                    strongAgainstMap[toLowerCase(currentAbility)] = value;
                } else if (key == "WeakAgainst") {
                    weakAgainstMap[toLowerCase(currentAbility)] = value;
                } else {
                 
                    currentAbility = toLowerCase(key);
                    istringstream ss(value);
                    string pokemon;
                    vector<string> pokemonList;

                    while (getline(ss, pokemon, ',')) {
                        pokemonList.push_back(trim(pokemon));
                    }

                    abilityMap[currentAbility] = pokemonList;
                }
            }
        }

        file.close();
    }

 
    void displayAbilities() {
        cout << "\nAvailable Abilities:\n";
        for (const auto& entry : abilityMap) {
            string ability = entry.first;
            cout << "- " << ability;
            if (abilityDescriptionMap.find(ability) != abilityDescriptionMap.end()) {
                cout << " -> " << abilityDescriptionMap[ability]; 
            }
            cout << endl;
        }
    }


    void displayPokemonByAbility(string ability) {
        ability = toLowerCase(trim(ability));

        auto it = abilityMap.find(ability);
        if (it != abilityMap.end()) {
            cout << "\nPokemon with ability '" << ability << "':\n";
            for (const auto& pokemon : it->second) {
                cout << "  - " << pokemon << endl;
            }
        } else {
            cout << "No Pokemon found with the ability '" << ability << "'.\n";
        }
    }


    void displayAbilityMatchups(string ability) {
        ability = toLowerCase(trim(ability));

        auto strongIt = strongAgainstMap.find(ability);
        auto weakIt = weakAgainstMap.find(ability);

        cout << "\nMatchups for ability '" << ability << "':\n";
        if (strongIt != strongAgainstMap.end()) {
            cout << "  Strong Against: " << strongIt->second << endl;
        } else {
            cout << "  Strong Against: None\n";
        }

        if (weakIt != weakAgainstMap.end()) {
            cout << "  Weak Against: " << weakIt->second << endl;
        } else {
            cout << "  Weak Against: None\n";
        }
    }
};

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
